struct DoorLock : Service::LockMechanism {     // Door LockMechanism

  SpanCharacteristic *current;            // reference to the Current Door State Characteristic
  SpanCharacteristic *target;             // reference to the Target Door State Characteristic

  int lockPin;

  DoorLock(int relayPin) : Service::LockMechanism(){       // constructor() method

    lockPin = relayPin;

    current=new Characteristic::LockCurrentState(1);              // initial value of 1 means closed
    target=new Characteristic::LockTargetState(1);                // initial value of 1 means closed

    Serial.print("Configuring Door LockMechanism");   // initialization message
    Serial.print("\n");

  } // end constructor

boolean update(){                              // update() method

    // see HAP Documentation for details on what each value represents

    if(target->getNewVal()==0){                    // if the target-state value is set to 0, HomeKit is requesting the door to be in open position
      LOG1("Opening Door\n");
      digitalWrite(lockPin, HIGH);                 // close the contact on the relay
      current->setVal(0);                          // set the current-state value to 0, which means "opening"
      LOG1("Door Open\n");
    } else {
      LOG1("Closing Door\n");
      digitalWrite(lockPin, LOW);
      current->setVal(1);                          // set the current-state value to 1, which means "closing"
      LOG1("Door Closed\n");
    }

    return(true);                                  // return true
}

void loop(){                                       // loop() method

    if(current->getVal()==target->getVal())        // if current-state matches target-state there is nothing do -- exit loop()
      return;

  } // loop

};
