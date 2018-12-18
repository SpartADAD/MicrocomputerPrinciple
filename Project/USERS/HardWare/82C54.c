/****************************82C54.c***********************/
#include "82C54.h"
#include "main.h"
#include "STC15F2K60S2.h"
#include "HD7279.h"

uint8_t xdata P8254_CTL _at_ 0xF903;
uint8_t xdata P8254_0 _at_ 0xF900;
uint8_t xdata P8254_1 _at_ 0xF901;
uint8_t xdata P8254_2 _at_ 0xF902;

uint8_t  P374       _at_ 0xFa00; 
/** 
	* @brief  分别对几个实验根据预编译宏进行初始化  
	* @param  void
  * @retval none
  */
void My82C54Init(void)
{
	/*设置分频*/
	CLK_DIV=0x40;
	/*实验1初始化*/
	#if C54_EXPERIMENT == C54_EXPERIMENT_1
	/*初始化计数器0为分频模式，装载值5（函数内部减去1），为二进制计数*/
			Init_82C54(COUNT_0, FREQUENCY_DIVISION_MODE,5,BINARY_COUNT);
	/*实验2初始化*/
	#elif	C54_EXPERIMENT == C54_EXPERIMENT_2
	/*初始化计数器1，2为方波发生模式两者级联，装载值2000，为二进制计数*/
			Init_82C54(COUNT_1, SQUARE_WAVE_MODE,2000,BINARY_COUNT);
			Init_82C54(COUNT_2, SQUARE_WAVE_MODE,2000,BINARY_COUNT);
	/*实验3初始化*/
	#elif	C54_EXPERIMENT == C54_EXPERIMENT_3
			/*等开关状态变化才进行初始化*/
	#endif


}
/** 
	* @brief  C54初始化  
	* @param  count_x 选择某一个计数器 	counterMode 选择计数模式 countTime 计数时间 codeMode计数方式 BCD或者二进制
  * @retval none
  */
void Init_82C54(uint8_t count_x, uint8_t counterMode, uint16_t countTime,uint8_t codeMode)
{
	uint8_t lowValue=0;
	uint8_t highValue=0;
	uint8_t  initCode=0;
	
	count_x&=0x03;
	counterMode&=0x07;
	initCode = ((count_x << 6) | (counterMode << 1)) | 0X30 | codeMode;
	//先写低位，再写高位，选择二进制计数
	P8254_CTL = initCode;		
	//当为工作方式即方式0时，计数值需要减1
	if(counterMode == INTERRUPT_MODE)			
	{
		countTime -= 1;
	}
	
	lowValue = (countTime & 0XFF);		//取低字节数
	highValue = (countTime >> 8) & 0XFF; 		//取高字节数
	switch(count_x)
	{
		case COUNT_0 :				//对应计数器0
			P8254_0 = lowValue;
			P8254_0 = highValue;
			break;
		
		case COUNT_1 :				//对应计数器1
			P8254_1= lowValue;
			P8254_1 = highValue;
			break;
		
		case COUNT_2 :				//对应计数器2
			P8254_2= lowValue;
			P8254_2 = highValue;
			break;
		
		default:
			
		break;
	}
}
/** 
	* @brief  实验1进行led流水灯 和跑马灯切换 rightShift控制流水灯 timeDelay控制延时时间
	* @param  void
  * @retval none
  */
void EXInterruptLed(void)
{
	static uint16_t timeDelay=0;
	static uint8_t rightShift=0x01;
	timeDelay++;
	if(gParam.c55LedMode==0)
	{
		if(timeDelay<=100)
		{
			P374=0xf0;
		}else if(timeDelay>100&&timeDelay<200)
		{
			P374=0x0f;
		}else
		{
			timeDelay=0;
		}
	}
	else if(gParam.c55LedMode==1)
	{
		
		if(timeDelay>=200)
		{
			timeDelay=0;
			rightShift=(rightShift<<1);
			if(rightShift==0)
			{
				rightShift=0x01;
			}
			P374=~rightShift;
		}
	}
}
/*定义开关输入宏定义*/
#define KEY_VALUE (P1&0x03)
/** 
	* @brief  实验3，判断上一次和这一次读出来开关的值，若相同的话，则直接返回，若不同的话对82C54
进行重新初始化，同时记住这一次的开关值,通过数码管直接显示当前的频率
	* @param  void
  * @retval none
  */
void DiffFangBo(void)
{
	static  xdata lastValue = 0;
	uint8_t key = KEY_VALUE;
	uint16_t xdata countTime1=P8254_0;
	
	if(lastValue==key)
	{	
		return;
	}
	
	if(KEY_VALUE==0)
	{
		Init_82C54(COUNT_0,SQUARE_WAVE_MODE,10,BINARY_COUNT);
		HD7279ShowInt(200000);
	}
	else if(KEY_VALUE==1)
	{
		Init_82C54(COUNT_0,SQUARE_WAVE_MODE,100,BINARY_COUNT);
		HD7279ShowInt(20000);
	}
	else if(KEY_VALUE==2)
	{
		Init_82C54(COUNT_0,SQUARE_WAVE_MODE,1000,BINARY_COUNT);
		HD7279ShowInt(2000);
	}
	else if(KEY_VALUE==3)
	{
		Init_82C54(COUNT_0,SQUARE_WAVE_MODE,10000,BINARY_COUNT);
		HD7279ShowInt(200);
	}
	lastValue = key;
}
/** 
	* @brief  通过预编译宏进行下载
	* @param  void
  * @retval none
  */
void MyExperiment82C54(void)
{
	#if C54_EXPERIMENT == C54_EXPERIMENT_1
		 EXInterruptLed();
	#elif	C54_EXPERIMENT == C54_EXPERIMENT_2
	
	#elif	C54_EXPERIMENT == C54_EXPERIMENT_3
			DiffFangBo();
	#endif



}
