/*
 * 485通讯
 * 该实例实现modbus主机向从机发送03功能码
 * 并读取从机发回的数据存入数组
 */
#define SIZE 30//从机响应帧存储数组的大小
#define DelayTime 5 //等待3.5字节以上时间
unsigned char frame[SIZE];//从机响应帧
unsigned long SumProduction=0;//总产量计算
float bkflow=0;//标况流量
float gkflow=0;//工况流量
void setup()
{
    Serial.begin(9600);
    Serial.flush();
    modbusRTUmasterWrite(2,3,0x0000,0x0001);
    delay(5);
    modbusRTUmasterRead();
    while(!(frame[2]==0x02&&frame[3]==0x00&&frame[3]==0x00))
    {
        modbusRTUmasterRead();
        delay(5);
        modbusRTUmasterWrite(2,3,0x0000,0x0001);
     }
 }
void loop()
{
    modbusRTUmasterWrite(2,3,0x0001,0x000b);
    delay(5);
    modbusRTUmasterRead();
}
void modbusRTUmasterWrite(unsigned char slaveID,unsigned char function,int startData,int ReadNum)
{
      unsigned char Writeframe[8];//主机请求帧
      unsigned int crc16;  //校验位
      Writeframe[0]=slaveID;  //设定站号
      Writeframe[1]=function;  //设定功能码
      Writeframe[2] = startData >> 8;  //读寄存器的起始地址
      Writeframe[3] = startData & 0xFF;             
      Writeframe[4] = ReadNum>> 8;  //读寄存器的个数
      Writeframe[5] = ReadNum & 0xFF;
      crc16 = calculateCRC(&Writeframe[0],6);  //计算校验值
      Writeframe[6] = crc16 >> 8;  //填写校验位
      Writeframe[7] = crc16 & 0xFF;
      Serial.write(&Writeframe[0],8); 
}
void modbusRTUmasterRead()
 {
      unsigned char frame[SIZE];//保存接收的数据
      unsigned int i=0;
      unsigned int crc16;  //校验位
      while(Serial.available()>0)
      {
           if(i<SIZE)
           {
                frame[i]=Serial.read();
                i++;
            }
            else
            {
                 Serial.read();
             }
       delay(DelayTime);//等待3.5个字节以上时间
       if(Serial.available()==0)
       {
             if(frame[0]==2)//看看是哪个设备发送来的信息
             {
                   crc16 = ((frame[i-2]<<8) | frame[i-1]);//crc检验码
                   if(calculateCRC(&frame[0],i-2)==crc16)  //数据校验通过,进入条件
                   {
                        unsigned char function=frame[1];  //读取功能码
                        if(function==3)//功能码03
                        {
                             unsigned int num=frame[2];//总字节数
                             for(int j=3;j<8;j++)
                             {
                                  SumProduction=SumProduction*100+frame[j];
                              }
                             for(int j=9;j<=12;j++)
                             {
                                  bkflow=bkflow*100+frame[j]*0.01;
                              }
                              for(int j=13;j<=16;j++)
                             {
                                  gkflow=gkflow*100+frame[j]*0.01;
                              }
                         }
                    }
              }
        }
     }
       
  }
//CRC校验函数
//参数1:待校验数组的起始地址
//参数2:待校验数组的长度
//返回值CRC校验结果,16位,低字节在前
unsigned int calculateCRC(unsigned char* _regs,unsigned char arraySize) 
{
  unsigned int temp, temp2, flag;
  temp = 0xFFFF;
  for (unsigned char i = 0; i < arraySize; i++)
  {
    temp = temp ^ *(_regs+i);
    for (unsigned char j = 1; j <= 8; j++)
    {
      flag = temp & 0x0001;
      temp >>= 1;
      if (flag)
        temp ^= 0xA001;
    }
  }
  temp2 = temp >> 8;
  temp = (temp << 8) | temp2;
  temp &= 0xFFFF; 
  return temp; 
}


