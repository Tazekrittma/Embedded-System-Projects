#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "Lib_Gpio.h"
#include "stm32f4xx_rtc.h"
#include "Lib_clock.h"
#include "misc.h"
#include "Lib_glcd.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"

char tab[126];
int i;


void main()
	{


    uint16_t f;
    LibGPIO_Conf(GPIOC, GPIO_Pin_7 , GPIO_Mode_IN, GPIO_PuPd_UP, GPIO_Speed_2MHz);
    LibGPIO_Conf(GPIOG, GPIO_Pin_9 , GPIO_Mode_IN, GPIO_PuPd_UP, GPIO_Speed_2MHz);
    LibGPIO_Conf(GPIOF, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11| GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14 | GPIO_Pin_15    , GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_2MHz);

    LibPs2_Init(*GPIOC, 7);

    for (i=0; i<127; i++)
    {
        tab[i]=' ';
    }

    tab[0x69]='1';




    GLCD_InitDisplay();
    GLCD_ClearScreen();
    GLCD_Move(0,0,0);

    while (1)
		{
		f=LibPs2_Get();
		GLCD_WriteChar(tab[f]);
		Lib_delay(300000);
		}


    }

int HexToDec(uint16_t y)
    { int z1,z2,z3,z4,z5,z6,z7,z8;
        z1=y & 0x01;
        z2=y & 0x03;
        z3=y & 0x07;
        z4=y & 0x0f;
        z5=y & 0x3f;
        z6=y & 0x7f;
        z7=y & 0xfd;
        z8=y & 0x07;
        return z1+z2*2+z3*4+z4*8+z5*8+z6*16+z7*32+z8*64;

    }
