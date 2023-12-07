struct DoorBell : Service::Doorbell { 
 
  SpanCharacteristic *switchEvent;                  // reference to the ProgrammableSwitchEvent Characteristic
  
  DoorBell(int buttonPin) : Service::Doorbell(){

    switchEvent=new Characteristic::ProgrammableSwitchEvent();  // Programmable Switch Event Characteristic (will be set to SINGLE, DOUBLE or LONG press)
                
    new SpanButton(buttonPin);                                  // create new SpanButton

    Serial.print("Configuring Programmable Pushbutton: Pin=");  // initialization message
    Serial.print(buttonPin);
    Serial.print("\n");
    
  } // end constructor

  // We do NOT need to implement an update() method or a loop() method - just the button() method:

  void button(int pin, int pressType) override {

    LOG1("Found button press on pin: ");            // always a good idea to log messages
    LOG1(pin);
    LOG1("  type: ");
    LOG1(pressType==SpanButton::LONG?"LONG":(pressType==SpanButton::SINGLE)?"SINGLE":"DOUBLE");
    LOG1("\n");

    // All the action occurs in this single line below.  We simply set the value of the Programmable Switch Event Characteristic
    // to the value provided by pressType.  The values of pressType (0=SpanButton::SINGLE, 1=SpanButton::DOUBLE, and 2=SpanButton::LONG)
    // were designed to match the required values of the Programmable Switch Event Characteristic.

    switchEvent->setVal(pressType);                // set the value of the switchEvent Characteristic

  }

};
