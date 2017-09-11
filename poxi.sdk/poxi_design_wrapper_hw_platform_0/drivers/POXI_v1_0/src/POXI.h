
#ifndef POXI_H
#define POXI_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"
#include "xparameters.h"

#define POXI_S00_AXI_SLV_REG0_OFFSET 0
#define POXI_S00_AXI_SLV_REG1_OFFSET 4
#define POXI_S00_AXI_SLV_REG2_OFFSET 8
#define POXI_S00_AXI_SLV_REG3_OFFSET 12


/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a POXI register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the POXIdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void POXI_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define POXI_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a POXI register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the POXI device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 POXI_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define POXI_mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

/************************** Function Prototypes ****************************/
/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the POXI instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus POXI_Reg_SelfTest(void * baseaddr_p);

#define IP_POXI_BASEADDR					XPAR_POXI_0_S00_AXI_BASEADDR// _AXI_BASEADDR   !!!!!!


#define ACCESS_REGISTER(base, index)		(*((volatile uint32_t *)((base)+4*(index))))
#define REGISTER_GET(reg, mask, shift)		(((mask) & (reg)) >> (shift))
#define REGISTER_SET(reg, mask, shift, val)	((reg) = (~mask & (reg)) | ((mask) & ((val)<<(shift))))

// POXI PMOD DEVICE

#define POXI_ZYBO_GPIO_REGISTER_INDEX       0
#define POXI_ZYBO_GPIO_REGISTER             ACCESS_REGISTER(IP_POXI_BASEADDR, POXI_ZYBO_GPIO_REGISTER_INDEX)

#define POXI_SPI_CONTROL_REGISTER_INDEX		1
#define POXI_SPI_CONTROL_REGISTER			ACCESS_REGISTER(IP_POXI_BASEADDR, POXI_SPI_CONTROL_REGISTER_INDEX)

#define POXI_SPI_DATA_REGISTER_INDEX		2
#define POXI_SPI_DATA						ACCESS_REGISTER(IP_POXI_BASEADDR, POXI_SPI_DATA_REGISTER_INDEX)


#define POXI_ZYBO_LEDS_MASK		            0x0000000Fu
#define POXI_ZYBO_LEDS_SHIFT	            0
#define SET_POXI_ZYBO_LEDS(val)	            REGISTER_SET(POXI_ZYBO_GPIO_REGISTER, \
														 POXI_ZYBO_LEDS_MASK,	  \
														 POXI_ZYBO_LEDS_SHIFT,    \
														 val)


#define POXI_ZYBO_SWITCHS_MASK		        0x0000000Fu
#define POXI_ZYBO_SWITCHS_SHIFT             0	 
#define GET_POXI_ZYBO_SWITCHS       		REGISTER_GET(POXI_ZYBO_GPIO_REGISTER, \
														 POXI_ZYBO_SWITCHS_MASK,  \
														 POXI_ZYBO_SWITCHS_SHIFT)


#define POXI_ZYBO_PUSHBUTTONS_MASK          0x000000F0u
#define POXI_ZYBO_PUSHBUTTONS_SHIFT         4
#define GET_POXI_ZYBO_PUSHBUTTONS           REGISTER_GET(POXI_ZYBO_GPIO_REGISTER, \
														 POXI_ZYBO_PUSHBUTTONS_MASK,  \
														 POXI_ZYBO_PUSHBUTTONS_SHIFT)


#define POXI_SPI_BAUD_RATE_DIVIDER_MASK		0x000000FFu
#define POXI_SPI_BAUD_RATE_DIVIDER_SHIFT	0
#define SET_POXI_SPI_BAUD_RATE_DIVIDER(val)	REGISTER_SET(POXI_SPI_CONTROL_REGISTER,			\
														 POXI_SPI_BAUD_RATE_DIVIDER_MASK,	\
														 POXI_SPI_BAUD_RATE_DIVIDER_SHIFT,  \
														 val)
#define GET_POXI_SPI_BAUD_RATE_DIVIDER		REGISTER_GET(POXI_SPI_CONTROL_REGISTER,			\
														 POXI_SPI_BAUD_RATE_DIVIDER_MASK,	\
														 POXI_SPI_BAUD_RATE_DIVIDER_SHIFT)


#define POXI_SPI_CLOCK_PHASE_MASK			0x00000100u
#define POXI_SPI_CLOCK_PHASE_SHIFT			8
#define SET_POXI_SPI_CLOCK_PHASE(val)		REGISTER_SET(POXI_SPI_CONTROL_REGISTER,	\
														 POXI_SPI_CLOCK_PHASE_MASK,	\
														 POXI_SPI_CLOCK_PHASE_SHIFT,\
														 val)
#define GET_POXI_SPI_CLOCK_PHASE			REGISTER_GET(POXI_SPI_CONTROL_REGISTER,	\
														 POXI_SPI_CLOCK_PHASE_MASK,	\
														 POXI_SPI_CLOCK_PHASE_SHIFT)


#define POXI_SPI_CLOCK_POLARITY_MASK		0x00000200u
#define POXI_SPI_CLOCK_POLARITY_SHIFT		9
#define SET_POXI_SPI_CLOCK_POLARITY(val)	REGISTER_SET(POXI_SPI_CONTROL_REGISTER,	   \
														 POXI_SPI_CLOCK_POLARITY_MASK, \
														 POXI_SPI_CLOCK_POLARITY_SHIFT,\
														 val)
#define GET_POXI_SPI_CLOCK_POLARITY			REGISTER_GET(POXI_SPI_CONTROL_REGISTER,	   \
														 POXI_SPI_CLOCK_POLARITY_MASK, \
														 POXI_SPI_CLOCK_POLARITY_SHIFT)


#define POXI_SPI_DATA_LENGTH_8_BITS			0
#define POXI_SPI_DATA_LENGTH_16_BITS		1
#define POXI_SPI_DATA_LENGTH_24_BITS		2
#define POXI_SPI_DATA_LENGTH_32_BITS		3

#define POXI_SPI_DATA_LENGTH_MASK			0x00000C00u
#define POXI_SPI_DATA_LENGTH_SHIFT			10
#define SET_POXI_SPI_DATA_LENGTH(val)		REGISTER_SET(POXI_SPI_CONTROL_REGISTER,	\
													 	 POXI_SPI_DATA_LENGTH_MASK, \
														 POXI_SPI_DATA_LENGTH_SHIFT,\
														 val)
#define GET_POXI_SPI_DATA_LENGTH			REGISTER_GET(POXI_SPI_CONTROL_REGISTER,	\
														 POXI_SPI_DATA_LENGTH_MASK, \
														 POXI_SPI_DATA_LENGTH_SHIFT)


#define POXI_SPI_TRANSMISSION_DONE_MASK		0x00008000u
#define POXI_SPI_TRANSMISSION_DONE_SHIFT	15
#define GET_POXI_SPI_TRANSMISSION_DONE		REGISTER_GET(POXI_SPI_CONTROL_REGISTER,       \
														 POXI_SPI_TRANSMISSION_DONE_MASK, \
														 POXI_SPI_TRANSMISSION_DONE_SHIFT)


#define POXI_SPI_NO_CS  0x00
#define POXI_SPI_DAC_CS 0x01
#define POXI_SPI_PGA_CS 0x02
#define POXI_SPI_ADC_CS 0x03

#define POXI_SPI_SLAVE_SELECT_MASK			0x00030000u
#define POXI_SPI_SLAVE_SELECT_SHIFT			16
#define SET_POXI_SPI_SLAVE_SELECT(val)		REGISTER_SET(POXI_SPI_CONTROL_REGISTER,	 \
													 	 POXI_SPI_SLAVE_SELECT_MASK, \
														 POXI_SPI_SLAVE_SELECT_SHIFT,\
														 val)
#define GET_POXI_SPI_SLAVE_SELECT			REGISTER_GET(POXI_SPI_CONTROL_REGISTER,	 \
														 POXI_SPI_SLAVE_SELECT_MASK, \
														 POXI_SPI_SLAVE_SELECT_SHIFT)


#define POXI_SPI_LED_RED_MASK				0x01000000u
#define POXI_SPI_LED_RED_SHIFT				24
#define SET_POXI_SPI_LED_RED(val)			REGISTER_SET(POXI_SPI_CONTROL_REGISTER,	\
													 	 POXI_SPI_LED_RED_MASK,     \
														 POXI_SPI_LED_RED_SHIFT,    \
														 val)
#define GET_POXI_SPI_LED_RED				REGISTER_GET(POXI_SPI_CONTROL_REGISTER,	\
														 POXI_SPI_LED_RED_MASK,     \
														 POXI_SPI_LED_RED_SHIFT)


#define POXI_SPI_LED_INFRARED_MASK			0x02000000u
#define POXI_SPI_LED_INFRARED_SHIFT			25
#define SET_POXI_SPI_LED_INFRARED(val)		REGISTER_SET(POXI_SPI_CONTROL_REGISTER,	 \
													 	 POXI_SPI_LED_INFRARED_MASK, \
														 POXI_SPI_LED_INFRARED_SHIFT,\
														 val)
#define GET_POXI_SPI_LED_INFRARED			REGISTER_GET(POXI_SPI_CONTROL_REGISTER,  \
														 POXI_SPI_LED_INFRARED_MASK, \
														 POXI_SPI_LED_INFRARED_SHIFT)


#endif // POXI_2_H
