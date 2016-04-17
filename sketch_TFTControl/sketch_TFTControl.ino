//int j=0;
//String Order;
const float targetpress=3.0;//目标套压
const float presentpress=4.0;//当前套压
const int targetflow=2500;//目标瞬流
const int presentflow=2300;//当前瞬流
const unsigned int totalflow=400000;//累计流量
const int dailyflow=10000;//日产气量
const int cycle=600;//采样周期
const float stepRange=0.5;//调节幅度
const int storage=30;//数据存储量
const bool power=0;//供电模式
const float instantLP=4.0;//瞬时产液量
const float totalLP=4.0;//累计产液量
const float previousLP=4.0;//前一日产液量
const int bottleUsed=2;//目前正在进行排液计量的罐
const int valvelift=40;//阀门开度
const float DLPS=10;//日产液量
void setup() 
{
    Serial.begin(9600);
}
void loop() 
{
/*
    Order=Receive_Serial();
    if(Order=="FWD")
    {
          Serial.print("t4.txt=\"forward\"");
          j=j+1;
     }
     else if(Order=="REV")
     {
          Serial.print("t4.txt=\"reverse\"");
          j=j-1;
      }
      else
      {
          Serial.print("");
       }
     off();
    Serial.print("n0.val=");
    Serial.print(j);
    off();*/
    Main_1();
}
void off() //结束代码
{  
      for (int i = 0; i < 3; i++) 
      {
        Serial.write(0xff);
      }
}
/*String Receive_Serial()
{
    String order;
    while(Serial.available()>0)
    {
        order+=char(Serial.read());
        delay(2);
     }
     return order;
 }*/
 /*
  * 主界面1显示
  */
 void Main_1()
 {
      Serial.print("t_targetpress.txt=");
      TFT_InputCharF(targetpress);
      Serial.print("t_presentpress.txt=");
      TFT_InputCharF(presentpress);
      Serial.print("t_presentflow.txt=");
      TFT_InputCharF(presentflow);
      Serial.print("t_valvelift.txt=");
      TFT_InputCharF(valvelift);
      Serial.print("t_DLPS.txt=");
      TFT_InputCharF(DLPS);              
 }
void TFT_InputCharF(float f1)
 {
      Serial.print("\"");
      Serial.print(f1);
      Serial.print("\""); 
      off();
  }
