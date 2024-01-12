#include <easyapc.h>
#include <SoftwareSerial.h>

// RX connection (apc TX) pin 10, TX connection (apc RX) pin 11 and SET connection pin 12
SoftwareAPC apc = SoftwareAPC(10, 11, 12); 

void setup() { 
    // Normal serial opened for printing status of apc operations
    Serial.begin(9600);

    // Startup of APC and then software serial initialisation
    Serial.print(apc.startup());
    apc.s.begin(9600);

    // Activation of SET mode
    Serial.print(apc.setmode());

    // Attempt configuration 
    Serial.print(apc.configure(442, 3, 9, 4, 0));
} 

void loop() {
    delay(200)
    // Waits for Serial Monitor input to confirm status
    if ( Serial.available() > 0) {
        Serial.print(apc.confirm());
    }
}
  