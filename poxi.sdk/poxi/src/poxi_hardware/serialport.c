/*
 * serialport.c
 *
 *  Created on: 29 de ene. de 2017
 *      Author: Yarib Nev�rez
 */
#include <stdlib.h>
#include "xparameters.h"
#include "xuartps_hw.h"
#include "serialport.h"

static uint8_t SerialPort_sendFrameCommand(uint8_t * command, uint8_t cmdSize, uint8_t * data, uint8_t dataSize);
static uint8_t SerialPort_receiveFrameBuffer(uint8_t * buffer, uint8_t * size);
static uint8_t SerialPort_sendFrameBuffer(uint8_t * buffer, uint8_t size);
static uint8_t SerialPort_receiveBuffer(uint8_t * buffer, uint8_t size);
static void    SerialPort_sendBuffer(uint8_t * buffer, uint8_t size);
static uint8_t SerialPort_receiveByte(uint8_t * byte);
static void    SerialPort_sendByte(uint8_t byte);
static void    SerialPort_setRetries(uint8_t retries);
static void    SerialPort_setTimeOut(uint32_t timeout);
static void    SerialPort_setStdinAddress(uint32_t address);
static void    SerialPort_setStdoutAddress(uint32_t address);
static uint8_t SerialPort_isReceiveData(void);
static void    SerialPort_purge(void);
static void    SerialPort_reset(void);

static uint32_t SerialPort_stdinAddress   = STDIN_BASEADDRESS;
static uint32_t SerialPort_stdoutAddress  = STDOUT_BASEADDRESS;
static uint32_t SerialPort_timeOut        = 10000000;
static uint8_t  SerialPort_maximumRetries = 3;

static const uint8_t SerialPort_frameSignature = 0x5A;

static uint8_t SerialPort_CRC(uint8_t * buffer, uint8_t size)
{
	uint8_t crc = 0;
	if (buffer != NULL)
	{
		uint8_t i;
		for (i = 0; i < size; i ++)
		{
			crc += buffer[i];
		}
	}

	return crc;
}

static SerialPort SerialPort_obj = { SerialPort_sendFrameCommand,
                                     SerialPort_receiveFrameBuffer,
                                     SerialPort_sendFrameBuffer,
                                     SerialPort_receiveBuffer,
                                     SerialPort_sendBuffer,
                                     SerialPort_receiveByte,
                                     SerialPort_sendByte,
                                     SerialPort_setRetries,
                                     SerialPort_setTimeOut,
                                     SerialPort_setStdinAddress,
                                     SerialPort_setStdoutAddress,
                                     SerialPort_isReceiveData,
									 SerialPort_purge,
                                     SerialPort_reset };

SerialPort * SerialPort_instance(void)
{
	return & SerialPort_obj;
}

static uint8_t SerialPort_receiveFrameBuffer(uint8_t * buffer, uint8_t * size)
{
	uint8_t rc = 0;
	if (buffer != NULL)
	{
		uint8_t attempts;
		uint8_t signature;
		uint8_t crc;

		do
		{
			do
			{
				rc = SerialPort_receiveByte(&signature);
			}
			while (rc & (signature != SerialPort_frameSignature));

			if (rc)
			{
				rc = SerialPort_receiveByte(size);

				if (rc)
				{
					rc = SerialPort_receiveBuffer(buffer, *size);
				}

				if (rc)
				{
					rc = SerialPort_receiveByte(&crc) && (crc == SerialPort_CRC(buffer, *size));
				}

				if (rc)
				{
					SerialPort_sendByte(crc + (*size));
				}
			}
		}
		while ((attempts ++) < SerialPort_maximumRetries);
	}
	return rc;
}

static uint8_t SerialPort_sendFrameBuffer(uint8_t * buffer, uint8_t size)
{
	uint8_t rc = 0;

	if (buffer != NULL)
	{
		//uint8_t crc_r = 0;
		uint8_t attempts = 0;
		uint8_t crc = SerialPort_CRC(buffer, size);
		do
		{
			//SerialPort_purge();
			SerialPort_sendByte(SerialPort_frameSignature);
			SerialPort_sendByte(size);
			SerialPort_sendBuffer(buffer, size);
			SerialPort_sendByte(crc);

			//rc = SerialPort_receiveByte(&crc_r) && (crc_r == (crc + size));
			rc = 1;
		} while(!rc && (attempts++) < SerialPort_maximumRetries);
	}

	return rc;
}

static uint8_t SerialPort_sendFrameCommand(uint8_t * command, uint8_t cmdSize, uint8_t * data, uint8_t dataSize)
{
	uint8_t rc = 0;

	if ((command != NULL) && ((data != NULL) || (dataSize == 0)))
	{
		//uint8_t crc_r = 0;
		uint8_t attempts = 0;
		uint8_t crc = SerialPort_CRC(command, cmdSize) + SerialPort_CRC(data, dataSize);
		do
		{
			//SerialPort_purge();
			SerialPort_sendByte(SerialPort_frameSignature);
			SerialPort_sendByte(cmdSize + dataSize);
			SerialPort_sendBuffer(command, cmdSize);
			SerialPort_sendBuffer(data, dataSize);
			SerialPort_sendByte(crc);

			//rc = SerialPort_receiveByte(&crc_r) && (crc_r == (crc + size));
			rc = 1;
		} while(!rc && (attempts++) < SerialPort_maximumRetries);
	}

	return rc;
}

static uint8_t SerialPort_receiveBuffer(uint8_t * buffer, uint8_t size)
{
	uint8_t rc = 0;
	if (buffer != NULL)
	{
		uint8_t i;
		for (i = 0; rc && (i < size); i ++)
		{
			rc = SerialPort_receiveByte(&buffer[i]);
		}
	}

	return rc;
}

static void SerialPort_sendBuffer(uint8_t * buffer, uint8_t size)
{
	if (buffer != NULL)
	{
		uint8_t i;
		for (i = 0; i < size; i ++)
		{
			SerialPort_sendByte(buffer[i]);
		}
	}
}

static uint8_t SerialPort_receiveByte(uint8_t * byte)
{
	uint32_t rc = 0;
	int32_t ms_timeout = SerialPort_timeOut;

	while (!SerialPort_isReceiveData() && (ms_timeout --)>0);

	if (SerialPort_isReceiveData())
	{
		*byte = (uint8_t) XUartPs_ReadReg(SerialPort_stdinAddress, XUARTPS_FIFO_OFFSET);
		rc = 1;
	}

	return rc;
}

static void SerialPort_sendByte(uint8_t byte)
{
	XUartPs_SendByte(SerialPort_stdoutAddress, byte);
}

static void SerialPort_setRetries(uint8_t retries)
{
	SerialPort_maximumRetries = retries;
}

static void SerialPort_setTimeOut(uint32_t timeout)
{
	SerialPort_timeOut =  10000 * timeout;
}

static void SerialPort_setStdinAddress(uint32_t address)
{
	SerialPort_stdinAddress = address;
}

static void SerialPort_setStdoutAddress(uint32_t address)
{
	SerialPort_stdoutAddress = address;
}

static uint8_t SerialPort_isReceiveData(void)
{
	return XUartPs_IsReceiveData(SerialPort_stdinAddress);
}

static void SerialPort_purge(void)
{
	while (SerialPort_isReceiveData())
		XUartPs_ReadReg(SerialPort_stdinAddress, XUARTPS_FIFO_OFFSET);
}

static void SerialPort_reset(void)
{
	XUartPs_ResetHw(SerialPort_stdinAddress);
}
