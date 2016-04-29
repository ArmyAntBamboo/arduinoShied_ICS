/*
 * 触摸屏通讯程序，接收触摸屏指令，并控制触摸屏显示内容
 * 
 */
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
    if(Order=="Preferences")//参数页选择
    {
        Preferences();
    }
    else if(Order=="Setting")//设置页选择
    {
        Serial.print("page Setting");
        off();
    }
    else if(Order=="LPS")//产液计量选择
    {
        LPS();
    }
    else if(Order=="b_press")//选择定压生产模式
    {
        models=0;
        Setting_1();
    }
    else if(Order=="b_flow")//选择定流量生产模式
    {
        models=1;
        Setting_2();
    }
    else if(Order=="Main")//选择主页面
    {
        Main();
    }
    else if(Order=="b_AddPress")//目标套压增加
    {
        targetpress=targetpress+0.1;
        Setting_1();
    }
    else if(Order=="b_MinusPress")////目标套压减少
    {
        targetpress=targetpress-0.1;
        Setting_1();
    }
    else if(Order=="b_AddFlow")//目标流量增加
    {
        targetflow=targetflow+1;
        Setting_2();
    }
    else if(Order=="b_MinusFlow")//目标流浪减少
    {
        targetflow=targetflow-1;
        Setting_2();
    }
    else if(Order=="b_AddRange")//每小时可调节产量增加
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
    else if(Order=="b_MinusRange")//每小时可调节产量减少
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
    else if(Order=="b_AddCycle")//多次时间执行一次产量调节程序，增加
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
    else if(Order=="b_MinusCycle")//多次时间执行一次产量调节程序，减少
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
      off();
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
      off();
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
      off();
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
      off();
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
      off();
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
      off();
      for(int i=0;i<4;i++)
      {
            Serial.print(str_LPS[i]);
            Serial.print(".txt=");
            TFT_InputCharF(t_LPS[i]);
       }
       Serial.print("t_bottleUsed.txt=");
       Serial.print("\"");
       Serial.print(bottleUsed);
       Serial.print("\"");
       off();
 }
void TFT_InputCharF(float f1)
 {
      Serial.print("\"");
      Serial.print(f1);
      Serial.print("\""); 
      off();
      delay(2);
  }
