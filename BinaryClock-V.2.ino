//LIBRARY IMPORT
#include <DS1302.h>
#include "Button.h"
//#include "ClockModule.h" led.h da çağırdık.
//#include "Led.h" Music.h da çağırdık.
#include "Music.h"

//CONST VALUE FOR MAIN
#define ROW 3
#define COLUMN 2

//VARIABLE FOR MAIN
boolean alarmActivated = true;
int c = 0;
int posCont = 0;


void clearArray(int myArray[ROW][COLUMN]) {
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COLUMN; j++) {
      myArray[i][j] = 0;
    }
  }
}
void setRgbColor() {
  switch (clockMode) {
    case ShowClock:
      if (alarmActivated)
        turnOnRgb(255, 0, 255);
      else
        turnOnRgb(0, 255, 0);
      break;
    case SetAlarm: turnOnRgb(255, 255, 255);
      break;
    case SetClock: turnOnRgb(0, 0, 255);
      break;
    default:
      break;
  }
}
void checkAlarm(Time current, Time alarm) {
  if (current.hr == alarm.hr && current.min == alarm.min && current.sec == alarm.sec && alarmActivated) {
    Serial.println("GIRDI");
    playHarryPotter();
    alarmActivated = !alarmActivated;
    setRgbColor();
  }
}
void incrementTime(Time *setter, boolean up) {
  if (!up) {
    switch (posCont) {
      case 0: if (setter->hr > 0)setter->hr--;
        break;
      case 1: if (setter->min > 0) setter->min--;
        break;
      case 2:  if (setter->sec > 0)setter->sec--;
        break;
      default: break;
    }
  }
  else {
    switch (posCont) {
      case 0: if (setter->hr < 23) setter->hr++;
        break;
      case 1: if (setter->min < 59) setter->min++;
        break;
      case 2: if (setter->sec < 59) setter->sec++;
        break;
      default: break;
    }
  }
}
void positionControl() {
  posCont++;
  if (posCont == 3)
    c = 1;
}

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  rgbLedConfig();
  buttonConfig();



}

void loop() {

  setRgbColor();
  Time setter(0, 0, 0, 0, 0, 0, 0);
  Time alarmChecker = arrayToTime(alarmSet);

  while (clockMode == ShowClock) {
      Serial.println("show");
    parseTime(currentTime, rtc.time());

    showHour(currentTime[Hour]);
    showMinute(currentTime[Minute]);
    showSecond(currentTime[Second]);

    checkAlarm(rtc.time(), alarmChecker);
    pushButton(setPin);

    if (btnPushTime > 0 && btnPushTime < 1000) {
      clockMode = SetAlarm;
      btnPushTime = 0;
    }
    else if (btnPushTime >= 1000 && btnPushTime < 3000) {
      clockMode = SetClock;
      btnPushTime = 0;
    }
    else if (btnPushTime >= 3000) {
      alarmActivated = !alarmActivated;
      setRgbColor();
      btnPushTime = 0;
    }
  }


  setRgbColor();

  while (clockMode == SetAlarm) {
    checkAlarm(rtc.time(), alarmChecker);

    Serial.println("set alarm");
    readButtonState();

    if (backBtnVal == HIGH) {
      Serial.println("-----");
      incrementTime(&setter, false);
      delay(PUSH_DELAY);
    }
    else if (setBtnVal == HIGH) {
      positionControl();

      Serial.println("set alarm go");
      delay(PUSH_DELAY);
    }
    else if (nextBtnVal == HIGH) {
      incrementTime(&setter, true);
      Serial.println("goooo");
      delay(PUSH_DELAY);
    }

    parseTime(alarmSet, setter);
    showHour(alarmSet[Hour]);
    showMinute(alarmSet[Minute]);
    showSecond(alarmSet[Second]);

    if (c == 1) {
      c = 0;
      posCont = 0;
      alarmActivated = true;
      clearTime(&setter);
      clockMode = ShowClock;
      alarmChecker = arrayToTime(alarmSet);

      break;
    }
  }
  setRgbColor();

  while (clockMode == SetClock) {
    checkAlarm(rtc.time(), alarmChecker);
    Serial.println("set clock");
    readButtonState();

    if (backBtnVal == HIGH) {
      incrementTime(&setter, false);
      Serial.println("----------------");
      delay(PUSH_DELAY);
    }
    else if (setBtnVal == HIGH) {
      positionControl();
      Serial.println("set clock go");
      delay(PUSH_DELAY);
    }
    else if (nextBtnVal == HIGH) {
      incrementTime(&setter, true);
      Serial.println("+++++++++++");
      delay(PUSH_DELAY);
    }

    parseTime(clockSet, setter);
    showHour(clockSet[Hour]);
    showMinute(clockSet[Minute]);
    showSecond(clockSet[Second]);

    if (c == 1) {
      c = 0;
      clearTime(&setter);
      posCont = 0;
      clockMode = ShowClock;
      Time temp = arrayToTime(clockSet);
      setTime(temp);
      break ;
    }

  }
}
