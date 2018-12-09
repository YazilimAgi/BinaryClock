#define UNIT 3
#define DIGIT 2
enum Clock {
  Hour,
  Minute,
  Second
};

enum Digit {
  Most,
  Least
};

enum ClockMode {
  ShowClock,
  SetAlarm,
  SetClock
};

byte clockMode = ShowClock;

byte currentTime[UNIT][DIGIT] = {{0, 0}, {0, 0}, {0, 0}};
byte alarmSet   [UNIT][DIGIT] = {{0, 0}, {0, 0}, {0, 0}};
byte clockSet   [UNIT][DIGIT] = {{0, 0}, {0, 0}, {0, 0}};
// PİN CONFIG FOR CLOCK MODULE

#define clockReset 4    //RST PİN
#define clockData 3    //DAT PİN
#define clockClk 2  //CLK PİN
DS1302 rtc(clockReset, clockData, clockClk);

void parseTime(byte t[3][2], Time current) {

  t[Hour][Least] = current.hr % 10;
  t[Hour][Most] = current.hr / 10;

  t[Minute][Least] = current.min % 10;
  t[Minute][Most] = current.min / 10;

  t[Second][Least] = current.sec % 10;
  t[Second][Most] = current.sec / 10;

}
Time arrayToTime(byte t[3][2]) {
  Time temp(2018, 12, 10,
            (t[Hour][Most] * 10) + t[Hour][Least],
            (t[Minute][Most] * 10) + t[Minute][Least],
            (t[Second][Most] * 10) + t[Second][Least],
            Time::kFriday);
  return temp;
}
void setTime(Time t) {
  rtc.writeProtect(false);
  rtc.halt(false);
  rtc.time(t);
}
void clearTime(Time *t) {
  t->hr = 0;
  t->min = 0;
  t->sec = 0;
}
