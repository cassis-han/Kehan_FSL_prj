/* ###################################################################
**     Filename    : Events.h
**     Project     : FRDM-KL26 SDK TEST
**     Processor   : MKL26Z128VLH4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-07-28, 14:16, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "fsl_device_registers.h"
#include "clockMan1.h"
#include "pin_init.h"
#include "osa1.h"
#include "lpTmr1.h"
#include "DbgCs1.h"
#include "gpio1.h"
#include "adConv1.h"

#ifdef __cplusplus
extern "C" {
#endif 


void lpTmr1_OnTimerCompare(void);

/*! adConv1 IRQ handler */
void ADC0_IRQHandler(void);

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
