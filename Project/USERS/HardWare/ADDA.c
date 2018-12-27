/****************************ADDA.c***********************/
#include "main.h"
#include "ADDA.h"
#include "HD7279.h"
#include "82C54.h"

unsigned char xdata DAC32 _at_ 0xFD00;
unsigned char xdata ADC04 _at_ 0xFE00;
unsigned char V1[32]={0x00,0x0f,0x1f,0x2f,0x3f,0x4f,0x5f,0x6f,0x7f,0x8f,0x9f,0xaf,0xbf,0xcf,0xdf,0xef,0xff,0xef, \
                          0xdf,0xcf,0xbf,0xaf,0x9f,0x8f,0x7f,0x6f,0x5f,0x4f,0x3f,0x2f,0x1f,0x0f};

/**
	* @brief  用led显示当前ADC转换结果二进制码
  * @param  void
  * @retval void
  */
void LedShow(void)
{
	uint8_t adcValue  = gParam.adcValue;
	
	P374 =~adcValue;
}
/**
	* @brief  将ADC转换结果8位码转换显示出来
  * @param  void
  * @retval void
  */
void AdcHD7279Show(void)
{
	uint8_t adcValue  = ADC04;
	
	HD7279ShowInt(adcValue);
}
/**
	* @brief  显示ADC转换结果的电压为小数
  * @param  void
  * @retval void
  */
void ShowVoltage(void)
{
	float voltage = 5.f*(255.f-gParam.adcValue)/255.f;
	HD7279ShowFloat(voltage);
}
/**
	* @brief  ADC初始化
  * @param  void
  * @retval void
  */
void AdcInit(void)
{
	ADC04 = 0x00;
}
/**
	* @brief  得到ADC转换结果
  * @param  void
  * @retval void
  */	
uint8_t GetAdcValue(void)
{
	uint8_t adcValue=ADC04;
	return adcValue;

}
/**
	* @brief  DAC输出 50HZ的方波
  * @param  void
  * @retval void
  */
void DacOUT(void)
{
	static uint32_t xdata timeCnt=0;
	uint16_t xdata period = 80;
	static uint32_t out=0;
	timeCnt++;
	if(timeCnt<=period/2)
	{
		 out+= (uint8_t)(255.f/(period/2));
	}else if(timeCnt>period/2&&timeCnt<=period)
	{
		 out-= (uint8_t)(255.f/(period/2));
	}else if(timeCnt>period)
	{
		 timeCnt=0;
	}
	DAC32=out&0xff;
}