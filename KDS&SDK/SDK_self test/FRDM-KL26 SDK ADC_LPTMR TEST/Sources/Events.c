/* ###################################################################
**     Filename    : Events.c
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
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 

extern void ADC16_Measure(void);
extern int32_t get_current_temperature(uint32_t adcValue);
extern volatile uint32_t lptmrCounter;
/* User includes (#include below this line is not maintained by Processor Expert) */

void lpTmr1_OnTimerCompare(void)
{
  /* Write your code here ... */
	lptmrCounter++;
	ADC16_Measure();
}

/*! adConv1 IRQ handler */
void ADC0_IRQHandler(void)
{
  /* Write your code here ... */
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
