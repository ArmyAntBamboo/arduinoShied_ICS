//int j=0;
float targetpress=3.0;//目标套压
float presentpress=4.0;//当前套压
int targetflow=2500;//目标瞬流
int presentflow=2300;//当前瞬流
unsigned int totalflow=400000;//累计流量
int dailyflow=10000;//日产气量
int cycle=600;//采样周期
float stepRange=0.5;//调节幅度
int storage=30;//数据存储量
bool power=0;//供电模式
float instantLP=4.0;//瞬时产液量
float totalLP=4.0;//累计产液量
float previousLP=4.0;//前一日产液量
int bottleUsed=2;//目前正在进行排液计量的罐
int valvelift=40;//阀门开度
float DLPS=10;//日产液量
boolean models=0;//控制模式，0为定压模式，1为定流量模式
void setup() 
{
    Serial.begin(9600);
    Main();
}
void loop() 
{
    APIs(); 
}
void off() //结束代码
{  
      for (int i = 0; i < 3; i++) 
      {
        Serial.write(0xff);
      }
}
void APIs()
{
    String Order;
    Order=Receive_Serial();
    if(Order=="Preferences")
    {
        Serial.print("page Preferences");
        //Preferences();
    }
    else if(Order=="Setting")
    {
        Serial.print("page Setting");
        off();
    }
    else if(Order=="LPS")
    {
        LPS();
    }
    else if(Order=="b_press")
    {
        models=0;
        Setting_1();
    }
    else if(Order=="b_flow")
    {
        models=1;
        Setting_2();
    }
    else if(Order=="Main")
    {
        Main();
    }
    else if(Order=="b_AddPress")
    {
        targetpress=targetpress+0.1;
        Setting_1();
    }
    else if(Order=="b_MinusPress")
    {
        targetpress=targetpress-0.1;
        Setting_1();
    }
    else if(Order=="b_AddFlow")
    {
        targetflow=targetflow+1;
        Setting_2();
    }
    else if(Order=="b_MinusFlow")
    {
        targetflow=targetflow-1;
        Setting_2();
    }
    else if(Order=="b_AddRange")
    {
        stepRange=stepRange+0.1;
        if(models==0)
        {
            Setting_1();
         }
         else
         {
            Setting_2();
          }
    }
    else if(Order=="b_MinusRange")
    {
          stepRange=stepRange-0.1;
           if(models==0)
          {
              Setting_1();
           }
           else
           {
              Setting_2();
            }
    }
    else if(Order=="b_AddCycle")
    {
          cycle=cycle+10;
          if(models==0)
          {
              Setting_1();
           }
           else
           {
              Setting_2();
            }
    }
    else if(Order=="b_MinusCycle")
    {
          cycle=cycle-10;
          if(models==0)
          {
              Setting_1();
           }
           else
           {
              Setting_2();
            }
    }
    else
    {
        
    }
 }
 /*
  * 判断主界面显示那个的程序
  */
 void Main()
 {
      if(models==0)
      {
          Main_1();
       }
       else
       {
          Main_2();
        }
  }
/*
 * 该程序接受触摸屏及蓝牙等上位机通过串口传递字符串，并返回
 */
String Receive_Serial()
{
    String order;
    while(Serial.available()>0)
    {
        order+=char(Serial.read());
        delay(4);
     }
     return order;
 }
 /*
  * 主界面1显示
  */
 void Main_1()
 {
      float t_main_1[5] ={targetpress,presentpress,presentflow,valvelift,DLPS};
      //定义浮点型数组，用存放显示的数据
      String str_main_1[5]={"t_targetpress","t_presentpress","t_presentflow","t_valvelift","t_DLPS"};
      //定义字符串数组，用来存放在触摸屏上对应的地址
      Serial.print("page Main_1");
      for(int i=0;i<5;i++)
      {
            Serial.print(str_main_1[i]);
            Serial.print(".txt=");
            TFT_InputCharF(t_main_1[i]);
       }
       //for循环，通过串口写入触摸屏            
 }
 /*
  * 主页面2显示
  */
void Main_2()
{
      float t_main_2[5] ={targetflow,presentflow,presentpress,valvelift,DLPS};
      //定义浮点型数组，用存放显示的数据
      String str_main_2[5]={"t_targetflow","t_presentflow","t_presentpress","t_valvelift","t_DLPS"};
      //定义字符串数组，用来存放在触摸屏上对应的地址
      Serial.print("page Main_2");
      for(int i=0;i<5;i++)
      {
            Serial.print(str_main_2[i]);
            Serial.print(".txt=");
            TFT_InputCharF(t_main_2[i]);
       }
 }
void Preferences()
{
      float t_Preferences[10] ={presentpress,targetpress,presentflow,targetflow,totalflow,dailyflow,cycle,stepRange,valvelift,storage};
      //定义浮点型数组，用存放显示的数据
      String str_Preferences[10]={"t_presentpress","t_targetpress","t_presentflow","t_targetflow","t_totalflow","t_dailyflow","t_cycle","t_stepRange","t_valvelift","t_storage"};
      //定义字符串数组，用来存放在触摸屏上对应的地址
      Serial.print("page Preferences");
      for(int i=0;i<10;i++)
      {
            Serial.print(str_Preferences[i]);
            Serial.print(".txt=");
            TFT_InputCharF(t_Preferences[i]);
       }
       Serial.print("bt_power.val=");
       Serial.print(power);
       off();
 }
 void Setting_1()
 {
       float t_Setting_1[4] ={presentpress,targetpress,stepRange,cycle};
      //定义浮点型数组，用存放显示的数据
       String str_Setting_1[4]={"t_presentpress","t_targetpress","t_stepRange","t_cycle"};
      //定义字符串数组，用来存放在触摸屏上对应的地址
      Serial.print("page Setting_1");
      for(int i=0;i<4;i++)
      {
            Serial.print(str_Setting_1[i]);
            Serial.print(".txt=");
            TFT_InputCharF(t_Setting_1[i]);
       }
  }
void Setting_2()
 {
       float t_Setting_2[4] ={presentflow,targetflow,stepRange,cycle};
      //定义浮点型数组，用存放显示的数据
      String str_Setting_2[4]={"t_presentflow","t_targetflow","t_stepRange","t_cycle"};
      //定义字符串数组，用来存放在触摸屏上对应的地址
      Serial.print("page Setting_2");
      for(int i=0;i<4;i++)
      {
            Serial.print(str_Setting_2[i]);
            Serial.print(".txt=");
            TFT_InputCharF(t_Setting_2[i]);
       }
  }
void LPS()
{
      float t_LPS[4] ={DLPS,instantLP,totalLP,previousLP};
      //定义浮点型数组，用存放显示的数据
      String str_LPS[4]={"t_DLPS","t_instantLP","t_totalLP","t_previousLP"};
      //定义字符串数组，用来存放在触摸屏上对应的地址
      Serial.print("page LPS");
      for(int i=0;i<4;i++)
      {
            Serial.print(str_LPS[i]);
            Serial.print(".txt=");
            TFT_InputCharF(t_LPS[i]);
       }
       Serial.print("n_bottleUsed.val=");
       Serial.print(bottleUsed);
       off();
 }
void TFT_InputCharF(float f1)
 {
      Serial.print("\"");
      Serial.print(f1);
      Serial.print("\""); 
      off();
  }
