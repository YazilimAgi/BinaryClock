  #define backPin 18
  #define setPin 17
  #define nextPin 19
  
  #define PUSH_DELAY 200
  
  int btnFirstPush = 0;
  int btnPushTime = 0;
  
  int backBtnVal = LOW;
  int setBtnVal = LOW;
  int nextBtnVal = LOW;
  
  boolean buttonActive = false;
  
  void buttonConfig() {
    pinMode(backPin, INPUT);
    pinMode(setPin, INPUT);
    pinMode(nextPin, INPUT);
  }
  void pushButton(int buttonPin) {
    if (digitalRead(buttonPin) == HIGH) {
      if (buttonActive == false) {
        buttonActive = true;
        btnFirstPush = millis();
      }
    } else {
      if (buttonActive == true) {
        buttonActive = false;
        btnPushTime = millis() - btnFirstPush;
        delay(PUSH_DELAY);
      }
    }
  }
  void readButtonState() {
    backBtnVal = digitalRead(backPin);
    setBtnVal = digitalRead(setPin);
    nextBtnVal = digitalRead(nextPin);
  }
