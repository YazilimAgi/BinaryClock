#include "ClockModule.h"
//DELAY FOR LED
#define dly 1

//PIN CONF. FOR RGB STATE LED.
#define redPin 15
#define greenPin 16
#define bluePin 14

//PIN CONF. FOR 20 LEDS.
#define LED_PIN_A 9
#define LED_PIN_B 8
#define LED_PIN_C 7
#define LED_PIN_D 6
#define LED_PIN_E 5

//FOR 3 DIMENTIONAL ARRAY
#define LED_PIN_COUNT 20
#define PIN_COUNT 5
#define PIN_CONFIG 0
#define PIN_STATE 1

//LED STATES FOR 20LEDS
#define HOUR_MD_ONE 3
#define HOUR_MD_TWO 4

#define HOUR_LD_ONE 12
#define HOUR_LD_TWO 11
#define HOUR_LD_FOUR 18
#define HOUR_LD_EIGHT 17

#define MINUTE_MD_ONE 1
#define MINUTE_MD_TWO 2
#define MINUTE_MD_FOUR 6

#define MINUTE_LD_ONE 7
#define MINUTE_LD_TWO 8
#define MINUTE_LD_FOUR 5
#define MINUTE_LD_EIGHT 14

#define SECOND_MD_ONE 13
#define SECOND_MD_TWO 9
#define SECOND_MD_FOUR 10

#define SECOND_LD_ONE 20
#define SECOND_LD_TWO 19
#define SECOND_LD_FOUR 16
#define SECOND_LD_EIGHT 15



int matrix[LED_PIN_COUNT][2][PIN_COUNT] = {
  //              PIN_CONFIG                          PIN_STATE
  //    A       B       C      D      E         A     B    C    D    E
  { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } },
  { { OUTPUT, INPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } },

  { { INPUT, INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } },
  { { INPUT, INPUT, OUTPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } },

  { { INPUT, OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } },
  { { INPUT, OUTPUT, INPUT, OUTPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } },

  { { INPUT, OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, HIGH, LOW, LOW, LOW } },
  { { INPUT, OUTPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } },

  { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } },
  { { OUTPUT, INPUT, INPUT, OUTPUT, INPUT }, { LOW, LOW, LOW, HIGH, LOW } },

  { { INPUT, OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, LOW, HIGH, LOW, LOW } },
  { { INPUT, OUTPUT, OUTPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } },

  { { INPUT, INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, HIGH, LOW } },
  { { INPUT, INPUT, INPUT, OUTPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } },

  { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT }, { HIGH, LOW, LOW, LOW, LOW } },
  { { OUTPUT, OUTPUT, INPUT, INPUT, INPUT }, { LOW, HIGH, LOW, LOW, LOW } },

  { { INPUT, INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, HIGH, LOW, LOW } },
  { { INPUT, INPUT, OUTPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } },

  { { OUTPUT, INPUT, INPUT, INPUT, OUTPUT }, { HIGH, LOW, LOW, LOW, LOW } },
  { { OUTPUT, INPUT, INPUT, INPUT, OUTPUT }, { LOW, LOW, LOW, LOW, HIGH } },
};

//RGB LED FUNCTİONS
void rgbLedConfig() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
void turnOnRgb(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
void turnOffRgb() {
  analogWrite(redPin, LOW);
  analogWrite(greenPin, LOW);
  analogWrite(bluePin, LOW);
}
void turnOn( int led ) {
  led--;
  for (int pin = LED_PIN_A, state = 0; pin >= LED_PIN_E; pin--, state++) {
    pinMode( pin, matrix[led][PIN_CONFIG][state] );
    digitalWrite( pin, matrix[led][PIN_STATE][state] );
  }
  delay(dly);
}
void turnOnAll() {
  for (int i = 1; i < 21; i++) {
    turnOn(i);
  }
}
void turnOff() {
  for (int pin = LED_PIN_A, state = 0; pin >= LED_PIN_E; pin--, state++) {
    pinMode( pin, OUTPUT );
    digitalWrite( pin, LOW );
  }
  delay(dly);
}
void alarmModForLed() {
  for (int i = 1; i < 21; i++)
    turnOn(i);
  delay(dly);
  turnOff();
}

void showHour(byte myTimeArray[UNIT]) {
  switch (  myTimeArray[Least]) {
    case 0:
      if (clockMode == SetClock || clockMode == SetAlarm)
        turnOff();
      break;
    case 1:
      turnOn(HOUR_LD_ONE); break;
    case 2:
      turnOn(HOUR_LD_TWO); break;
    case 3:
      turnOn(HOUR_LD_ONE); turnOn(HOUR_LD_TWO); break;
    case 4:
      turnOn(HOUR_LD_FOUR); break;
    case 5:
      turnOn(HOUR_LD_ONE); turnOn(HOUR_LD_FOUR); break;
    case 6:
      turnOn(HOUR_LD_TWO); turnOn(HOUR_LD_FOUR); break;
    case 7:
      turnOn(HOUR_LD_ONE); turnOn(HOUR_LD_TWO); turnOn(HOUR_LD_FOUR); break;
    case 8:
      turnOn(HOUR_LD_EIGHT); break;
    case 9:
      turnOn(HOUR_LD_ONE); turnOn(HOUR_LD_EIGHT); break;
  }

  switch (  myTimeArray[Most]) {
    case 0:
      if (clockMode == SetClock || clockMode == SetAlarm)
        turnOff();
      break;
    case 1:
      turnOn(HOUR_MD_ONE); break;
    case 2:
      turnOn(HOUR_MD_TWO); break;
  }
}

void showMinute(byte myTimeArray[UNIT]) {
  switch (  myTimeArray[Least]) {
    case 0:
      if (clockMode == SetClock || clockMode == SetAlarm)
        turnOff();
      break;
    case 1:
      turnOn(MINUTE_LD_ONE); break;
    case 2:
      turnOn(MINUTE_LD_TWO); break;
    case 3:
      turnOn(MINUTE_LD_ONE); turnOn(MINUTE_LD_TWO); break;
    case 4:
      turnOn(MINUTE_LD_FOUR); break;
    case 5:
      turnOn(MINUTE_LD_ONE); turnOn(MINUTE_LD_FOUR); break;
    case 6:
      turnOn(MINUTE_LD_TWO); turnOn(MINUTE_LD_FOUR); break;
    case 7:
      turnOn(MINUTE_LD_ONE); turnOn(MINUTE_LD_TWO); turnOn(MINUTE_LD_FOUR); break;
    case 8:
      turnOn(MINUTE_LD_EIGHT); break;
    case 9:
      turnOn(MINUTE_LD_ONE); turnOn(MINUTE_LD_EIGHT); break;
  }
  switch (  myTimeArray[Most]) {
    case 0:
      if (clockMode == SetClock || clockMode == SetAlarm)
        turnOff();
      break;
    case 1:
      turnOn(MINUTE_MD_ONE); break;
    case 2:
      turnOn(MINUTE_MD_TWO); break;
    case 3:
      turnOn(MINUTE_MD_ONE); turnOn(MINUTE_MD_TWO); break;
    case 4:
      turnOn(MINUTE_MD_FOUR); break;
    case 5:
      turnOn(MINUTE_MD_ONE); turnOn(MINUTE_MD_FOUR); break;
  }
}

void showSecond(byte myTimeArray[UNIT]) {
  switch (  myTimeArray[Least]) {
    case 0:
      if (clockMode == SetClock || clockMode == SetAlarm)
        turnOff();
      break;
    case 1:
      turnOn(SECOND_LD_ONE); break;
    case 2:
      turnOn(SECOND_LD_TWO); break;
    case 3:
      turnOn(SECOND_LD_ONE); turnOn(SECOND_LD_TWO); break;
    case 4:
      turnOn(SECOND_LD_FOUR); break;
    case 5:
      turnOn(SECOND_LD_ONE); turnOn(SECOND_LD_FOUR); break;
    case 6:
      turnOn(SECOND_LD_TWO); turnOn(SECOND_LD_FOUR); break;
    case 7:
      turnOn(SECOND_LD_ONE); turnOn(SECOND_LD_TWO); turnOn(SECOND_LD_FOUR); break;
    case 8:
      turnOn(SECOND_LD_EIGHT); break;
    case 9:
      turnOn(SECOND_LD_ONE); turnOn(SECOND_LD_EIGHT); break;
  }
  switch (  myTimeArray[Most]) {
    case 0:
      if (clockMode == SetClock || clockMode == SetAlarm)
        turnOff();
      break;
    case 1:
      turnOn(SECOND_MD_ONE); break;
    case 2:
      turnOn(SECOND_MD_TWO); break;
    case 3:
      turnOn(SECOND_MD_ONE); turnOn(SECOND_MD_TWO); break;
    case 4:
      turnOn(SECOND_MD_FOUR); break;
    case 5:
      turnOn(SECOND_MD_ONE); turnOn(SECOND_MD_FOUR); break;
  }

}
