/****************************HD7279.c***********************/
#include "HD7279.h"
#include "delay.h"
#include "stdio.h"
#include "math.h"

//HD7279显示内容对应数码
unsigned char xdata realCode[] = \
	{0x7e , 0x30 , 0x6d , 0x79 , 0x33 , 0x5b , 0x5f , 0x70 , 0x7f , 0x7b , 0x01 , 0x80 , 0x00 , 0x6f};
//	0		   1		   2		  3		   4		  5	     6		  7		   8	    9		   -		.		  blank	  error

/**
  * @brief	HD7279发送一个字节
  * @note
  * @param	sendData：要发送的数据
  * @param
  * @retval none
  */
void HD7279SendByte(unsigned char sendData)
{
#define SEND_DATA_LENGTH (8)
	unsigned char xdata sendCounter = 0;
	//片选端拉低
	cs=0;
	Delay10Us(12);
	//生成时钟信号并将八位数字依次发送
	for(sendCounter = 0 ; sendCounter < SEND_DATA_LENGTH ; sendCounter++)
	{
		if(sendData & 0x80)
		{
			dat = 1;
		}
		else
		{
			dat = 0;
		}
		//产生一个上升沿
		clk = 1;
		Delay10Us(2);
		//产生一个下降沿
		clk = 0;
		Delay10Us(2);
		sendData<<=1;
	}
	dat = 0;
}

/**
  * @brief	HD7279接收数据
  * @note
  * @param none
  *     @arg
  * @param none
  * @retval ：接受到的一个字节数据
  */
unsigned char HD7279ReceiveByte(void)
{
#define RECEIVE_DATA_LENGTH (8)
	unsigned char xdata receiveCounter  = 0;
	unsigned char xdata receiveData = 0;
	//数据端拉高准备接收数据
	dat = 1;
	Delay10Us(12);
	//生成时钟信号并将八位数字一次接收
	for(receiveCounter = 0 ; receiveCounter < RECEIVE_DATA_LENGTH ; receiveCounter++)
	{
		//产生一个上升沿
		clk = 1;
		Delay10Us(2);
		receiveData*=2;
		if(dat)
		{
			receiveData|=0x01;
		}
		else
		{
		
		}
		clk = 0;
		Delay10Us(2);
	}
	dat = 0;
	return receiveData;
}

//通过HD7279让数码管显示对应内容
/**
  * @brief	数码管显示函数
  * @note
  * @param cmd：命令字
  *     @arg
* @param dataSend:数据字
  * @retval
  */
void HD7279Write(unsigned char cmd , unsigned char dataSend)
{
	HD7279SendByte(cmd);
	
	HD7279SendByte(dataSend);	
}
#define DIGITTAL_TUBE_LENGTH  8  
/** 
	* @brief  HD7279  
	* @param  showValue HD7279需要显示的整型数据	
  * @retval none
  */
void HD7279ShowInt(long showValue)
{
	uint8_t xdata i=0;
	/*通过Springf存储的字符数组*/
	uint8_t xdata myString[DIGITTAL_TUBE_LENGTH]={0};
	/*通过数码管显示字符数组*/
	uint8_t xdata tubeString[DIGITTAL_TUBE_LENGTH]={0};
	/*显示有效位计数*/
	uint8_t xdata dataLength =0;
	/*判断是否在显示范围内，将其转换为字符数串*/
	if(showValue>=-9999999&&showValue<=99999999)
	{
		/*将输入数组转化为字符串*/
		sprintf(myString,"%ld",showValue);
	}
	else
	{
		showValue = 0;
		/*超出最大显示值*/
		for(i=0;i<DIGITTAL_TUBE_LENGTH;i++)
		{
			HD7279Write(UNDECODE+i,0x01);
		}
		return;
	}
	/*计算长度*/
	for(i=0;i<DIGITTAL_TUBE_LENGTH;i++)
	{
		/*有效位计数*/
		if(myString[i]!=0x00)
		{
			dataLength++;
		}
	}
	for(i=0;i<dataLength;i++)
	{
		/*如果是“-”便不管*/
		if(myString[i]=='-')
		{
			tubeString[(DIGITTAL_TUBE_LENGTH - dataLength) + i]=0x01;
		}
		else
		{
			/*ASCII码 0x30 进行赋值   由于将数据转换为字符型数据 由ASCII码表可得0-9的数字的ASCII码减去0x30可得相对应的数字0-9
			填入HD7279显示内容对应数码数组realCode*/
			myString[i]=realCode[(myString[i]-0x30)];
			tubeString[(DIGITTAL_TUBE_LENGTH - dataLength) + i]=myString[i];
		}
	}
	
	for(i=0;i<DIGITTAL_TUBE_LENGTH;i++)
	{
		HD7279Write(UNDECODE+DIGITTAL_TUBE_LENGTH -1 - i,tubeString[i]);
	}


}



/*通过数据提取*/
void HD7279ShowFloat(double showValue)
{
	uint8_t xdata index=0;
	/*通过个人译码*/
	uint8_t xdata myCode[DIGITTAL_TUBE_LENGTH]={0};
	/*通过数码管显示字符数组*/
	uint8_t xdata tubeString[DIGITTAL_TUBE_LENGTH]={0};
	/*确定小数点位置*/
	uint8_t xdata pointIndex = 0;
	/*整数部分*/
	uint32_t xdata showValueInt = (uint32_t)fabs(showValue);
	/*小数部分*/
	double xdata showValueFloat = fabs(showValue) - showValueInt;
	uint32_t xdata getNum=1;
	/*有效数据长度*/
	uint8_t xdata dataLength=0;
	
	
	
	if(showValue<0)
	{
		myCode[dataLength]=10;
		showValue = fabs(showValue);
		dataLength++;
	}
		
	if(showValue>1.f)
	{
		/*获取整数位前有几位*/
		while(showValueInt/getNum)
		{
			getNum =getNum*10;
		}
		getNum=getNum /10;
		
		while(getNum)
		{
			myCode[dataLength]=showValueInt/getNum;
			dataLength++;
			showValueInt%=getNum;
			getNum =getNum/10;
		}
	}
	else
	{
		myCode[dataLength]=0;
		dataLength++;
	}	
	/*得到小数点显示的位数*/	
	pointIndex=dataLength - 1;
	getNum=pow(10,(DIGITTAL_TUBE_LENGTH - dataLength- 1))+1;
	showValueInt = (showValueFloat*getNum*10);

	while(getNum)
	{
		myCode[dataLength]=showValueInt/getNum;
		dataLength++;
		showValueInt %= getNum;
		getNum =getNum/10;
	}
		
	for(index=0;index<DIGITTAL_TUBE_LENGTH;index++)
	{
		tubeString[index]=realCode[myCode[index]];
		if(index == pointIndex)
		{
			tubeString[index]|=realCode[11];
		}
	}
	
	for(index=0;index<DIGITTAL_TUBE_LENGTH;index++)
	{
		
		HD7279Write(UNDECODE+DIGITTAL_TUBE_LENGTH -1 - index,tubeString[index]);
	}

}