#include <SPI.h>
#include <SD.h>
#include"Defines.h"
#include <stdio.h>
#include <string.h>
#include <DS1302.h>

void setup() 
{
     Init();//初始化函数
}

/*
 * 多线程执行三个程序
 */
void loop( ) 
{
        tryTFT();// 判断触摸屏是否刷新
        trySD() ;// 判断SD是否写入
        tryStepper() ;// 判断步进电机是否到了执行时间
}
void tryTFT() //触摸屏刷新的执行判断条件
{
        Time t_TFT2= rtc.time();
        uint8_t  x;
        if( t_TFT2.sec-t_TFT.sec>0)
        {
                x=t_TFT2.sec-t_TFT.sec;
         }
         else x=t_TFT2.sec+60-t_TFT.sec;
        if(x < TFT_Every) return; // 时间没到，退出
         t_TFT =  rtc.time();
         TFT_Reload( );  // 时间到了执行事件1，并记录执行时间
}
void TFT_Reload()//TFT重载函数
{
     //Serial.println("event1");
}
void trySD() //SD写入的执行判断条件
{
         Time t_SD2= rtc.time(); 
          uint8_t  x;
         if( t_TFT2.min-t_TFT.min>0)
        {
                x=t_TFT2.min-t_TFT.min;
         }
         else x=t_TFT2.min+60-t_TFT.min;
          if(x < SD_Every) return; // 时间没到，退出
          t_SD= rtc.time(); 
          SD_Write();
}
void  SD_Write()//SD卡写入函数
{
       //Serial.println("event2");
}
void tryStepper() //SD写入的执行判断条件
{
           Time t_Stepper2= rtc.time(); 
            uint8_t  x;
           if(  t_Stepper2.min- t_Stepper.min>0)
          {
                  x= t_Stepper2.min- t_Stepper.min;
           }
           else x= t_Stepper2.min+60- t_Stepper.min;
            if(x < Stepper_Every) return; // 时间没到，退出
            t_Stepper= rtc.time(); 
            Stepper_Move();
}
void  Stepper_Move()//SD卡写入函数
{
       //Serial.println("event2");
}

