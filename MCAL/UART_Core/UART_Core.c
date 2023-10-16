/*
 * UART_Core.c
 *
 * Created: 9/29/2023 12:48:31 PM
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
#include "UART_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define  TX_BUFFER_SIZE  7
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint8 UART_RECIEVED_DATA[10]={0};
uint8 UART_TRANSMITE_DATA[TX_BUFFER_SIZE]={0};
uint8 RECIEVE_STATUS_FLAG=0;
uint8 TX_STATUS_FLAG=0;
uint8 TX_Cnt=0;
uint8 U_REC_DATA=0;
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
* \Syntax          : void UART_Init(void)
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void UART_Init(void)
{
	uint16 UBRR=0;
	
	/*PARITY*/
	#if (UART_PARITY_STATE==ENABLE)
	   #if (UART_PARITY_TYPE==PARITY_ODD)
           UCSRC|=0XD0;
	   #elif (UART_PARITY_TYPE==PARITY_EVEN)
	       UCSRC|=0XA0;
       #endif
	#elif (UART_PARITY_STATE==DISABLE)
	    UCSRC|=0X80;
    #endif
	
    /*INTERRUPT*/	
	#if (UART_INTERRUPT_STATE == ENABLE)
		SET_BIT(UCSRB,7);
		SET_BIT(UCSRB,6);
    #elif (UART_INTERRUPT_STATE == DISABLE)
	    CLR_BIT(UCSRB,6);
	    CLR_BIT(UCSRB,7);
	#endif
	
	/*DATA BYTES*/
	#if (UART_DATA_BYTES==UART_DATA_BYTES_9)
        UCSRC=|0X86;
		UCSRB=|0X04;
    #else
	    UCSRC=UCSRC|(UART_DATA_BYTES<<1)+0X80;
    #endif
	
	
	/*BAUD RATE*/
	UBRR = (160000/(16*UART_BAUD_RATE))-1;
	UBRRL=UBRR;
	CLR_BIT(UBRRH,7);
	UBRRH=UBRR>>8;
	
	/*RECIEVER AND TRANSMITTER*/
	SET_BIT(UCSRB,3);
	SET_BIT(UCSRB,4);
}
/******************************************************************************
* \Syntax          : void UART_InitiateTx(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void UART_InitiateTx(void)
{
	SET_BIT(UCSRB,6);
	TX_STATUS_FLAG=1;
}
/******************************************************************************
* \Syntax          : void UART_SendData(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void UART_SendData(void)
{
	
	if(TX_Cnt==TX_BUFFER_SIZE)
	{
		TX_Cnt=0;
		TX_STATUS_FLAG=0;
		CLR_BIT(UCSRB,6);
	}
	if(TX_STATUS_FLAG==1)
	{
		UDR=UART_TRANSMITE_DATA[TX_Cnt];
		TX_STATUS_FLAG=0;
	}
}
/******************************************************************************
* \Syntax          : void UART_ReceiveData(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void UART_ReceiveData(void)
{
	static uint8 REC_COUNTER=0;
	UART_RECIEVED_DATA[REC_COUNTER]=UDR;
	REC_COUNTER++;
	if(UDR=='.')
	{
		REC_COUNTER=0;
		RECIEVE_STATUS_FLAG=1;
	}
}
/******************************************************************************
* \Syntax          : void UART_ReceiveChar(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void UART_ReceiveChar(void)
{
	U_REC_DATA=UDR;
	RECIEVE_STATUS_FLAG=1;
}
/******************************************************************************
* \Syntax          : uint8 UART_RecieveStatus(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
uint8 UART_RecieveStatus(void)
{
	uint8 REC_STATUS=0;
	if (RECIEVE_STATUS_FLAG==1)
	{
		REC_STATUS=1;
		RECIEVE_STATUS_FLAG=0;
	}
	return REC_STATUS;
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/