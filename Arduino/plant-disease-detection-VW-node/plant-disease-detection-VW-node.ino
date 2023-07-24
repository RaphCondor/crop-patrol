/***************************************************************************
  This is a library for the AMG88xx GridEYE 8x8 IR camera

  This sketch tries to read the pixels from the sensor

  Designed specifically to work with the Adafruit AMG88 breakout
  ----> http://www.adafruit.com/products/3538

  These sensors use I2C to communicate. The device's I2C address is 0x69

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <VirtualWire.h>


char *disease;
char *none;

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

void setup() {
    Serial.begin(9600);
    //Serial.println(F("AMG88xx pixels"));

    bool status;
    
    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
        while (1);
    }
    
    //Serial.println("-- Pixels Test --");

    //Serial.println();

    delay(100); // let sensor boot up

    vw_set_ptt_inverted(true);
    vw_set_tx_pin(12);
    vw_setup(4000);
}

boolean state = LOW;

void loop() { 

    disease = "C";
    none = "D";
  
    //read all the pixels
    amg.readPixels(pixels);
    double sum = 0.00;
    double average = 0.00;

    for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
      sum = pixels[i-1] + sum;
      
    }
    average = sum/64;
    //Serial.println(sum);
    //Serial.println(average);

    //delay a second
    if (average > 30.1) {            // check if the input is HIGH
    if (state == LOW) {
      // we have just turned on
      vw_send((uint8_t *)disease, strlen(disease));
      vw_wait_tx(); // Wait until the whole message is gone
      delay(2000);
      Serial.println(average);
      // We only want to print on the output change, not state
      state = HIGH;
    } 
    }
    else {
    if (state == HIGH){
      vw_send((uint8_t *)none, strlen(none));
      vw_wait_tx(); // Wait until the whole message is gone
      delay(1000);
      Serial.println("D");
      state = LOW;
    }
  }
  
}
