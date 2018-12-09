#include "Led.h"

#define buzzerPin  12
#define NOTE_A  550
#define NOTE_As  582
#define NOTE_B  617
#define NOTE_C  654
#define NOTE_Cs  693
#define NOTE_D  734
#define NOTE_Ds  777
#define NOTE_E  824
#define NOTE_F  873
#define NOTE_Fs  925
#define NOTE_G  980
#define NOTE_Gs  1003
#define NOTE_A2  1100
#define NOTE_A2s  1165
#define NOTE_B2  1234
#define NOTE_C3  1308
#define NOTE_C3s  1385
#define NOTE_D3  1555

#define HALF  0.5
#define ONE  1.0
#define ONE_HALF  1.5
#define TWO  2.0
#define TWO_HALF  2.5

#define TEMPO 400


int harryPotterNote[14] = {NOTE_B, NOTE_E, NOTE_G, NOTE_F, NOTE_E,
                           NOTE_B2, NOTE_A2, NOTE_Fs, NOTE_E, NOTE_G,
                           NOTE_F, NOTE_Ds, NOTE_F, NOTE_B
                          };

float harryPotterDuration[14] = {ONE, ONE_HALF, HALF, ONE, TWO, ONE, TWO_HALF,
                                 TWO_HALF, ONE_HALF, HALF, ONE, TWO, ONE, TWO_HALF
                                };

void setTone(int pin, int note, int duration) {
  tone(pin, note, duration);
  delay(duration);
  noTone(pin);
}
void playMusic(int pin, int *note, float *duration, int len) {
  for (int i = 0; i < len; i++) {
    setTone(buzzerPin,  note[i], TEMPO *  duration[i]);
    alarmModForLed();
  }
}
void playHarryPotter() {
  playMusic(12, harryPotterNote, harryPotterDuration, 14);
}
