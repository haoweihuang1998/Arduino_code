#include <LiquidCrystal.h> 

// declare airflow variables
float sensor = A1;
float sensorRead = 0;
float x;
float y;
float z;
float max_flow = 0.0, min_flow = 0.0;

// declare lcd variables
// LCD 接腳: RS, Enable, D4, D5, D6, D7 
// Arduino 接腳: 12, 11, 5, 4, 3, 2
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// declase button variabls
const int button1 = 7;
const int button2 = 8;
int button1State = 0;
int button2State = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2); // 初始化 LCD，一行 16 的字元，共 2 行，預設開啟背光
  // Print a message to the LCD
  lcd.setCursor(0, 0);  // set to the head of first row
  lcd.print("airflow");
  lcd.setCursor(0, 1);  // set to the head of second row
  lcd.print("measurement");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);  // set to the 6th char of first row
  lcd.print("max: ");
  lcd.print(max_flow);
  lcd.setCursor(0, 1);  // set to the 6th char of second row
  lcd.print("min: ");
  lcd.print(min_flow);

  // set pin mode of button as input
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  
  // set up baud rate of Arduino board
  Serial.begin(9600);

}

void loop() {
  // read the analog signal
  sensorRead = analogRead(sensor);//由A1的接腳讀取類比訊號
  x=sensorRead/100;
  z=x/5;

  // convert the signal to airflow rate
  y=250*((x/5)-1.03)+2.0;
  Serial.println(y);//將讀到的數值傳到序列埠  y (flow rate) = 50x (output voltage) - 25

  // compare max and min
  button1State = digitalRead(button1);  // get button1 state
  if (button1State == HIGH) {
    if ((y-max_flow) > 0) {
      max_flow = y;
      // print the max & min airflow value on the LCD
      lcd.setCursor(5, 0);  // set to the 6th char of first row
      lcd.print(max_flow);
      }
    if ((min_flow-y) > 0) {
      min_flow = y;
      lcd.setCursor(5, 1);  // set to the 6th char of second row
      lcd.print(min_flow);
      }
  }

  // reset max_flow & min_flow
  button2State = digitalRead(button2);  // get button2 state
  if (button2State == LOW) {
    max_flow = 0.0;
    min_flow = 0.0;
    button2State = 0;
    lcd.clear();
    lcd.setCursor(0, 0);  // set to the 6th char of first row
    lcd.print("max: ");
    lcd.print(max_flow);
    lcd.setCursor(0, 1);  // set to the 6th char of second row
    lcd.print("min: ");
    lcd.print(min_flow);
  }
  
  delay(100);
  
}
