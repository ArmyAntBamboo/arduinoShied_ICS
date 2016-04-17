/*
 * 该程序为步进电机控制程序
 * 步进电机型号为两相混合型步进电机，采用MA860H型驱动器
 * 该驱动器通过PUL（脉冲）,DIR（正反）,ENA（使能）三个输入信号控制
 */
#include"Defines.h"

void setup() 
{
    pinMode(PUL,OUTPUT);
    pinMode(DIR,OUTPUT);
    pinMode(ENA,OUTPUT);
    Serial.begin(9600);
}

void loop() 
{
     //StepperControl(PluseCount,HIGH,HIGH);//须在PID控制中修改
     TFT_Communication();
}
void StepperControl(int PluseCount,boolean dirValue,boolean enaValue)
{
     digitalWrite(DIR,dirValue);
     digitalWrite(ENA,enaValue);
     unsigned int i=0;
     for(i=0;i<=PluseCount;i++)
     {
         digitalWrite(PUL,HIGH);
         delay(10);
         digitalWrite(PUL,LOW);
      }
 }

