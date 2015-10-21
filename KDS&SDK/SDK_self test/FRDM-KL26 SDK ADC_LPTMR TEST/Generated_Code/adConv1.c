/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : adConv1.c
**     Project     : FRDM-KL26 SDK TEST
**     Processor   : MKL26Z128VLH4
**     Component   : fsl_adc16
**     Version     : Component 1.2.0, Driver 01.00, CPU db: 3.00.000
**     Repository  : KSDK 1.2.0
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-07-29, 12:43, # CodeGen: 6
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file adConv1.c
** @version 01.00
*/         
/*!
**  @addtogroup adConv1_module adConv1 module documentation
**  @{
*/         

/* adConv1. */

#include "Events.h"
#include "adConv1.h"

const adc16_converter_config_t adConv1_InitConfig0 = {
  .lowPowerEnable = false,
  .clkDividerMode = kAdc16ClkDividerOf1,
  .longSampleTimeEnable = true,
  .resolution = kAdc16ResolutionBitOf16,
  .clkSrc = kAdc16ClkSrcOfBusClk,
  .asyncClkEnable = false,
  .highSpeedEnable = true,
  .longSampleCycleMode = kAdc16LongSampleCycleOf24,
  .hwTriggerEnable = false,
  .refVoltSrc = kAdc16RefVoltSrcOfVref,
  .continuousConvEnable = false,
  .dmaEnable = false,
};

const adc16_hw_cmp_config_t adConv1_HwConfig0 = {
  .hwCmpEnable = false,
  .hwCmpGreaterThanEnable = false,
  .hwCmpRangeEnable = false,
  .cmpValue1 = 0U,
  .cmpValue2 = 0U,
};


const adc16_chn_config_t adConv1_ChnConfig0 = {
  .chnIdx = kAdc16Chn26,
  .convCompletedIntEnable = false,
  .diffConvEnable = false
};
/* END adConv1. */

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
