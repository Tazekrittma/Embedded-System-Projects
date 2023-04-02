
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#include "Lib_Gpio.h"


void main()
	{
    uint16_t x;
    uint16_t y;
    long t;
    long somme=0;

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

        if(y==0x0001)       /// Appui sur 1er BP
            {
            if (somme < 8)
                {
                somme++;
                }
            }

        if(y==0x0002)       /// Appui sur 2emme BP
            {
            if (somme > 0)
                {
                somme--;
                }
            }


        switch(somme)
            {
            case 0: GPIO_Write(GPIOE, 0x0000); break;
            case 1: GPIO_Write(GPIOE, 0x0001); break;
            case 2: GPIO_Write(GPIOE, 0x0003); break;
            case 3: GPIO_Write(GPIOE, 0x0007); break;
            case 4: GPIO_Write(GPIOE, 0x000f); break;
            case 5: GPIO_Write(GPIOE, 0x001f); break;
            case 6: GPIO_Write(GPIOE, 0x003f); break;
            case 7: GPIO_Write(GPIOE, 0x007f); break;
            case 8: GPIO_Write(GPIOE, 0x00ff); break;
            }

        Lib_delay(300000);
		}
	}
