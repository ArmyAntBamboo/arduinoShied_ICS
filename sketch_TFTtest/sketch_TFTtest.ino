int j=0;
String Order;
void setup() 
{
    Serial.begin(9600);
}
void loop() 
{
    /*j=j+1;
    Serial.print("n0.val=");
    Serial.print(j);
    off();*/
    //delay(1000);
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
    off();
}
void off() //结束代码
{  
      for (int i = 0; i < 3; i++) 
      {
        Serial.write(0xff);
      }
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
