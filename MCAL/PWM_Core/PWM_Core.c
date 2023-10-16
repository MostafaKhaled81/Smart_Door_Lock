/*
 * PWM_Core.c
 *
 * Created: 9/22/2023 2:38:50 PM
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
#include "PWM_Core.h"

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
* \Syntax          : void PWM_INIT(void)       
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void PWM_INIT(void)
{
	#if (PWM0_STATE==PWM_ENABLE)
       
	   #if (PWM0_TYPE==PWM_FAST)
          SET_BIT(TCCR0,6);
		  SET_BIT(TCCR0,3);
	   #elif (PWM0_TYPE==PWM_PHASE_CORRECT)
	      SET_BIT(TCCR0,6);
	      CLR_BIT(TCCR0,3);
	   #endif
	   
	   #if (PWM0_MODE==PWM_INVERTED)
          SET_BIT(TCCR0,4);
		  SET_BIT(TCCR0,5);
	   #elif (PWM0_MODE==PWM_NONINVERTED)
	      CLR_BIT(TCCR0,4);
		  SET_BIT(TCCR0,5);
       #endif
    #endif
	
	
	#if PWM1_STATE == PWM_ENABLE
	#if  (PWM1_TYPE == PWM_FAST)
	TCCR1A |= 0X02;
	TCCR1B |= 0X18;
	#elif (PWM1_TYPE == PWM_PHASE_CORRECT)
	TCCR1A |= 0X02;
	TCCR1B |= 0X10;
	
	#endif /*#if (PWM1_TYPE == PWM_FAST)*/
	
	#if (PWM1_MODE == PWM_INVERTED)
	TCCR1A |= 0XC0;
	#elif (PWM1_MODE == PWM_NONINVERTED)
	TCCR1A |= 0X80;
	#endif /*#if (PWM1_MODE == PWM_INVERTED)*/
	#endif /*if PWM1_STATE == PWM_ENABLE*/
	   

}

/******************************************************************************
* \Syntax          : void PWM0_Generate(uint8 DUTY_CYCLE)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void PWM0_Generate(uint8 DUTY_CYCLE)
{
	#if (PWM0_STATE==PWM_ENABLE)
	
       #if (PWM0_TYPE==PWM_FAST)
          #if (PWM0_MODE==PWM_INVERTED)
             OCR0=255-((DUTY_CYCLE*256)/100);
          #elif (PWM0_MODE==PWM_NONINVERTED)
             OCR0=((DUTY_CYCLE*256)/100)-1;
          #endif /*MODE*/
       #elif (PWM0_TYPE==PWM_PHASE_CORRECT)
          #if (PWM0_MODE==PWM_INVERTED)
             OCR0=255-((DUTY_CYCLE*256)/100);
          #elif (PWM0_MODE==PWM_NONINVERTED)
             OCR0=((DUTY_CYCLE*255)/100)-1;
          #endif /*MODE*/
       #endif /*TYPE*/
	   #if (PWM0_PRESC ==  PWM_PRESC8)
	   TCCR0 |= 0X02;
	   #elif (PWM0_PRESC == PWM_PRESC64)
	   TCCR0 |= 0X03;
	   #elif (PWM0_PRESC == PWM_PRESC256)
	   TCCR0 |= 0X04;
	   #elif (PWM0_PRESC == PWM_PRESC1024)
	   TCCR0 |= 0X05;
	   #endif /*#if (PWM0_FREQUANCY == PWM0_FREQ_2MHZ)*/
    #endif /*STATE*/
}

/******************************************************************************
* \Syntax          : void PWM1_Generate(uint8 DUTY_CYCLE,uint16 Frequency)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void PWM1_Generate(uint8 Duty_Cycle , uint16 Frequency)
{
	#if (PWM1_STATE == PWM_ENABLE)
	#if (PWM1_TYPE == PWM_FAST)
	
	/*TIMER Top number of counts*/
	ICR1 = (16000000U / (Frequency * PWM1_PRESC)) ;
	
	#if (PWM1_MODE == PWM_INVERTED)
	OCR1A = ICR1 - ((Duty_Cycle * (ICR1+1) ) /100 );
	#elif (PWM1_MODE == PWM_NONINVERTED)
	OCR1A = ((Duty_Cycle * (ICR1+1) ) /100 ) - 1;
	#endif /*if (PWM1_MODE == PWM_INVERTED)*/
	
	#elif (PWM1_TYPE == PWM_PHASE_CORRECT)
	
	/*TIMER Top number of counts*/
	ICR1 = (16000000U / (2 * (Frequency * PWM1_PRESC))) ;
	
	#if (PWM1_MODE == PWM_INVERTED)
	OCR1A = ICR1 - ((Duty_Cycle * (ICR1) ) /100 );
	
	#elif (PWM1_MODE == PWM_NONINVERTED)
	OCR1A = ((Duty_Cycle * (ICR1) ) /100 );
	#endif /*if (PWM1_MODE == PWM_INVERTED)*/
	
	#endif /*if (PWM1_TYPE == PWM_FAST)*/
	
	#if (PWM1_PRESC == PWM_PRESC8)
	TCCR1B |= 0X02;
	
	#elif (PWM1_PRESC == PWM_PRESC64)
	TCCR1B |= 0X03;
	
	#elif (PWM1_PRESC == PWM_PRESC256)
	TCCR1B |= 0X04;
	
	#elif (PWM1_PRESC == PWM_PRESC1024)
	TCCR1B |= 0X05;
	
	#endif /*#if (PWM1_PRESC == PWM_PRESC8)*/
	
	#endif /*if (PWM1_STATE == PWM_ENABLE)*/
}

/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/