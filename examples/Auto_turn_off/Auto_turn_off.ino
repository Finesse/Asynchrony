/*

Buttons turn LED corresponding LED on, after it automaticaly turns off after some time

Circuit:

(2) (3) (3)   (8) (9) (10)
 │   │   │     │   │   │
 ▽   ▽   ▽    [/] [/] [/]
 │   │   │     │   │   │
[R] [R] [R]    ┴   ┴   ┴
 │   │   │
 ┴   ┴   ┴

Where [R] is resistor (220Ω), ▽ is LED and [/] is button.

*/

#include <Asynchrony.h>
using namespace Asynchrony;


#define LED_1 2
#define LED_2 3
#define LED_3 4
#define BUTTON_1 8
#define BUTTON_2 9
#define BUTTON_3 10
#define SHIMMER_DURATION 1000



// I tried to put all futher stuff to single class, but I failed because passing object method as function argument is impossible

// Timeout listeners identificators
identificator timeout_1,
              timeout_2,
              timeout_3;


// Actions on timeout that turn LEDs off. Timeouts are started on button click.
void onTimeout_1() {
  digitalWrite(LED_1, LOW);
}

void onTimeout_2() {
  digitalWrite(LED_2, LOW);
}

void onTimeout_3() {
  digitalWrite(LED_3, LOW);
}

// Click actions that turn LEDs on and start turning-off timeout.
void onClick_1() {
  digitalWrite(LED_1, HIGH);

  // If button is pressed before LED turns off previuos timeout should be stopped. Otherwise LED will turn off early.
  if(Asyn.check(timeout_1))
    Asyn.remove(timeout_1);

  timeout_1 = Asyn.timeout(onTimeout_1, SHIMMER_DURATION);
}

void onClick_2() {
  digitalWrite(LED_2, HIGH);

  if(Asyn.check(timeout_2))
    Asyn.remove(timeout_2);

  timeout_2 = Asyn.timeout(onTimeout_2, SHIMMER_DURATION);
}

void onClick_3() {
  digitalWrite(LED_3, HIGH);

  if(Asyn.check(timeout_3))
    Asyn.remove(timeout_3);

  timeout_3 = Asyn.timeout(onTimeout_3, SHIMMER_DURATION);
}



void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  
  /*
    Hooking `onClick_x` actions to buttons click.
    In pullup mode when button is pressed input voltage is low.
  */
  Asyn.click(onClick_1, BUTTON_1, LOW, INPUT_PULLUP);
  Asyn.click(onClick_2, BUTTON_2, LOW, INPUT_PULLUP);
  Asyn.click(onClick_3, BUTTON_3, LOW, INPUT_PULLUP);
}

void loop() {
  Asyn.loop();
}
