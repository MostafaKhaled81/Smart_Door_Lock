/*
 * I2C_Core.c
 *
 * Created: 10/8/2023 4:35:57 PM
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
#include "I2C_Core.h"
#include "LCD_Core.h"
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
void I2C_Init(void)
{
	/*Init SCL 400KHZ / TWBR=0X0C*/
	/*Init SCL 100KHZ / TWBR=0X28*/
	TWBR =0X0C;
	CLR_BIT(TWSR,0);
	CLR_BIT(TWSR,1);
	
	/*SET NODE ADDRESS*/
	TWAR|=(0X01<<1);
	
	/*ENABLE ACK*/
	SET_BIT(TWCR,6);
	
	/*ENABLE I2C*/
	SET_BIT(TWCR,2);
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
void I2C_StartCondition(void)
{
	SET_BIT(TWCR,5);
    TWCR=0X84;
	while(GET_BIT(TWCR,7)==0);
	while((TWSR&0xF8)!=START_ACK);
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
void I2C_RepeatedStart(void)
{
	SET_BIT(TWCR,5);
	TWCR|=0X84;
	while(GET_BIT(TWCR,7)==0);
	while((TWSR&0xF8)!=REP_START_ACK);
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
void I2C_SendAddress_WriteOperation(uint8 addr)
{
	TWDR=(addr<<1);
	TWCR=0X84;
	while(GET_BIT(TWCR,7)==0);
	while((TWSR&0xF8)!=SLAVE_ADD_AND_WR_ACK);
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
void I2C_SendAddress_ReadOperation(uint8 addr)
{
	TWDR=((addr<<1)|1);
	TWCR=0X84;
	while(GET_BIT(TWCR,7)==0);
	while((TWSR&(0xF8))!=SLAVE_ADD_AND_RD_ACK);
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
void I2C_WriteByte(uint8 data)
{
	TWDR=data;
	TWCR=0X84;
	while(GET_BIT(TWCR,7)==0);
	while((TWSR&0xF8)!=WR_BYTE_ACK);
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
uint8 I2C_ReadByte(void)
{
	uint8 data=0;
	TWCR=0X84;
	while(GET_BIT(TWCR,7)==0);
	while((TWSR & 0xF8)!=RD_BYTE_WITH_ACK);
	data=TWDR;
	return data;
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
void I2C_StopCondition(void)
{
	TWCR=0X94;
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/