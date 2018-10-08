#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "dma.h"	

#define SEND_BUF_SIZE 4096	//发送数据长度,最好等于sizeof(TEXT_TO_SEND)+2的整数倍.

__IO  u16 SendBuff[SEND_BUF_SIZE];	//发送数据缓冲区
//ALIENTEK 探索者STM32F407开发板 实验18
//ADC模数转换实验-库函数版本  
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK

int main(void)
{ 
	
	u16 i;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	LED_Init();					//初始化LED 
	Adc_Init();         //初始化ADC
	MYDMA_Config(DMA2_Stream0,DMA_Channel_0,(u32)&ADC1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA2,STEAM0,CH0,外设为adc1,存储器为SendBuff,长度为:SEND_BUF_SIZE.
	while(1)
	{   
		
		if (USART_RX_STA & 0x8000)
		{
			USART_RX_STA = 0;
			LED1=0;
			LED0=1;
			
			ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
			Get_Adc(ADC_Channel_0);
			
			ADC_DMACmd(ADC1,ENABLE);//使能ADC1的DMA发送    
			MYDMA_Enable(DMA2_Stream0,SEND_BUF_SIZE);         //开始一次DMA传输！	
	//	  delay_ms(100);
			 while(1)
		    {
				if(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0)!=RESET)//等待DMA2_Steam0传输完成
				{ 
					DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);//清除DMA2_Steam0传输完成标志
					break; 
		    }
				}
//			
			ADC_Cmd(ADC1, DISABLE);  //关闭AD转换器	
			DMA_Cmd(DMA2_Stream0, DISABLE);  //关闭DMA传输	
			
			for(i=0;i<SEND_BUF_SIZE;i++)
			{  
//			  printf("%d\r\n",SendBuff[i]);	
				USART_SendData(USART1, SendBuff[i]);
				delay_ms(1);
				while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
				USART_SendData(USART1, SendBuff[i]>>8);
				while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
			delay_ms(1);
			}				
		}
		else
		{
			LED1=1;
			LED0 = !LED0; //闪烁LED,提示系统正在运行.
			delay_ms(200);
		}
	
	}
}



