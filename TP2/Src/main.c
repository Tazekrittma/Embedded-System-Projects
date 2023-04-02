

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "Lib_Gpio.h"


void main()
	{
	uint16_t x,y;	int i=0, cheak=0;

    LibGPIO_Conf(GPIOD, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3, GPIO_Mode_IN, GPIO_PuPd_UP, GPIO_Speed_2MHz);
    LibGPIO_Conf(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 , GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_2MHz);
    LibGPIO_Conf(GPIOF, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 , GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_2MHz);

    GLCD_InitDisplay();
    GLCD_ClearScreen();
    GLCD_Move(0,0,0);
    GLCD_Write("Decompte");

    GLCD_Move(0,3,0);
    GLCD_Write("0");

	while (1)
		{
        x= ~GPIO_ReadInputData(GPIOD);
        y=x & 0x000b;

        if(y==0x0001)  ///Button1
            {
            i++;
            GLCD_Move(0,3,0);
            GLCD_ShowInt(i);
            GLCD_Write(" ");
            Lib_delay(300000);
            }

        if(y==0x0002) ///Button 2
            {
            i--;
            GLCD_Move(0,3,0);
            GLCD_ShowInt(i);
            GLCD_Write(" ");
            Lib_delay(900000);
            }

        if((y==0x0008) && (i>0) )  ///Button 3
            {
            cheak=!cheak;
            Lib_delay(900000);
            }

        if  ((cheak)&& (i>0))
            {
            i--;
            GLCD_Move(0,3,0);
            GLCD_ShowInt(i);
            GLCD_Write(" ");
            Lib_delay(900000);
            }

        if ((i==0) && (cheak))
            {
            GPIO_Write(GPIOE, 0x01);
            }
        }
    }
