/*
 * PWR_Standby.c
 *
 *  Created on: Sep 25, 2020
 *      Author: USER
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private variables ---------------------------------------------------------*/
PWRST_t PWRST;


void EnterStandbyPWR_Mode(RTC_HandleTypeDef *hrtc)
{
	//-------Wake up Pin setting---------------------
	/*
	// Disable all used wakeup sources: Pin2(PC.13)
	HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN2);
	// Clear the related wakeup pin flag
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WUF2);
	// Re-enable all used wakeup sources: Pin2(PC.13)
	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2);
	*/

	//-------RTC Wake up setting---------------------
	//Set StnadbyTime
	PWRST.StandbyTime_Sec = 10 ;
	//set RTC WakeUpTimer
	if (HAL_RTCEx_SetWakeUpTimer_IT(hrtc, PWRST.StandbyTime_Sec, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK)
	{
		Error_Handler();
	}
	/* Request to enter STANDBY mode  */
	HAL_PWR_EnterSTANDBYMode();
}

void RUN_PWR_Mode_Init(RTC_HandleTypeDef *hrtc)
{
	/*
	//-------Wake up Pin setting---------------------
	if(__HAL_PWR_GET_FLAG(PWR_FLAG_SB)!=RESET)
	{		// Clear the related wakeup pin flag
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WUF2);
		// Disable all used wakeup sources: Pin2(PC.13)
		HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN2);
	}
	*/
	//-------RTC Wake up setting---------------------
	//Disable RTC WakeUpTimer
	HAL_RTCEx_DeactivateWakeUpTimer(hrtc);
}
