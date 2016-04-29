/*
 产量量计量程序
该程序通过称重传感器测量桶内液体质量，来判断桶有没有满，当桶内液体满之后，切换到另一个桶内
通过两个桶的交替进液和排液，从而计算出了液体体积，最后也实现了计量流量

由Army-Ant技术服务公司Bamboo编写
QQ:997876984
于2016年4月9日完成
可以转载或者使用，但请说明程序出处
 */
/*
 * 定义两个变量，用来存储传感器读出来的数据
 */
 int sensorValue1 = 0;
 int sensorValue2 = 0; 
 float weight1=0;//桶1液体的重量
 float weight2=0;//桶2液体的重量
 //float totalLP=0;//产液量，即累计流量。必须申明为全局变量，最大计量到43万方
 unsigned long T1=0;
 unsigned long T2=0;
 //float instantLP=0;//瞬时产液量
float LPMeasure()
{
      sensorValue1 = analogRead(Sensor1);
      sensorValue2 = analogRead(Sensor2);//读取到数字是0-1023的数字，需要转化成重量
      weight1=sensorValue1/1023*sensorFS;//将传感器值转换为实际测量的重量
      weight2=sensorValue2/1023*sensorFS;
     /*
     * 每满一罐，就进行排液，同时另一个罐进行储液
     */
      if(weight1>=weightFull&&weight2<=weightEmpty)
      {
          T1=millis();//记录桶1满切换到桶2时的时间点，单位ms
          change(1,2);//当1满，2排空时进行换罐
          totalLP=totalLP+PerVolume;//每次计量液量
      }
      if(weight2>=weightFull&&weight1<=weightEmpty)
      {
          T2=millis();//记录桶2满切换到桶1时的时间点，单位ms
          change(2,1);//当2满，1排空时进行换罐
          totalLP=totalLP+PerVolume;//每次计量液量
       }
       instantLP=PerVolume*0.001*3600*1000/(T1-T2);//瞬时产液量，单位：方/小时
}
  /*
 * 进行倒换罐进行储液程序
 * 当1在进液的时候，2在排液。2在进液的时候1在排液
 */
void change(int From,int To)
{
   if(From==1&&To==2)
   {
        ValveControl(point_BallValve_In2,Delay_inREV);//向罐2进液
        ValveControl(point_BallValve_Out5,Delay_outFWD);//罐1开始排液
    }
    else
    {
        ValveControl(point_BallValve_In3,Delay_inFWD);//向罐1进液
        ValveControl(point_BallValve_Out6,Delay_outREV);//罐2开始排液
    }
}
 /*
 * ValveControl阀门开关控制程序
 * 控制继电器Delay将阀门开到Point位置，并停止旋转
 */
void ValveControl(int Point,int Delay)
{
   do{
        digitalWrite(Delay,HIGH);
    } while(digitalRead(Point)==1);
    digitalWrite(Delay,LOW);
}
