  void Init()
  {
      pinMode(point_BallValve_In1,INPUT); 
      pinMode(point_BallValve_In2,INPUT); 
      pinMode(point_BallValve_In3,INPUT); 
      pinMode(point_BallValve_Out4,INPUT); 
      pinMode(point_BallValve_Out5,INPUT); 
      pinMode(point_BallValve_Out6,INPUT); 
      pinMode(Delay_inFWD,OUTPUT); 
      pinMode(Delay_outFWD,OUTPUT);
      pinMode(Delay_inREV,OUTPUT);
      pinMode(Delay_outREV,OUTPUT);
     /*
     * 初始化，进口阀门开到位置3（罐1），出口阀门开到位置4（关闭）
     */
      ValveControl(point_BallValve_In3,Delay_inFWD);//已经打开罐1进口阀门
      ValveControl(point_BallValve_Out4,Delay_outFWD);//已经关闭出水阀门
     /*
     * 触摸屏通讯初始化
     */
      Serial.begin(9600);//设定串口通讯波特率
      Main();//显示触摸屏主页面
     /*
     * SD卡初始化程序
     */
     Init_SD();
      /*
     * 多线程执行初始化，记录初始时间
     */    
      t_TFT= rtc.time();//初始化时，记录首次执行触摸屏刷新的时间点
      TFT_Reload( ); //执行触摸屏刷新
      t_SD= rtc.time(); //初始化时，记录首次SD写入数据的时间点
      SD_Write( );//执行SD卡写入
      t_Stepper= rtc.time();//初始化时，记录首次执行步进电机动作程序
      Stepper_Move();//执行步进电机动作程序
  }
