/*
 * PWR_Standby.h
 *
 *  Created on: Sep 24, 2020
 *      Author: USER
 */

#ifndef INC_PWR_STANDBY_H_
#define INC_PWR_STANDBY_H_



#endif /* INC_PWR_STANDBY_H_ */

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	_Bool WLUP_BTstatus;
	uint16_t StandbyTime_Sec;
	_Bool PowerMode;
} PWRST_t;

/* Private defines -----------------------------------------------------------*/
#define LED_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_7
#define WKUP_GPIO_Port GPIOC
#define WKUP_Pin GPIO_PIN_13
#define RunMode 0
#define StandbyMode 1
/* Exported functions prototypes ---------------------------------------------*/
void EnterStandbyPWR_Mode(RTC_HandleTypeDef *hrtc);
void RUN_PWR_Mode_Init(RTC_HandleTypeDef *hrtc);
