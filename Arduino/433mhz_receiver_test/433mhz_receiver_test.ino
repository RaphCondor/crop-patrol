// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

String pest,disease,total;
 
void setup()
{
    // Initialize ASK Object
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);
}
 
void loop()
{
    // Set buffer to size of expected message
    uint8_t buf[1];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
   if(rf_driver.recv(buf, &buflen)){
    if ((char*)buf == "A" || (char*)buf == "B")
    {
      pest = (char*)buf;  
      delay(2000);       
      
    }
    if((char*)buf == 'C' || (char*)buf == 'D'){
      disease = (char*)buf;
      delay(2000);
    }
    String total = pest + disease;
    Serial.println((char*)buf);
   }

    


    
}
