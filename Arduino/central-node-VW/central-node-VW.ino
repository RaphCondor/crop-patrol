#include <VirtualWire.h>// LED's
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <Wire.h> // Library for I2C communication

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,16,2) for 16x2 LCD.
char Sensor1CharMsg[1];
void setup() {
  Serial.begin(9600);
  vw_set_ptt_inverted(true); 
  vw_set_rx_pin(11);
  vw_setup(4000);
  vw_rx_start();  
  pinMode(3,OUTPUT);
  pinMode(6,OUTPUT);  
  lcd.init();
  lcd.backlight();   
} // END void setup

void loop(){
    lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
    lcd.print("CROPATROL"); // Print the string "Hello World!"
    lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
    lcd.print("Number of Pests: 21"); // Print the string "Hello World!"
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen))
    {        
     for ( int i=0;i<buflen;i++)
       {   
         Sensor1CharMsg[i] = char(buf[i]);
          }
//          
          for(int i=0;i<buflen;i++){ 
          Serial.print(Sensor1CharMsg[i]); 
          }
          if(Sensor1CharMsg[0] == 'A'){
            digitalWrite(3,HIGH);
            lcd.clear();
            lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
            lcd.print("CROPATROL"); // Print the string "Hello World!"
            lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
            lcd.print("Pest Detected"); // Print the string "Hello World!"
            lcd.setCursor(0,2);
            lcd.print("Detected at Area 1");
            digitalWrite(9,HIGH);
            delay(5000);
          }
          
          if(Sensor1CharMsg[0] == 'B'){
            digitalWrite(3,LOW);
            lcd.clear();
            lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
            lcd.print("CROPATROL"); // Print the string "Hello World!"
            lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
            lcd.print("Field Clear"); // Print the string "Hello World!"
            digitalWrite(9,LOW);
          }
          
          if(Sensor1CharMsg[0] == 'C'){
            digitalWrite(6,HIGH);
            lcd.clear();
            lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
            lcd.print("CROPATROL"); // Print the string "Hello World!"
            lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
            lcd.print("Disease Detected"); // Print the string "Hello World!"
            lcd.setCursor(0,2);
            lcd.print("Detected at Area 1");
             digitalWrite(9,HIGH);
            delay(5000);
          }
          
          if(Sensor1CharMsg[0] == 'D'){
            digitalWrite(6,LOW);
            lcd.clear();
            lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
            lcd.print("CROPATROL"); // Print the string "Hello World!"
            lcd.setCursor(0, 1); // Set the cursor on the first column and first row.
            lcd.print("Field Clear"); // Print the string "Hello World!"
            digitalWrite(9,LOW);
          }

     
  Serial.print("\n");
  delay(200);
}
digitalWrite(3,HIGH);
}
