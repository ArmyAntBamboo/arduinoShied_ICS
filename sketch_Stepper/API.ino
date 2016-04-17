/******************************
      Title：字符串在串口上的处理，用串口控制灯的色度
      Author：zhengguorong
      Time：2014-08-27
      http://www.zhengguorong.com/wordpress/arduino-lesson-3-serial-data-transceiver-and-string-processing/
      *******************************/
      /*
      char buffer[18];    //串口缓冲区的字符数组
      int PinRed = 9;
      int PinYellow = 10;
      int PinBlue = 11;   //分别设定三种灯色对应的引脚，注意引脚必须是PWM~引脚，因为涉及到PWM转换成模拟量输出

      void setup()      //设定串口和引脚模式
      {
        Serial.begin(9600);
        Serial.flush();   //请客串口缓存
        pinMode(PinRed, OUTPUT);
        pinMode(PinYellow, OUTPUT);
        pinMode(PinBlue, OUTPUT);
      }

      void loop()
      {
        if(Serial.available() > 0)      //Serial.available()返回串口收到的字节数
        {
        int index = 0;
        delay(100);             //延时等待串口收完数据，否则刚收到1个字节时就会执行后续程序
        int numChar = Serial.available(); 
        if(numChar > 15)          //确认数据不会溢出，应当小于缓冲大小
        {
          numChar = 15;
        }
        while(numChar--)
        {
          buffer[index++] = Serial.read();  //将串口数据一字一字的存入缓冲
        }
        splitString(buffer);        //字符串分割
        }
      }

      void splitString(char *data)
      {
        Serial.print("Data entered:");
        Serial.println(data);
        char *parameter;
        parameter = strtok(data, " ,");   //string token，将data按照空格或者,进行分割并截取
        Serial.print("***");
        Serial.println(parameter);
        while(parameter != NULL)
        {
        setLED(parameter);
        parameter = strtok(NULL, " ,");   //string token，再次分割并截取，直至截取后的字符为空
        Serial.print("---");
        Serial.println(parameter);      
        }
        for(int x = 0; x < 16; x++)     //清空缓冲
        {
        buffer[x] = '\0';
        }
        Serial.flush();
      }

      void setLED(char *data)
      {
        if((data[0] == 'r') || (data[0] == 'R'))
        {
        int Ans = strtol(data + 1, NULL, 10); //10进制提取数据
        Ans = constrain(Ans, 0, 255);     //限制在0~255范围内
        analogWrite(PinRed, Ans);
        Serial.print("Red is set to :");
        Serial.println(Ans);
        }
        if((data[0] == 'y') || (data[0] == 'Y'))
        {
        int Ans = strtol(data + 1, NULL, 10);
        Ans = constrain(Ans, 0, 255);
        analogWrite(PinYellow, Ans);
        Serial.print("Yellow is set to :");
        Serial.println(Ans);
        }
        if((data[0] == 'b') || (data[0] == 'B'))
        {
        int Ans = strtol(data + 1, NULL, 10);
        Ans = constrain(Ans, 0, 255);
        analogWrite(PinBlue, Ans);
        Serial.print("Blue is set to :");
        Serial.println(Ans);
        }
      }
