/*

Plays notes on button clicking, like a real piano.

Circuit:

(3)   (7) (8) (9) (10) (11) (12) (13)
 │     │   │   │   │    │    │    │
[B]   [/] [/] [/] [/]  [/]  [/]  [/]
 │     │   │   │   │    │    │    │
 ┴     ┴   ┴   ┴   ┴    ┴    ┴    ┴

Where [B] is buzzer and [/] is button.

*/

#include <Asynchrony.h>

#define FIRST_BUTTON_PIN 7  // First piano button pin. Other buttos are connected to next pins 
#define BUZZER_PIN 3
#define SOUND_DURATION 200

// Do
void note1() {
  tone(BUZZER_PIN, 261.63, SOUND_DURATION);
}

// Re
void note2() {
  tone(BUZZER_PIN, 293.33, SOUND_DURATION);
}

// Mi
void note3() {
  tone(BUZZER_PIN, 329.63, SOUND_DURATION);
}

// Fa
void note4() {
  tone(BUZZER_PIN, 349.23, SOUND_DURATION);
}

// Sol
void note5() {
  tone(BUZZER_PIN, 392, SOUND_DURATION);
}

// La
void note6() {
  tone(BUZZER_PIN, 440, SOUND_DURATION);
}

// Si
void note7() {
  tone(BUZZER_PIN, 493.88, SOUND_DURATION);
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  
  Asyn.click(note1, FIRST_BUTTON_PIN, LOW, INPUT_PULLUP);  // In pullup mode when button is pressed input voltage is low
  Asyn.click(note2, FIRST_BUTTON_PIN + 1, LOW, INPUT_PULLUP);
  Asyn.click(note3, FIRST_BUTTON_PIN + 2, LOW, INPUT_PULLUP);
  Asyn.click(note4, FIRST_BUTTON_PIN + 3, LOW, INPUT_PULLUP);
  Asyn.click(note5, FIRST_BUTTON_PIN + 4, LOW, INPUT_PULLUP);
  Asyn.click(note4, FIRST_BUTTON_PIN + 5, LOW, INPUT_PULLUP);
  Asyn.click(note5, FIRST_BUTTON_PIN + 6, LOW, INPUT_PULLUP);
}

void loop() {
  Asyn.loop();
}
