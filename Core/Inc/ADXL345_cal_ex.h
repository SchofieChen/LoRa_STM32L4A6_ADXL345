/*
 * ADXL345_cal_ex.h
 *
 *  Created on: Oct 8, 2020
 *      Author: USER
 */

#ifndef INC_ADXL345_CAL_EX_H_
#define INC_ADXL345_CAL_EX_H_



#endif /* INC_ADXL345_CAL_EX_H_ */

/* Private includes ----------------------------------------------------------*/
#include "ADXL.h"
#include "arm_const_structs.h"
#include "arm_math.h"
#include "Calculate_statistic.h"
//#include "stdbool.h"



/* Private define ------------------------------------------------------------*/
#define dataLength 4096
#define FFT_Frequency_Scale 3200/(dataLength/2)

/* Exported types ------------------------------------------------------------*/
typedef struct FFTInstance
{
	float32_t bufferforFFT[dataLength];
	float32_t bufferforTimeSV[dataLength/2];
	uint16_t data0;
	uint16_t data1;
	int16_t acceleration;
	float32_t accelerationfloat;
	float32_t bufferforfilter[dataLength/2];
}fftInstance;

//typedef enum {true,false} dataReadyFlag;

/* Exported functions prototypes ---------------------------------------------*/
void ADXL345_Init();
void AcquireData(uint8_t *data);
//void AcquireData();
void FeatureExtraction();
void ADXL345_Measure();
void movingAverage_filter(float * input_data, float * filterdata, int length, int filterOrder);


