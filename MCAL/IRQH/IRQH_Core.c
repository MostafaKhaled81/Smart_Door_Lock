/*
 * IRQH_Core.c
 *
 * Created: 9/1/2023 5:48:17 PM
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
#include "IRQH_Core.h"
#include "ADC_Core.h"
#include "SPI_Core.h"
#include "Led.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
void(*CallBack_PtrFunc[20])(void) = {Null};
	extern uint32 TIMER0_NUMBER_OVERFLOW;
	extern uint32 TIMER0_INIT_VALUE_G;
	extern uint8 TIMER1_NO_OF_OUTPUT_COMPARES;
	extern uint8 ICU_Cnt;
	extern uint8 UART_RECIEVED_DATA[10];
	extern uint8 TX_STATUS_FLAG;
	extern uint8 TX_Cnt;
	uint8 OVF_Cnt=0;
	uint32 cap1=0;
	uint32 cap2=0;
	uint32 cap3=0;
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
* \Syntax          : void IRQH_SetGlobalINT(uint8)
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void IRQH_SetGlobalINT(uint8 Global_INT_Status)
{
	switch (Global_INT_Status)
	{
		case INT_ENABLE:
		SET_BIT(SREG,7);
		break;
		case INT_DISABLE:
		CLR_BIT(SREG,7);
		break;
		default:
		break;
	}
}

/******************************************************************************
* \Syntax          : void IRQH_SetExternalINIT(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void IRQH_SetExternalINIT(void)
{
	#if (INT_0 == INT_ENABLE)
	  SET_BIT(GICR,6);
	  #if (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_LOW_LEVEL)
	  CLR_BIT(MCUCR,0);
	  CLR_BIT(MCUCR,1);
	  #elif (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_LOGICAL_CHANGE)
	  SET_BIT(MCUCR,0);
	  CLR_BIT(MCUCR,1);
	  #elif (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE)
	  CLR_BIT(MCUCR,0);
	  SET_BIT(MCUCR,1);
	  #elif (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_RISING_EDGE)
	  SET_BIT(MCUCR,0);
	  SET_BIT(MCUCR,1);
	  #endif
	#endif
	
	#if (INT_1 == INT_ENABLE)
	  SET_BIT(GICR,7);
	  #if (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_LOW_LEVEL)
	  CLR_BIT(MCUCR,2);
	  CLR_BIT(MCUCR,3);
	  #elif (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_LOGICAL_CHANGE)
	  SET_BIT(MCUCR,2);
	  CLR_BIT(MCUCR,3);
	  #elif (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE)
	  CLR_BIT(MCUCR,2);
	  SET_BIT(MCUCR,3);
	  #elif (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_RISING_EDGE)
	  SET_BIT(MCUCR,1);
	  SET_BIT(MCUCR,3);
	  #endif
	#endif
	
	#if (INT_2 == INT_ENABLE)
	  SET_BIT(GICR,5);
	  #if (EXT_INT2_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE)
	  CLR_BIT(MCUCR,6);
	  #elif (EXT_INT2_TRIGGER == EXT_INT_TRIGGER_RISING_EDGE)
	  SET_BIT(MCUCR,6);
	  #endif
	#endif
}

/******************************************************************************
* \Syntax          : void IRQH_SetCallBack(uint8 Intrrupt_Vector_Index,void(*p)(void))
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void IRQH_SetCallBack(uint8 Intrrupt_Vector_Index,void(*p)(void))
{
	CallBack_PtrFunc[Intrrupt_Vector_Index]=p;
}

ISR(INT0_vect)
{
	if (CallBack_PtrFunc[External_Interrupt_Request_0_VECTOR_INDEX]!=Null)
	{
		(*CallBack_PtrFunc[External_Interrupt_Request_0_VECTOR_INDEX])();
	}
}
ISR(ADC_vect)
{
	uint32 Digital_Read=0;
	#if (ADC_REG_ADJUST==ADC_RIGHT_ADJUCT)
	Digital_Read=ADC_RES;
	#elif (ADC_REG_ADJUST==ADC_LEFT_ADJUCT)
	Digital_Read=(ADCH<<2)|(ADCL>>6);
	#endif
	ADC_VAL=(Digital_Read*5000)/1023;
	if (CallBack_PtrFunc[ADC_Conversion_Complete_VECTOR_INDEX]!=Null)
	{
		(*CallBack_PtrFunc[ADC_Conversion_Complete_VECTOR_INDEX])();
	}
}
ISR(TIMER0_OVF_vect)
{
	static uint8 INT_CNT_1=0;
	INT_CNT_1++;
	if (INT_CNT_1==TIMER0_NUMBER_OVERFLOW)
	{
		(*CallBack_PtrFunc[Timer_Counter0_Overflow_VECTOR_INDEX])();
		INT_CNT_1=0;
		TCNT0=TIMER0_INIT_VALUE_G;
	}
}
ISR(TIMER1_COMPA_vect)
{
	static uint8 TIMER1_CNT=0;
	TIMER1_CNT++;
	if (TIMER1_CNT==TIMER1_NO_OF_OUTPUT_COMPARES)
	{
		(*CallBack_PtrFunc[Timer_Counter1_Compare_Match_A_VECTOR_INDEX])();
		TIMER1_CNT=0;
	}
}
ISR(TIMER1_OVF_vect)
{
	OVF_Cnt++;
}
ISR(TIMER1_CAPT_vect)
{
	ICU_Cnt++;
	if (ICU_Cnt==1)
	{
		cap1=ICR1;
		OVF_Cnt=0;
		CLR_BIT(TCCR1B,6);
	}
	else if (ICU_Cnt==2)
	{
		cap2=ICR1+(OVF_Cnt*65535);
		SET_BIT(TCCR1B,6);
	}
	else if (ICU_Cnt==3)
	{
		cap3=ICR1+(OVF_Cnt*65535);
		CLR_BIT(TIMSK,5);
	}
}
ISR(USART_RXC_vect)
{
	if(CallBack_PtrFunc[USART_Rx_Complete_VECTOR_INDEX]!=0)
	{
		(*CallBack_PtrFunc[USART_Rx_Complete_VECTOR_INDEX])();
	}
}
ISR(USART_TXC_vect)
{
	TX_STATUS_FLAG=1;
	TX_Cnt++;
}
ISR(SPI_STC_vect)
{
	SPI_TRANCIEVER(0);
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/