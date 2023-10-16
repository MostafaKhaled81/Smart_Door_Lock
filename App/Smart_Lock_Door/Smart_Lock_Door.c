/*
 * Smart_Lock_Door.c
 *
 * Created: 9/25/2023 4:49:19 PM
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
#include "Smart_Lock_Door.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint8 Pass[5]={0};
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
* \Syntax          :void SmartLockDoor_Init(void)
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void SmartLockDoor_Init(void)
{
	SERVO_INIT();
	LCD_Init();
	BLUTOOTH_MODULE_INIT();
	I2C_Init();
}

/******************************************************************************
* \Syntax          :void SmartLockDoor_Init(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
uint8 SmartLockDoor_SelectMode(void)
{
	uint8 mode=0;
	LCD_Clear();
	LCD_Write_String("1-Change Password");
	LCD_GOTO(1,0);
	LCD_Write_String("2-Open the door");
	mode=BLUETOOTH_RecieveChar();
	return mode;
}
/******************************************************************************
* \Syntax          :void SmartLockDoor_Init(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void SmartLockDoor_SetPassword(void)
{
	uint8 pass_element=0,i=0;
	
	LCD_Clear();
	LCD_GOTO(0,1);
	LCD_Write_String("Enter the new");
	LCD_GOTO(1,4);
	LCD_Write_String("Password");
	
	while(i<5)
	{
		pass_element=BLUETOOTH_RecieveChar();
		if (i==0)
		{
			LCD_Clear();
			LCD_GOTO(0,5);
		}
		LCD_WriteChar(pass_element);
	    Pass[i]=pass_element;
	    i++;
	}
	
	i=0;
	
	while(i<5)
	{
		EEPROM_WriteByte(Pass[i],0B01010000,i);
		_delay_ms(5);
		i++;
	}
}
/******************************************************************************
* \Syntax          :void Get_Password(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
bool Get_Password(void)
{
	sint8 i=0;
	uint8 element=0;
	uint8 trys=0;
	uint8 Entered_Pass[5]={0};
	for (trys=0;trys<3;trys++)
	{
		i=0;
		if (trys==0)
		{
			LCD_Clear();
			LCD_GOTO(0,2);
			LCD_Write_String("Enter password");
		}
		else
		{
			LCD_Clear();
			LCD_GOTO(0,1);
			LCD_Write_String("Wrong Password");
			LCD_GOTO(1,0);
			LCD_Write_String("Please try again");
		}
	    while (i<=4)
	    {
	    	element=BLUETOOTH_RecieveChar();
	    	Entered_Pass[i]=element;
			if (i==0)
			{
				LCD_Clear();
				LCD_GOTO(0,5);
			}
	    	LCD_WriteChar('*');
	    	element=0;
	    	i++;
	    }
		i--;
	    while (i>=0)
	    {
	    	if (Entered_Pass[i]==Pass[i])
	    	{
	    		i--;
	    	}
	    	else
	    	{
	    		break;
	    	}
	    }
		if (i==(-1))
		{
			return true;
		}
		else
		{
		}
	}
	return false;
}
/******************************************************************************
* \Syntax          :void Open_Door(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void Open_Door(void)
{
	LCD_GOTO(0,2);
	LCD_Write_String("Welcome Home");
	LED_SetValue(LED_BLUE,PIN_HIGH);
	SERVO_SetDegree(90);
	_delay_ms(3000);
	LED_SetValue(LED_BLUE,PIN_LOW);
	SERVO_SetDegree(0);
}
/******************************************************************************
* \Syntax          :void Fire_Alarm(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void Fire_Alarm(void)
{
	BUZ_SetValue(PIN_HIGH);
	_delay_ms(3000);
	BUZ_SetValue(PIN_LOW);
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/
