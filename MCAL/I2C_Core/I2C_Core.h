/*
 * I2C_Core.h
 *
 * Created: 10/8/2023 4:36:11 PM
 *  Author: mk591
 */ 




/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Write File Name>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef I2C_CORE_H_
#define I2C_CORE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "STD.h"
#include "BIT_Math.h"
#include "MCU.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define START_ACK                0x08 // start has been sent#define REP_START_ACK            0x10 // repeated start#define SLAVE_ADD_AND_WR_ACK     0x18 // Master transmit ( slave address + Write request ) ACK#define SLAVE_ADD_AND_RD_ACK     0x40 // Master transmit ( slave address + Read request ) ACK#define WR_BYTE_ACK              0x28 // Master transmit data ACK#define RD_BYTE_WITH_NACK        0x50 // Master received data with not ACK#define RD_BYTE_WITH_ACK         0x58 //Master received data with ACK#define SLAVE_ADD_RCVD_RD_REQ    0xA8 // means that slave address is received with write req#define SLAVE_ADD_RCVD_WR_REQ    0x60 // means that slave address is received with read req#define SLAVE_DATA_RECEIVED      0x80 // means that read byte req is received#define SLAVE_BYTE_TRANSMITTED   0xC0 // means that write byte req is received

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void I2C_Init(void);

void I2C_StartCondition(void);

void I2C_RepeatedStart(void);

void I2C_SendAddress_WriteOperation(uint8 addr);

void I2C_SendAddress_ReadOperation(uint8 addr);

void I2C_WriteByte(uint8 data);

uint8 I2C_ReadByte(void);

void I2C_StopCondition(void);
 
#endif /* I2C_CORE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/

