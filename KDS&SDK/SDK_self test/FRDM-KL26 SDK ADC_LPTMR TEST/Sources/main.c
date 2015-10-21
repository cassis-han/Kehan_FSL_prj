/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM-KL26 SDK TEST
**     Processor   : MKL26Z128VLH4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-07-28, 14:16, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "clockMan1.h"
#include "pin_init.h"
#include "osa1.h"
#include "lpTmr1.h"
#include "DbgCs1.h"
#include "gpio1.h"
#include "adConv1.h"

#include "stdio.h"

#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif

/* User includes (#include below this line is not maintained by Processor Expert) */
#define ADC16_INSTANCE                (0)   // ADC instacne
#define ADC16_TEMPERATURE_CHN         (kAdc16Chn26) // Temperature Sensor Channel
#define ADC16_BANDGAP_CHN             (kAdc16Chn27) // ADC channel of BANDGAP
#define ADC16_CHN_GROUP               (0)   // ADC group configuration selection

#define ADCR_VDD                (65535U)    // Maximum value when use 16b resolution
#define V_BG                    (1000U)     // BANDGAP voltage in mV (trim to 1.0V)
#define V_TEMP25                (716U)      // Typical converted value at 25 oC in mV
#define M                       (1620U)     // Typical slope:uV/oC
#define STANDARD_TEMP           (25)

adc16_hw_average_config_t  hw_average_config;
adc16_calibration_param_t  calibration_param;
volatile uint32_t lptmrCounter=0;

uint32_t adcValue = 0;               // ADC value
uint32_t adcrTemp25 = 0;             // Calibrated ADCR_TEMP25
uint32_t adcr100m = 0;               // calibrated conversion value of 100mV

void ADC16_Measure(void);
void calibrateParams(void);
int32_t get_current_temperature(uint32_t adcValue);

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
   uint32_t      currentCounter = 0;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  hw_average_config.hwAverageCountMode = kAdc16HwAverageCountOf32;      //enable hardware average.
  ADC16_DRV_ConfigHwAverage(FSL_ADCONV1,&hw_average_config);
  ADC16_DRV_GetAutoCalibrationParam(FSL_ADCONV1,&calibration_param);

  calibrateParams();
  //ADC16_DRV_Init(FSL_ADCONV1, &adConv1_InitConfig0);

  LPTMR_DRV_SetTimerPeriodUs(FSL_LPTMR1,1000000);  // Set lptmr period
  printf("\r\nLPTMR is running!!\r\n");
  LPTMR_DRV_Start(FSL_LPTMR1);
  /* Write your code here */
  /* For example: for(;;) { } */
  while(1)
  {
      if(currentCounter != lptmrCounter)
      {
          currentCounter = lptmrCounter;
          printf("\r\nLPTMR interrupt No.%d \r\n",currentCounter);
          GPIO_DRV_TogglePinOutput(LEDRGB_GREEN);
      }
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
void calibrateParams(void)
{
    adc16_chn_config_t adcChnConfig;
#if FSL_FEATURE_ADC16_HAS_HW_AVERAGE
    adc16_hw_average_config_t userHwAverageConfig;
#endif
    pmc_bandgap_buffer_config_t pmcBandgapConfig = {
        .enable = true,
#if FSL_FEATURE_PMC_HAS_BGEN
        .enableInLowPower = false,
#endif
#if FSL_FEATURE_PMC_HAS_BGBDS
        .drive = kPmcBandgapBufferDriveLow,
#endif
    };

    uint32_t bandgapValue = 0;  // ADC value of BANDGAP
    uint32_t vdd = 0;           // VDD in mV

#if FSL_FEATURE_ADC16_HAS_CALIBRATION
    // Auto calibration
    adc16_calibration_param_t adcCalibraitionParam;
    ADC16_DRV_GetAutoCalibrationParam(ADC16_INSTANCE, &adcCalibraitionParam);
    ADC16_DRV_SetCalibrationParam(ADC16_INSTANCE, &adcCalibraitionParam);
#endif // FSL_FEATURE_ADC16_HAS_CALIBRATION.

    // Enable BANDGAP reference voltage
    PMC_HAL_BandgapBufferConfig(PMC_BASE_PTR, &pmcBandgapConfig);

#if FSL_FEATURE_ADC16_HAS_HW_AVERAGE
    // Use hardware average to increase stability of the measurement.
    userHwAverageConfig.hwAverageEnable = true;
    userHwAverageConfig.hwAverageCountMode = kAdc16HwAverageCountOf32;
    ADC16_DRV_ConfigHwAverage(ADC16_INSTANCE, &userHwAverageConfig);
#endif // FSL_FEATURE_ADC16_HAS_HW_AVERAGE

    // Configure the conversion channel
    // differential and interrupt mode disable.
    adcChnConfig.chnIdx                  = (adc16_chn_t)ADC16_BANDGAP_CHN;
#if FSL_FEATURE_ADC16_HAS_DIFF_MODE
    adcChnConfig.diffConvEnable          = false;
#endif
    adcChnConfig.convCompletedIntEnable  = false;
    ADC16_DRV_ConfigConvChn(ADC16_INSTANCE, ADC16_CHN_GROUP, &adcChnConfig);

    // Wait for the conversion to be done
    ADC16_DRV_WaitConvDone(ADC16_INSTANCE, ADC16_CHN_GROUP);

    // Get current ADC BANDGAP value and format it.
    bandgapValue = ADC16_DRV_GetConvValueSigned(ADC16_INSTANCE, ADC16_CHN_GROUP);
    // Calculates bandgapValue in 16bit resolution
    // from 12bit resolution to calibrate.
#if (FSL_FEATURE_ADC16_MAX_RESOLUTION < 16)
    bandgapValue = bandgapValue << 4;
#endif
    // ADC stop conversion
    ADC16_DRV_PauseConv(ADC16_INSTANCE, ADC16_CHN_GROUP);

    // Get VDD value measured in mV
    // VDD = (ADCR_VDD x V_BG) / ADCR_BG
    vdd = ADCR_VDD * V_BG / bandgapValue;
    // Calibrate ADCR_TEMP25
    // ADCR_TEMP25 = ADCR_VDD x V_TEMP25 / VDD
    adcrTemp25 = ADCR_VDD * V_TEMP25 / vdd;
    // Calculate conversion value of 100mV.
    // ADCR_100M = ADCR_VDD x 100 / VDD
    adcr100m = ADCR_VDD*100/ vdd;

    // Disable BANDGAP reference voltage
    pmcBandgapConfig.enable = false;
    PMC_HAL_BandgapBufferConfig(PMC_BASE_PTR, &pmcBandgapConfig);
}



/*!
 * @brief Gets current temperature of chip.
 *
 * This function gets convertion value, converted temperature and print them to terminal.
 */
void ADC16_Measure(void)
{
    adc16_chn_config_t chnConfig;

    // Configure the conversion channel
    // differential and interrupt mode disable.
    chnConfig.chnIdx     = (adc16_chn_t)ADC16_TEMPERATURE_CHN;
#if FSL_FEATURE_ADC16_HAS_DIFF_MODE
    chnConfig.diffConvEnable = false;
#endif
    chnConfig.convCompletedIntEnable  = false;

    // Software trigger the conversion.
    ADC16_DRV_ConfigConvChn(ADC16_INSTANCE, ADC16_CHN_GROUP, &chnConfig);

    //ADC16_DRV_ConfigConvChn(FSL_ADCONV1, 0U, &adConv1_ChnConfig0);
    // Wait for the conversion to be done.
    ADC16_DRV_WaitConvDone(ADC16_INSTANCE, ADC16_CHN_GROUP);

    // Fetch the conversion value.
    adcValue = ADC16_DRV_GetConvValueSigned(ADC16_INSTANCE, ADC16_CHN_GROUP);

    // Show the current temperature value.
    PRINTF("\r\n ADC converted value: %ld\t", adcValue );
    // Calculates adcValue in 16bit resolution
    // from 12bit resolution in order to convert to temperature.
#if (FSL_FEATURE_ADC16_MAX_RESOLUTION < 16)
    adcValue = adcValue << 4;
#endif
    PRINTF("\r\n Temperature %ld\r\n", get_current_temperature(adcValue));
    // Pause the conversion.
    ADC16_DRV_PauseConv(ADC16_INSTANCE, ADC16_CHN_GROUP);

}

/*!
 * @brief Calculates the current temperature
 *
 * This funcion calculate temperatue used calibrated value as formula in reference manual.
 *
 * @param ADC convered value of temperature.
 * @return current temperature in oC.
 */
int32_t get_current_temperature(uint32_t adcValue)
{
    int32_t currentTemp = 0;
    // Multiplied by 1000 because M in uM/oC
    // Temperature = 25 - (ADCR_T - ADCR_TEMP25) * 100*1000 / ADCR_100M*M
    currentTemp = (int32_t)(STANDARD_TEMP - ((int32_t)adcValue - (int32_t)adcrTemp25) * 100000 /(int32_t)(adcr100m*M));

    return currentTemp;
}
