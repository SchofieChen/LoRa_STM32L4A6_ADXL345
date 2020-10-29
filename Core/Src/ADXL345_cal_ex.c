/*
 * ADXL345_cal_ex.c
 *
 *  Created on: Oct 8, 2020
 *      Author: Wayne
 */
/* Includes ------------------------------------------------------------------*/
#include "ADXL345_cal_ex.h"
/* Private variables ---------------------------------------------------------*/
uint8_t ADXLid = 0;

/*uint8_t data[6]={0,0,0,0,0,0};
int16_t sampleIndex = 0;
extern dataReady;*/
extern int16_t sampleIndex;
extern fftInstance XfftInstance;
extern fftInstance YfftInstance;
extern fftInstance ZfftInstance;

uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
float32_t testOutput[dataLength/2];
int32_t fftSize = 2048;
float32_t maxValue = 0;
uint32_t testIndex = 0;


float32_t *ZstatisticDataSet = ZfftInstance.bufferforTimeSV;
float32_t *XstatisticDataSet = XfftInstance.bufferforTimeSV;
float32_t *YstatisticDataSet = YfftInstance.bufferforTimeSV;

/*
 * TODO: ADXL345 Wake-up and Measure, then enter standby mode.
 * */
/*
void ADXL345_Measure()
{

	while(sampleIndex < dataLength/2)
	    {
	    	ADXL_IntProto();
	    	readRegister(DATA0,data,6);
	    	if(dataReady == true)
	    	    {
	    	    	 AcquireData(&data);
	    	    	//AcquireData();
	    			sampleIndex++;
	    			dataReady = false;
	    	    }
	    }
	    FeatureExtraction();
	    //Data transmission by uart
	    sampleIndex = 0;
}
*/


/*
 * TODO: Init ADXL345 parameter and Start measurement
 * */

void ADXL345_Init()
{

	  ADXL_InitTypeDef adxl_config;
	  adxl_config.Range = RANGE_16G;
	  adxl_config.Resolution = RESOLUTION_FULL;
	  adxl_config.AutoSleep = AUTOSLEEPOFF;
	  adxl_config.LPMode = LPMODE_LOWPOWER;
	  adxl_config.Rate = BWRATE_3200;
	  adxl_config.SPIMode = SPIMODE_4WIRE;
	  adxl_config.IntMode = INT_ACTIVEHIGH;

	  adxlStatus InitStatus = ADXL_Init(&adxl_config, &ADXLid);
	  if(ADXLid == 0xE5)InitStatus = ADXL_OK;
	  if(InitStatus == ADXL_OK)
	  {
		  __NOP();

	  }

	  ADXL_Measure(ON);
	  writeRegister(INT_MAP, 0x10);
	  writeRegister(INT_ENABLE, 0x80);
}




/*
 *TODO: AcquireData from SPI
 * */
void AcquireData(uint8_t *data)
//void AcquireData()
{

	readRegister(DATA0,data,6);
	XfftInstance.data0 = data[0];
	XfftInstance.data1 = data[1];
	YfftInstance.data0 = data[2];
	YfftInstance.data1 = data[3];
	ZfftInstance.data0 = data[4];
	ZfftInstance.data1 = data[5];
	XfftInstance.acceleration = ((uint8_t)XfftInstance.data1<<8)|(uint8_t)XfftInstance.data0;
	YfftInstance.acceleration = ((uint8_t)YfftInstance.data1<<8)|(uint8_t)YfftInstance.data0;
	ZfftInstance.acceleration = ((uint8_t)ZfftInstance.data1<<8)|(uint8_t)ZfftInstance.data0;

	//3.9 is scale of LSB(one bit) mg, 1000 is scale to g
	XfftInstance.accelerationfloat = (float)XfftInstance.acceleration * 3.9 / 1000;
	YfftInstance.accelerationfloat = (float)YfftInstance.acceleration  * 3.9 / 1000;
	ZfftInstance.accelerationfloat = (float)ZfftInstance.acceleration  * 3.9 / 1000;

	// move X axis data to buffer
	XfftInstance.bufferforFFT[sampleIndex * 2] = XfftInstance.accelerationfloat;
	XfftInstance.bufferforFFT[sampleIndex * 2+1] = 0;
	XfftInstance.bufferforTimeSV[sampleIndex] = XfftInstance.accelerationfloat;

	// move Y axis data to buffer
	YfftInstance.bufferforFFT[sampleIndex * 2] = YfftInstance.accelerationfloat;
	YfftInstance.bufferforFFT[sampleIndex * 2+1] = 0;
	YfftInstance.bufferforTimeSV[sampleIndex] = YfftInstance.accelerationfloat;

	// move Z axis data to buffer
	ZfftInstance.bufferforFFT[sampleIndex * 2] = ZfftInstance.accelerationfloat;
	ZfftInstance.bufferforFFT[sampleIndex * 2+1] = 0;
	ZfftInstance.bufferforTimeSV[sampleIndex] = ZfftInstance.accelerationfloat;


}

/*
 *TODO : Calculate Time domain and Frequency Domain
 * */


void FeatureExtraction()
{
	//Calculate Z axis statistic
	movingAverage_filter(ZfftInstance.bufferforTimeSV, ZfftInstance.bufferforfilter, 2048,5);
	Calculate_FFT_RMS(ZfftInstance.bufferforFFT, testOutput, fftSize, &Zstatistic_value);
	Calculate_All_statisitc(ZfftInstance.bufferforfilter, dataLength/2, &Zstatistic_value);

	//Calculate X axis statistic
	movingAverage_filter(XfftInstance.bufferforTimeSV, XfftInstance.bufferforfilter, 2048,5);
	Calculate_FFT_RMS(XfftInstance.bufferforFFT, testOutput, fftSize, &Xstatistic_value);
	Calculate_All_statisitc(XfftInstance.bufferforfilter, dataLength/2, &Xstatistic_value);

	//Calculate Y axis statistic
	movingAverage_filter(YfftInstance.bufferforTimeSV, YfftInstance.bufferforfilter, 2048,5);
	Calculate_FFT_RMS(YfftInstance.bufferforFFT , testOutput, fftSize, &Ystatistic_value);
	Calculate_All_statisitc(YfftInstance.bufferforfilter, dataLength/2, &Ystatistic_value);


}

void movingAverage_filter(float * input_data, float * filterdata, int length, int filterOrder)
{

	for(uint16_t i=0; i<length; i++)
	{
		if(i > filterOrder )
		{
			filterdata[i] = (input_data[i] + input_data[i-1] + input_data[i-2]+ input_data[i-3]+ input_data[i-4]) / filterOrder;
		}
		else
		{
			filterdata[i] = (input_data[i] + input_data[i+1] + input_data[i+2]+ input_data[i+3]+  input_data[i+4]) / filterOrder  ;
		}
	}

}
