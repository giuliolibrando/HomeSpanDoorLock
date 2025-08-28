#include "HomeSpan.h"
#include "Doorbell.h"
#include "Lock.h"

int doorbellPin = 12; // input pin from doorbell, the other cable must go to GND
int relayPin = 13;  // choose a pin to control the relay
int openTime = 3000; // time in ms the lock should remain open before auto-closing

DoorLock *doorlock; // define doorlock globally to be able to reference it in void loop
unsigned long unlockTime = 0; // variable to store time when doorlock was opened

void setup()
{
  Serial.begin(115200);

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
    doorlock=new DoorLock(relayPin);

} // end of setup()

//////////////////////////////////////

void loop()
{
  homeSpan.poll();

  if(doorlock->current->getVal() == 0){ // 0 means that doorlock is open
    if(unlockTime == 0){ // save current time if not already set
      unlockTime = millis();
    }

    if(millis() - unlockTime >= openTime){ // when openTime amount of milliseconds passed, lock again
      doorlock->target->setVal(1); // 1 means that doorlock should lock
      doorlock->update();
      unlockTime = 0; // reset to 0 as doorlock is now locked
    }

  }else if(unlockTime != 0){ // if door was locked manually before openTime had passed, reset saved unlock time
    unlockTime = 0;
  }
}
