/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO-MINI STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart1.h"

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
		/* USART1 配置模式为 115200 8-N-1，中断接收 */
	USART1_Config();
	
	NVIC_Configuration();

	printf("\r\n 这是一个串口中断接收回显实验 \r\n");	
	printf("\r\n 请在超级终端或者串口调试助手输入字符 \r\n");	

	for(;;)
	{
		
	}
}
/*********************************************END OF FILE**********************/
