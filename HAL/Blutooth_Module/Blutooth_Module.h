/*
 * Blutooth_Module.h
 *
 * Created: 10/2/2023 11:33:29 PM
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
#ifndef BLUTOOTH_MODULE_H_
#define BLUTOOTH_MODULE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "UART_Core.h"
#include "IRQH_Core.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


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
void BLUTOOTH_MODULE_INIT(void);

uint8 BLUETOOTH_RecieveChar(void);
 
#endif /* BLUTOOTH_MODULE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/

