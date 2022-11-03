float sensor = A1;
float sensorRead = 0;
float x;
float y;
float z;
void setup() {
  Serial.begin(9600);

}

void loop() {
  sensorRead = analogRead(sensor);//由A1的接腳讀取類比訊號
  x=sensorRead/200;
  //z=x/5;
  
  //y=250*((x/5)-1.03)+2.0;
  y=88.8*pow(x,4) - 319.6*pow(x,3) + 441.1*pow(x,2) - 70.1*x - 39.2 -6.41; //y(flow rate)
  if(y > 30){
    y = y-0.8;
  }else if (y <= 30 && y >12){
    y = y-2;
  }else if (y <= 12 && y >4){
    y = y-2.5;
  }else if (y <= 4 && y >= 0){
    y = y-3.3;
  }
  Serial.println(y); //將讀到的數值傳到序列富  
  delay(100);
  
}
