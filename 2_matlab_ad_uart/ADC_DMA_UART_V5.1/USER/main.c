#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "dma.h"	

#define SEND_BUF_SIZE 4096	//�������ݳ���,��õ���sizeof(TEXT_TO_SEND)+2��������.

__IO  u16 SendBuff[SEND_BUF_SIZE];	//�������ݻ�����
//ALIENTEK ̽����STM32F407������ ʵ��18
//ADCģ��ת��ʵ��-�⺯���汾  
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

int main(void)
{ 
	
	u16 i;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
	Adc_Init();         //��ʼ��ADC
	MYDMA_Config(DMA2_Stream0,DMA_Channel_0,(u32)&ADC1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA2,STEAM0,CH0,����Ϊadc1,�洢��ΪSendBuff,����Ϊ:SEND_BUF_SIZE.
	while(1)
	{   
		
		if (USART_RX_STA & 0x8000)
		{
			USART_RX_STA = 0;
			LED1=0;
			LED0=1;
			
			ADC_Cmd(ADC1, ENABLE);//����ADת����	
			Get_Adc(ADC_Channel_0);
			
			ADC_DMACmd(ADC1,ENABLE);//ʹ��ADC1��DMA����    
			MYDMA_Enable(DMA2_Stream0,SEND_BUF_SIZE);         //��ʼһ��DMA���䣡	
	//	  delay_ms(100);
			 while(1)
		    {
				if(DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0)!=RESET)//�ȴ�DMA2_Steam0�������
				{ 
					DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);//���DMA2_Steam0������ɱ�־
					break; 
		    }
				}
//			
			ADC_Cmd(ADC1, DISABLE);  //�ر�ADת����	
			DMA_Cmd(DMA2_Stream0, DISABLE);  //�ر�DMA����	
			
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
			LED0 = !LED0; //��˸LED,��ʾϵͳ��������.
			delay_ms(200);
		}
	
	}
}



