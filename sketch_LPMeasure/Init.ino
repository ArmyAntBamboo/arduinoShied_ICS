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
  }
