
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#include "Lib_Gpio.h"


void main()
	{
    uint16_t x;
    uint16_t y;
    int puissance= 1;

    LibGPIO_Conf(GPIOD, GPIO_Pin_0 | GPIO_Pin_1, GPIO_Mode_IN, GPIO_PuPd_UP, GPIO_Speed_2MHz);
    LibGPIO_Conf(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 , GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_2MHz);

	while (1)
		{

		// TP1
		//Exercice1
		/*
        x=GPIO_ReadInputData(GPIOD);
        //negation
        y=~x;
        GPIO_Write(GPIOE, y);
        */

        /*
        GPIO_Write(GPIOE, 0x01);
        for (t=0;t<1000000;t++);
        GPIO_Write(GPIOE, 0x00);
        for (t=0;t<1000000;t++);


        GPIO_Write(GPIOE, 0x01);
        for (t=0;t<1000000;t++);

        GPIO_Write(GPIOE, 0x02);
        for (t=0;t<1000000;t++);
        */

        //Exercice2

        x= ~GPIO_ReadInputData(GPIOD);
        y=x & 0x0003;

        if ((y==0x0001) && (puissance<=128))       /// Appui sur 1er BP
            {
            puissance= puissance*2;
            }

        if ((y==0x0002) && (puissance>0))     /// Appui sur 2emme BP
            {
            puissance=puissance/2;
            }

        GPIO_Write(GPIOE, puissance-1);

        Lib_delay(300000);
		}
	}
