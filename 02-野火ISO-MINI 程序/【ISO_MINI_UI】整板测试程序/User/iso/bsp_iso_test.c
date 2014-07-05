/**
  ******************************************************************************
  * @file    bsp_iso_test.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ISO ������Գ��� bsp
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "bsp_iso_test.h"
#include "stm32f10x.h"
#include "bsp_ili9341_lcd.h"
#include "bsp_usart1.h"
#include "bsp_i2c_ee.h"
#include "bsp_touch.h"
#include "bsp_led.h" 
#include "bsp_key.h" 
#include "bsp_spi_flash.h"
#include "bsp_dht11.h"
#include "bsp_ds18b20.h"
#include "bsp_ov7725.h"
#include "bsp_adc.h"
#include "bsp_breathing.h" 
//#include "bsp_rda5807m.h"
#include "enc28j60_test.h"
#include "bsp_can.h"
#include "bsp_rtc.h"
//#include "bsp_fsmc_sram.h"
//#include "bsp_fsmc_nor.h"
//#include "bsp_nand.h"
#include "bsp_UsbMassStorage.h"
//#include "mp3.h"
#include "app_ui.h"
#include "bsp_bmp.h"
//#include "bsp_sdfs_app.h"


extern volatile uint8_t rec_cmd;
extern TESTING_STATE testing_state;			//������״̬��־λ��ָʾ�и裬���ڲ��ţ���ͣ��״̬

/*
 * ϵͳ�����λ
 */
void Soft_Reset(void)
{
  __set_FAULTMASK(1);   /* �ر������ж� */  
  NVIC_SystemReset();   /* ϵͳ��λ */
}

static void delay(uint16_t t)
{
	uint8_t i;
	while(t--)
	{
		for(i=0;i<250;i++);
	}
}

/* 
 * ISO ������Բ˵� 
 */
void Test_Menu(void)
{
	printf("\r\n[~~~~~~~~~~~~Ұ�� ISO STM32 ������Գ���~~~~~~~~~~~~~~~]\r\n");
	printf("[------------��ѡ������������������Сд��ĸ----------]\r\n");

	printf("1 - ��ˮ��\r\n");
	printf("2 - ����\r\n");
	printf("3 - EEPROM\r\n");
  printf("4 - RTC(������)\r\n");
  printf("5 - DHT11��ʪ��\r\n");
  printf("6 - DS18b20�¶ȴ�����\r\n");
  printf("7 - ����ͷ(����ov7725)\r\n");
  printf("8 - CAN(Loopback)\r\n");
  printf("9- ������\r\n");
  printf("a - ��̫��ENC28J60\r\n");
  printf("b - Usb-Mass-Storage ����\r\n");
  
  printf("�����������ĸ�������Сд\r\n");
  printf("\r\n");
}


/*
 * ���ݴ��ڲ�ͬ������ִ�в�ͬ�ĳ���
 * �û�Ҳ�������������Ӧ�ĳ���
 */
void Board_Test(void)
{  
  while( 1 )
  {    
		
		
    switch( rec_cmd )
    {
		
			
			case 1:					//����Һ������
      case '1':				//���Դ�������
        printf("���س����ز˵� \r\n");
        printf("ʵ������:LED1 LE2 LED3 ������˸ \r\n");
				Lcd_Note(1);
				LCD_DispEnCh(20,110,"ʵ������:LED1 LE2 LED3 ������˸",BLUE);		
        LED_Test();         
        break;
      
			case 2:
      case '2':
        printf("���س����ز˵� \r\n");
        printf("ʵ������:KEY1����LED1��ת,KEY2����LE2��ת \r\n");
				Lcd_Note(2);
				LCD_DispEnCh(20,110,"ʵ������:KEY1����LED1��ת,KEY2����LE2��ת",BLUE);		
        Key_Test();        
        break;
      
			case 3:
      case '3':
        printf("���س����ز˵� \r\n");
        printf("ʵ������:���ڴ�ӡ��:eeprom��д���Գɹ� \r\n");
				Lcd_Note(3);
        Eeprom_Test();
        break;
      
			case 4:
      case '4':
        printf("���س����ز˵� \r\n");
        printf("ʵ�鲽�� \r\n");
        printf("1-������ʾ�ڴ���������ʱ��\r\n");
        printf("ʵ������:�����������ũ����ʱ���\r\n");
				Lcd_Note(4);
				LCD_DispEnCh(20,110,"ʵ��˵��:��ʼʱ��Ϊ����̶���ʱ��,��������ʾ��ʱ��ÿ�����һ����˵��RTCģ������",BLUE);		

        RTC_Test();
        break;
      
			case 5:
      case '5':
        printf("���س����ز˵� \r\n");
        printf("ʵ�鲽�� \r\n");
        printf("1-��ISO�ϲ���DHT11ģ�� \r\n");
        printf("ʵ������:���ڴ�ӡ��:ʪ��ΪxxxRH,�¶�Ϊxxx�� \r\n");
				Lcd_Note(5);
				LCD_DispEnCh(20,110,"ʵ��˵��:��DHT11ģ����뿪����,����ʱ����Ļ��ʾ��ʪ��",BLUE);		
				DHT11_Test(); 				
		            
        break;
			
			case 6:
      case '6':
        printf("���س����ز˵� \r\n");
        printf("ʵ�鲽�� \r\n");
        printf("1-��ISO�ϲ���DS18b20ģ�� \r\n");
        printf("ʵ������:����ÿ��1s��ӡһ���¶�ֵ��ͬʱled1��˸һ��\r\n");
				Lcd_Note(6);
				LCD_DispEnCh(20,110,"ʵ��˵��:��DS18b20ģ����뿪����,����ʱ����Ļ��ʾ�¶�,ͬʱLED��˸",BLUE);		
				DS18B20_Test(); 
        break;
      
			case 7:
      case '7':
				printf("���س����ز˵� \r\n");
        printf("ʵ�鲽�� \r\n");
        printf("1-��ISO�ϲ�������ͷģ��(����OV7725)\r\n");
        printf("ʵ������:Һ��ʵʱ��ʾ����ͷ�Ļ�����ͼ��\r\n");
				Lcd_Note(7);
				LCD_DispEnCh(20,110,"ʵ��˵��:������ͷģ����뵽ISO��������,����ʱ�Ժ�Һ������ʾ����ͷ�Ļ�����ͼ��,ʹ��Ӳ����λ�˳�",BLUE);		
        delay(0xFFFF);
//				delay(0xFFFF);
//				delay(0xFFFF);
//				delay(0xFFFF);
				Camera_Test();   //���ö������������Ż������
        break;
      
			case 8:
      case '8':
        printf("���س����ز˵� \r\n");
        printf("ʵ������:���ڴ�ӡ��Ϣ:CAN�ػ����Գɹ�ͬʱLED1��LED2��\r\n");
				Lcd_Note(8);
				LCD_DispEnCh(20,110,"ʵ��˵��:CAN�ػ�����,����Ҫ�ⲿ����",BLUE);		
				CAN_Loopback_Test();   
        break;
      
			case 9:
      case '9':
        printf("���س����ز˵� \r\n");
        printf("ʵ������:LED1��PWM�źŵĿ������ں���\r\n");
				Lcd_Note(9);
				LCD_DispEnCh(20,110,"ʵ��˵��:LED1��PWM�źŵĿ������ں���",BLUE);		
        Breathing_Test();  
      
        break;
      
			case 10:
      case 'a':
				printf("���س����ز˵� \r\n");
        printf("ʵ�鲽�� \r\n");
        printf("1-��ISO�ϲ���ENC28J60��̫��ģ�飬��̫��ģ�����������ӵ��Ի���·����\r\n");
        printf("2-��DOSģʽ����������: ping 192.168.1.15 \r\n");
        printf("3-���Ե�IP��ַ���߾������ڵĵ��Ե�IP��ַ������192.168.1.x\r\n  ��������192.168.1.15 \r\n");
        Lcd_Note(10);
				LCD_DispEnCh(20,110,"ʵ��˵��:1-��ISO�ϲ�����̫��ģ��,��̫��ģ�����������ӵ��Ի���·����",BLUE);	
				LCD_DispEnCh(20,160,"2-��DOSģʽ����������: ping 192.168.1.15  (��pingͨ��ʾ����)",BLUE);	
				LCD_DispEnCh(20,193,"3-����IP��ַ���߾������ڵ��Ե�IP��ַ������192.168.1.x",BLUE);	

				ENC28J60_Test(); 
        break;
      
			case 11:
      case 'b': 
				printf("���س����ز˵� \r\n");
        printf("ʵ�鲽��\r\n");
        printf("1-��ISO�ϲ���SD����������С��32GB\r\n");
        printf("2-��microusb�����ӵ��Ժ�ISO�ϵĹ����microusb��(������ usb to uart) \r\n");
        printf("ʵ������:���ڻ��ӡ��:Ұ�� ISO STM32 USB MASS STORAGE ʵ��\r\n         LED1��˸��ͬʱSD�����ڵ�����ģ���һ��U��\r\n");
        Lcd_Note(11);
				LCD_DispEnCh(20,110,"ʵ��˵��:1-��ISO�ϲ���SD����������С��32GB",BLUE);		
				LCD_DispEnCh(20,150,"2-��microusb�����ӵ��Ժ�ISO�ϵĹ����microusb��(������ usb to uart)",BLUE);		
				LCD_DispEnCh(20,195,"����ʱLED1��˸,ͬʱSD�����ڵ�����ģ���һ��U��",BLUE);		
				UsbMassStorage_Test();

        break;		
			
                        
      default:       
        break;
    }
  }
}

/*
 * ��ʼ��Һ�������ڣ���������flash��sd�� * 
 */
void ISO_Init(void)
{
	uint8_t k;
	
  /* Һ����ʼ�����ڴ��ڣ���Ȼ����bug��������ʲôԭ����Ҳ��֪��:( */
  LCD_Init();
  
  USART1_Config();		

	/* ��ʼ��sd���ļ�ϵͳ����Ϊ���ֵ��ֿ������sd������ */
	Sd_fs_init();	

  /* ��ʾ����ͼƬ */
	Lcd_show_bmp(0, 0,"/boardtest/ISO_MINI/ui_boardtest.bmp");
	
	Lcd_List(1);
	
	/* ��ʼ���ⲿFLASH */
	SPI_FLASH_Init();
	//SPI_FLASH_SectorErase(0);
  
	/* ������IO���жϳ�ʼ�� */
	Touch_Init();		
		
		
		/*-------------------------------------------------------------------------------------------------------*/  
		#if 1
		SPI_FLASH_BufferRead(&cal_flag, 0, 1);
		if( cal_flag == 0x55 )
		{
			SPI_FLASH_BufferRead((void*)cal_p, 1, sizeof(cal_p));
			SPI_FLASH_CS_HIGH();
			for( k=0; k<6; k++ )
						printf("\r\n rx = %LF \r\n",cal_p[k]);
		}
		else
		{
			/* �ȴ�������У����� */
			while(Touch_Calibrate() !=0);
		}
		#elif 0
		/* �ȴ�������У����� */
		while(Touch_Calibrate() !=0);
		#endif
	


}


uint8_t key_state = 0;

/* 
 * ISO-MINI �Զ�������� 
 */
void ISO_AutoTest(void)
{
	uint32_t i=0x9ffff;
	uint8_t board_state = 1;
	uint8_t board_test = 0x55;
	
  /* Һ����ʼ�����ڴ��ڣ���Ȼ����bug��������ʲôԭ����Ҳ��֪��:( */
  LCD_Init();
  
	LCD_Clear(0,0,240,320,WHITE);
	
	LCD_DispStr(50,10,"ISO-MINI Auto Detect... ",BLUE);
	
  USART1_Config();			
	
	SysTick_Init();
	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();	
	LED1_ON;
	LED2_ON;
	LED3_ON;
	
	/*����*/
	Key1_GPIO_Config();
  Key2_GPIO_Config();
	
	
	/* EEPROM���� */
	LCD_DispStr(20,40,"1.EEPROM checking...",BLUE);
	/*-----------------------------------------------------------------------------------*/  
  if (EEPROM_AutoTest() == 0) //��
	{
		board_state = 0;	
		LCD_DispStr(20,40,"1.EEPROM check fail!",RED);
	}
	else
	{
		LCD_DispStr(20,40,"1.EEPROM check success!",BLUE);

	}		

	/* FLASH ���� */
	
	LCD_DispStr(20,60,"2.FLASH checking...",BLUE);
	
	if(FLASH_AutoTest() == 0) //��
	{
		board_state = 0;
		LCD_DispStr(20,60,"2.FLASH check fail!",RED);
	}
	else
	{
		LCD_DispStr(20,60,"2.FLASH check success!",BLUE);

	}
	
	/* RTC���� */
	
	LCD_DispStr(20,80,"3.RTC checking...",BLUE);
	
	if(RTC_AutoTest() == 0) //��
	{
		board_state = 0;
		LCD_DispStr(20,80,"3.RTC check fail!",RED);
	}
	else
	{
		LCD_DispStr(20,80,"3.RTC check success!",BLUE);

	}
		
	if(board_state == 0)// ���Բ�ͨ��
	{
			LCD_DispStr(20,200,"Board checking fail!!!",RED);
			while(1);
		}
		
	/* �������� */
	LCD_DispStr(20,100,"4.Please check the key and led ",BLUE);	
		

		
	while(i--)
	{
		/* �������� */
		if(	Key_Scan(GPIOA,GPIO_Pin_0) == KEY_ON)
		{	
				//key_state =~key_state;
				LED1_TOGGLE;
				LED2_TOGGLE;
				LED3_TOGGLE;
			
			}
		
		if(	Key_Scan(GPIOC,GPIO_Pin_13)== KEY_ON)
		{
				//key_state =~key_state;
				LED1_TOGGLE;
				LED2_TOGGLE;
				LED3_TOGGLE;

			}
	}	
	
	/* �ر�systick��ʱ�� ����Ӱ��IIcд��*/
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
	i2c_CheckDevice();
	ee_WriteBytes(&board_test,0x0,1); //�Բ�ɹ���д����
	Soft_Reset();	

}

/* 
 * ISO ������� 
 */
void ISO_Test(void)
{ 
	uint8_t board_test=0;	 

	i2c_CheckDevice();
	delay(0xff); 
	ee_ReadBytes(&board_test, 0x0, 1);
	
	if(board_test != 0x55) //�Լ�δͨ�� 
	{
		ISO_AutoTest();		
	}
	else
	{
		ISO_Init();	
		Test_Menu();
		Board_Test();
	}

	while( 1 ){}
}
/* ---------------------------------------end of file------------------------------------- */
