/*
 * EEPROM_Core.c
 *
 * Created: 10/8/2023 9:32:01 PM
 *  Author: mk591
 */ 
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EEPROM_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void EEPROM_WriteByte(uint8 data,uint8 addr,uint8 Byte_Loc)
{
	I2C_StartCondition();
	I2C_SendAddress_WriteOperation(addr);
	I2C_WriteByte(Byte_Loc);
	I2C_WriteByte(data);
	I2C_StopCondition();
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void EEPROM_WriteMultiBytes(uint8* data,uint8 data_size,uint8 addr,uint8 Byte_Loc)
{
	uint8 cnt=0;
	I2C_StartCondition();
	I2C_SendAddress_WriteOperation(addr);
	I2C_WriteByte(Byte_Loc);
	while(cnt<data_size)
	{
		I2C_WriteByte(data[cnt]);
	}
	I2C_StopCondition();
}

/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
uint8 EEPROM_ReadByte(uint8 addr,uint8 Byte_Loc)
{
	uint8 data=0;
	I2C_StartCondition();
	I2C_SendAddress_WriteOperation(addr);
	I2C_WriteByte(Byte_Loc);
	I2C_RepeatedStart();
	I2C_SendAddress_ReadOperation(addr);
	data=I2C_ReadByte();
	I2C_StopCondition();
	return data;
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/