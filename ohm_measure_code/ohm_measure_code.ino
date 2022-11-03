#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);   
int Vin=5;        
float Vout=0;     
float R1=300000;    
float R2=0;      
int a2d_data=0;    
float buffer=0;            
void setup() 
{
 lcd.begin(16,2);
 Serial.begin(9600);
}
void loop()
{
  a2d_data=analogRead(A0);
  if(a2d_data)
  {
    buffer=a2d_data*Vin;
    Vout=(buffer)/1024.0;
    buffer=Vout/(Vin-Vout); 
    R2=R1*buffer;
    lcd.setCursor(4,0);
    lcd.print("ohm meter");
    lcd.setCursor(0,1);
    lcd.print("R (ohm)=");
    //lcd.print(R2);
    lcd.print(R2/1000);
    lcd.print("K");
    Serial.println(R2/1000);
    //Serial.println(R2);
    delay(100);
  }
}
