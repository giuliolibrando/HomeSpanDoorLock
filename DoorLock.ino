#include "HomeSpan.h"
#include "Doorbell.h"
#include "Lock.h"

int doorbellPin = 15; //input pin from doorbell, the other cable must go to GND
int relayPin = 22;  // choose a pin to control the relay


void setup()
{
  Serial.begin(115200);
  homeSpan.setLogLevel(1); 

  homeSpan.setPairingCode("11122333");
  homeSpan.setQRID("111-22-333");
  homeSpan.setWifiCredentials("WIFI_NAME","WIFI_PASSWORD"); // change credentials

  homeSpan.begin(Category::Other,"Intercom");

  // set pins as dry contact 
  pinMode(relayPin, OUTPUT);         
                
 
  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Name("Doorbell");
    new DoorBell(doorbellPin);

  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Name("Lock Button");
    new DoorLock(relayPin);
      
} // end of setup()

//////////////////////////////////////

void loop()
{
  homeSpan.poll();
  
}
