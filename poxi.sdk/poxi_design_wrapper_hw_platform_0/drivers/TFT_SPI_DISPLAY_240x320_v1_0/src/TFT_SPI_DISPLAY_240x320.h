
#ifndef TFT_SPI_DISPLAY_240X320_H
#define TFT_SPI_DISPLAY_240X320_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"
#include "xparameters.h"

#define TFT_SPI_DISPLAY_240X320_S00_AXI_SLV_REG0_OFFSET 0
#define TFT_SPI_DISPLAY_240X320_S00_AXI_SLV_REG1_OFFSET 4
#define TFT_SPI_DISPLAY_240X320_S00_AXI_SLV_REG2_OFFSET 8
#define TFT_SPI_DISPLAY_240X320_S00_AXI_SLV_REG3_OFFSET 12


/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a TFT_SPI_DISPLAY_240X320 register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the TFT_SPI_DISPLAY_240X320device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void TFT_SPI_DISPLAY_240X320_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define TFT_SPI_DISPLAY_240X320_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a TFT_SPI_DISPLAY_240X320 register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the TFT_SPI_DISPLAY_240X320 device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 TFT_SPI_DISPLAY_240X320_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define TFT_SPI_DISPLAY_240X320_mReadReg(BaseAddress, RegOffset) \
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
 * @param   baseaddr_p is the base address of the TFT_SPI_DISPLAY_240X320 instance to be worked on.
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
XStatus TFT_SPI_DISPLAY_240X320_Reg_SelfTest(void * baseaddr_p);


// TFT SPI DISPLAY 240x320 PMOD DEVICE

#define ACCESS_REGISTER(base, index)		(*((volatile uint32_t *)((base)+4*(index))))
#define REGISTER_GET(reg, mask, shift)		(((mask) & (reg)) >> (shift))
#define REGISTER_SET(reg, mask, shift, val)	((reg) = (~mask & (reg)) | ((mask) & ((val)<<(shift))))


#define TFT_SPI_BASEADDR					XPAR_TFT_SPI_DISPLAY_240X320_0_S00_AXI_BASEADDR //_AXI_BASEADDR                !!

#define TFT_SPI_CONTROL_REGISTER_INDEX		0
#define TFT_SPI_CONTROL_REGISTER			ACCESS_REGISTER(TFT_SPI_BASEADDR, TFT_SPI_CONTROL_REGISTER_INDEX)
#define TFT_SPI_DATA_REGISTER_INDEX			1
#define TFT_SPI_DATA						ACCESS_REGISTER(TFT_SPI_BASEADDR, TFT_SPI_DATA_REGISTER_INDEX)

#define TFT_SPI_BAUD_RATE_DIVIDER_MASK		0x000000FFu
#define TFT_SPI_BAUD_RATE_DIVIDER_SHIFT		0
#define SET_TFT_SPI_BAUD_RATE_DIVIDER(val)	REGISTER_SET(TFT_SPI_CONTROL_REGISTER,	     \
													 	 TFT_SPI_BAUD_RATE_DIVIDER_MASK, \
														 TFT_SPI_BAUD_RATE_DIVIDER_SHIFT,\
														 val)
#define GET_TFT_SPI_BAUD_RATE_DIVIDER		REGISTER_GET(TFT_SPI_CONTROL_REGISTER,	     \
														 TFT_SPI_BAUD_RATE_DIVIDER_MASK, \
														 TFT_SPI_BAUD_RATE_DIVIDER_SHIFT)


#define TFT_SPI_CLOCK_PHASE_MASK			0x00000100u
#define TFT_SPI_CLOCK_PHASE_SHIFT			8
#define SET_TFT_SPI_CLOCK_PHASE(val)		REGISTER_SET(TFT_SPI_CONTROL_REGISTER, \
													 	 TFT_SPI_CLOCK_PHASE_MASK, \
														 TFT_SPI_CLOCK_PHASE_SHIFT,\
														 val)
#define GET_TFT_SPI_CLOCK_PHASE				REGISTER_GET(TFT_SPI_CONTROL_REGISTER, \
														 TFT_SPI_CLOCK_PHASE_MASK, \
														 TFT_SPI_CLOCK_PHASE_SHIFT)


#define TFT_SPI_CLOCK_POLARITY_MASK			0x00000200u
#define TFT_SPI_CLOCK_POLARITY_SHIFT		9
#define SET_TFT_SPI_CLOCK_POLARITY(val)		REGISTER_SET(TFT_SPI_CONTROL_REGISTER,	  \
													 	 TFT_SPI_CLOCK_POLARITY_MASK, \
														 TFT_SPI_CLOCK_POLARITY_SHIFT,\
														 val)
#define GET_TFT_SPI_CLOCK_POLARITY			REGISTER_GET(TFT_SPI_CONTROL_REGISTER,	  \
														 TFT_SPI_CLOCK_POLARITY_MASK, \
														 TFT_SPI_CLOCK_POLARITY_SHIFT)

#define TFT_SPI_DATA_LENGTH_8_BITS          0
#define TFT_SPI_DATA_LENGTH_16_BITS         1
#define TFT_SPI_DATA_LENGTH_24_BITS         2
#define TFT_SPI_DATA_LENGTH_32_BITS         3

#define TFT_SPI_DATA_LENGTH_MASK			0x00000C00u
#define TFT_SPI_DATA_LENGTH_SHIFT			10
#define SET_TFT_SPI_DATA_LENGTH(val)		REGISTER_SET(TFT_SPI_CONTROL_REGISTER, \
													 	 TFT_SPI_DATA_LENGTH_MASK, \
														 TFT_SPI_DATA_LENGTH_SHIFT,\
														 val)
#define GET_TFT_SPI_DATA_LENGTH				REGISTER_GET(TFT_SPI_CONTROL_REGISTER, \
														 TFT_SPI_DATA_LENGTH_MASK, \
														 TFT_SPI_DATA_LENGTH_SHIFT)


#define TFT_CS_FORCE_MASK				    0x00001000u
#define TFT_CS_FORCE_SHIFT				    12
#define SET_TFT_CS_FORCE(val)			    REGISTER_SET(TFT_SPI_CONTROL_REGISTER, \
													 	 TFT_CS_FORCE_MASK,        \
														 TFT_CS_FORCE_SHIFT,       \
														 val)
#define GET_TFT_CS_FORCE				    REGISTER_GET(TFT_SPI_CONTROL_REGISTER, \
														 TFT_CS_FORCE_MASK,        \
														 TFT_CS_FORCE_SHIFT)


#define TFT_SPI_SETTLE_TIME_MASK			0x00006000u
#define TFT_SPI_SETTLE_TIME_SHIFT			13
#define SET_TFT_SPI_SETTLE_TIME(val)		REGISTER_SET(TFT_SPI_CONTROL_REGISTER, \
													 	 TFT_SPI_SETTLE_TIME_MASK, \
														 TFT_SPI_SETTLE_TIME_SHIFT,\
														 val)
#define GET_TFT_SPI_SETTLE_TIME				REGISTER_GET(TFT_SPI_CONTROL_REGISTER, \
														 TFT_SPI_SETTLE_TIME_MASK, \
														 TFT_SPI_SETTLE_TIME_SHIFT)


#define TFT_TRANSMISSION_DONE_MASK			0x00008000u
#define TFT_TRANSMISSION_DONE_SHIFT			15
#define GET_TFT_TRANSMISSION_DONE			REGISTER_GET(TFT_SPI_CONTROL_REGISTER,   \
														 TFT_TRANSMISSION_DONE_MASK, \
														 TFT_TRANSMISSION_DONE_SHIFT)


#define TFT_DATA_COMMAND_MASK				0x00010000u
#define TFT_DATA_COMMAND_SHIFT				16
#define SET_TFT_DATA_COMMAND(val)			REGISTER_SET(TFT_SPI_CONTROL_REGISTER, \
													 	 TFT_DATA_COMMAND_MASK,    \
														 TFT_DATA_COMMAND_SHIFT,   \
														 val)
#define GET_TFT_DATA_COMMAND				REGISTER_GET(TFT_SPI_CONTROL_REGISTER, \
														 TFT_DATA_COMMAND_MASK,    \
														 TFT_DATA_COMMAND_SHIFT)

#define TFT_RESET_MASK						0x00020000u
#define TFT_RESET_SHIFT						17
#define SET_TFT_RESET(val)					REGISTER_SET(TFT_SPI_CONTROL_REGISTER, \
													 	 TFT_RESET_MASK,           \
														 TFT_RESET_SHIFT,          \
														 val)
#define GET_TFT_RESET						REGISTER_GET(TFT_SPI_CONTROL_REGISTER, \
														 TFT_RESET_MASK,           \
														 TFT_RESET_SHIFT)


#endif // TFT_SPI_DISPLAY_240X320_H
