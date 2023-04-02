
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "Lib_Gpio.h"
#include "stm32f4xx_rtc.h"
#include "Lib_clock.h"
#include "misc.h"
#include "Lib_glcd.h"


void main()
	{
    RTC_TimeTypeDef time1;
    RTC_DateTypeDef date1;
    RTC_AlarmTypeDef alarm1;

    int a=0,h,m,s,ha,ma,sa,ht,mt,st;
    int cheak=0,cmpt=0,on=0;
    uint16_t x,y,hah,mah,sah;

    LibGPIO_Conf(GPIOD, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3, GPIO_Mode_IN, GPIO_PuPd_UP, GPIO_Speed_2MHz);
    LibGPIO_Conf(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 , GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_2MHz);

    time1.RTC_Hours=0x16;
    time1.RTC_Minutes=0x57;
    time1.RTC_Seconds=0x15;
    time1.RTC_H12=0x00;

    date1.RTC_WeekDay=0x01;
    date1.RTC_Month=0x03;
    date1.RTC_Date=0x7;
    date1.RTC_Year=0x23;

    LibClock_Init(CLOCK_SOURCE_LSE,  &date1, &time1, CLOCK_FORCE);

    alarm1.RTC_AlarmDateWeekDay=0;
    alarm1.RTC_AlarmDateWeekDaySel=0;
    alarm1.RTC_AlarmMask=RTC_AlarmMask_DateWeekDay ;
    alarm1.RTC_AlarmTime.RTC_H12=0x00;
    alarm1.RTC_AlarmTime.RTC_Hours=0x16;
    alarm1.RTC_AlarmTime.RTC_Minutes=0x57;
    alarm1.RTC_AlarmTime.RTC_Seconds=0x20;


    LibClock_SetAlarm(RTC_Alarm_A, &alarm1);

    GLCD_InitDisplay();
    GLCD_ClearScreen();
    GLCD_Move(0,3,3);

    //Affichage d'alarm avant modification
    ha=BcdToDec(alarm1.RTC_AlarmTime.RTC_Hours);
    ma=BcdToDec(alarm1.RTC_AlarmTime.RTC_Minutes);
    sa=BcdToDec(alarm1.RTC_AlarmTime.RTC_Seconds);

    GLCD_Move(0,0,0);  ///affichage
    GLCD_Write("<<");
    if(ha<10) GLCD_Write("0");
    GLCD_ShowInt(ha);
    GLCD_Write(":");
    if(ma<10) GLCD_Write("0");
    GLCD_ShowInt(ma);
    GLCD_Write(":");
    if(sa<10) GLCD_Write("0");
    GLCD_ShowInt(sa);
    GLCD_Write(">>");
    GLCD_Write(" ");

	while (1)
		{
		x= ~GPIO_ReadInputData(GPIOD);
        y=x & 0x000b;

        LibClock_GetTime( &time1);

        h=BcdToDec(time1.RTC_Hours);
        m=BcdToDec(time1.RTC_Minutes);
        s=BcdToDec(time1.RTC_Seconds);

        GLCD_Move(0,3,3);

        GLCD_Write("<<");
        if(h<10) GLCD_Write("0");
        GLCD_ShowInt(h);
        GLCD_Write(":");
        if(m<10) GLCD_Write("0");
        GLCD_ShowInt(m);
        GLCD_Write(":");
        if(s<10) GLCD_Write("0");
        GLCD_ShowInt(s);
        GLCD_Write(">>");
        GLCD_Write(" ");


        if ((LibClock_OnAlarm(RTC_Alarm_A)==1) && (a==0))
            {
            a=1;
            GPIO_Write(GPIOE, 0x01);
            }

        if((y==0x0001) && (on==0) ) ///Button 1
            {
            if (cmpt==0)
                {
                ht = ha;
                mt = ma;
                st = sa;
                }
            cmpt++;
            if(cmpt > 3)
            {
            cmpt=0;
            on=1;
            }
            Lib_delay(500000);
            }

        if(y==0x0002) ///Button 2
            {
            switch (cmpt)
                {
                case 1 :
                    {
                    ht++;
                    if (ht > 23) ht=0;
                    Lib_delay(300000);
                    break;
                    }
                case 2 :
                    {
                    mt++;
                    if (mt > 59) mt=0;
                    Lib_delay(300000);
                    break;
                    }
                case 3 :
                    {
                    st++;
                    if (st > 59) st=0;
                    Lib_delay(300000);
                    break;
                    }
                }
            }

       if(y==0x0008) ///Button 3
            {
            GPIO_Write(GPIOE, 0x00);

            }

        if(cmpt == 1)
            {
            GLCD_Move(0,0,0);  ///affichage
            GLCD_Write("<<");

            if(ht<10) GLCD_Write("0");
            GLCD_ShowInt(ht);
            GLCD_Write(":");
            if(mt<10) GLCD_Write("0");
            GLCD_ShowInt(mt);
            GLCD_Write(":");
            if(st<10) GLCD_Write("0");
            GLCD_ShowInt(st);
            GLCD_Write(">>");
            GLCD_Write(" ");
            GLCD_Move(0,1,10);
            GLCD_Write("__");
            GLCD_Move(0,1,25);
            GLCD_Write("  ");
            }

        if(cmpt == 2)
            {
            GLCD_Move(0,0,0);  ///affichage
            GLCD_Write("<<");
            if(ht<10) GLCD_Write("0");
            GLCD_ShowInt(ht);
            GLCD_Write(":");
            if(mt<10) GLCD_Write("0");
            GLCD_ShowInt(mt);
            GLCD_Write(":");
            if(st<10) GLCD_Write("0");
            GLCD_ShowInt(st);
            GLCD_Write(">>");
            GLCD_Write(" ");
            GLCD_Move(0,1,25);
            GLCD_Write("__");
            GLCD_Move(0,1,10);
            GLCD_Write("  ");
            }

        if(cmpt == 3)
            {
            GLCD_Move(0,0,0);  ///affichage
            GLCD_Write("<<");
            if(ht<10) GLCD_Write("0");
            GLCD_ShowInt(ht);
            GLCD_Write(":");
            if(mt<10) GLCD_Write("0");
            GLCD_ShowInt(mt);
            GLCD_Write(":");
            if(st<10) GLCD_Write("0");
            GLCD_ShowInt(st);
            GLCD_Write(">>");
            GLCD_Write(" ");
            GLCD_Move(0,1,40);
            GLCD_Write("__");
            GLCD_Move(0,1,25);
            GLCD_Write("  ");
            }
        if(on == 1)
            {
            hah=DecToBcd(ht);
            mah=DecToBcd(mt);
            sah=DecToBcd(st);
            alarm1.RTC_AlarmDateWeekDay=0;
            alarm1.RTC_AlarmDateWeekDaySel=0;
            alarm1.RTC_AlarmMask=RTC_AlarmMask_DateWeekDay ;
            alarm1.RTC_AlarmTime.RTC_H12=0x00;
            alarm1.RTC_AlarmTime.RTC_Hours=hah;
            alarm1.RTC_AlarmTime.RTC_Minutes=mah;
            alarm1.RTC_AlarmTime.RTC_Seconds=sah;
            LibClock_SetAlarm(RTC_Alarm_A, &alarm1);
            LibClock_SetAlarm(RTC_Alarm_A, NULL);
            }

        Lib_delay(30000);
		}
	}
