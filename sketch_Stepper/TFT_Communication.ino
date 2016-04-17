/*
 * 
 */
String Order;
void TFT_Communication()
{
    Order=Receive_Serial();
    APIs_Test(Order);
 }
String Receive_Serial()
{
    String order;
    while(Serial.available()>0)
    {
        order+=char(Serial.read());
        delay(2);
     }
     return order;
 }
 void APIs_Test(String order)
 {
      Serial.print("t4.txt=order");
      off();
      if(order=="FWD")
      {
          Serial.print("t4.txt=\"正转\"");
       }
       if(order=="REV")
      {
          Serial.print("t4.txt=反转");
       }
       Serial.print("n0.val=4.0");
  }
  void off() //结束代码
  {  
      for (int i = 0; i < 3; i++) 
      {
        Serial.write(0xff);
      }
}

