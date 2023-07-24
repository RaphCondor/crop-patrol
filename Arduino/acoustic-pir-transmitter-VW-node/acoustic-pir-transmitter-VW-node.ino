
#include <VirtualWire.h>



char *pest;
char *none;
 
int ledPin = 13;                // choose the pin for the LED
int sound1 = 4;               // choose the input pin (for PIR sensor)
int sound2 = 5;
int pir1 = 6;
int pir2 = 7;
int pirState = LOW;             // we start, assuming no motion detected
int soundState = HIGH;
int val1 = 0;                    // variable for reading the pin status
int val2 = 0;  
int val3 = 0;  
int val4 = 0;  
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(sound1, INPUT);     // declare sensor as input
  pinMode(sound2, INPUT);
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  
  Serial.begin(9600);

  vw_set_ptt_inverted(true);
  vw_set_tx_pin(12);
  vw_setup(4000);

}
 
void loop(){
  pest="A";
  none="B";

  val1 = digitalRead(sound1);  // read input value
  val2 = digitalRead(sound2);
  val3 = digitalRead(pir1);
  val4 = digitalRead(pir2);
  if (val3 == HIGH || val4 == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      vw_send((uint8_t *)pest, strlen(pest));
      vw_wait_tx();
      delay(2000);
      // We only want to print on the output change, not state
      pirState = HIGH;
    } 
  }
   else if(val1 == LOW || val2 == LOW) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (soundState == HIGH) {
      // we have just turned on
      vw_send((uint8_t *)pest, strlen(pest));
      vw_wait_tx();
      delay(2000);
      // We only want to print on the output change, not state
      soundState = LOW;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (soundState == LOW || pirState == HIGH){
      // we have just turned off
      //Serial.println("No pest present");
      vw_send((uint8_t *)none, strlen(none));
      vw_wait_tx();
      delay(2000);
      // We only want to print on the output change, not state
      soundState = HIGH;
      pirState = LOW;
    }
  }
  } 
  
