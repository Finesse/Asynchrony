/*

Blinking LED. Clicking button turns on/off blinking.

Circuit:

(3)   (7)
 │     │
 ▽   [/]
 │     │
[R]    ┴
 │
 ┴

Where [R] is resistor (220Ω), ▽ is LED and [/] is button.

*/

#include <Asynchrony.h>
using namespace Asynchrony;


#define LED_PIN 3
#define BUTTON_PIN 7
#define BLINK_PERIOD 1000

bool blinkState = false; // Whether LED is on
bool buttonState = false; // Whether blinking is on
identificator interval; // Event listener identificator



void onInterval() {
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

void onClick() {
  if(!buttonState) {
    // Turning blinking on
    blinkState = true;
    digitalWrite(LED_PIN, HIGH);
    interval = Asyn.interval(onInterval, BLINK_PERIOD / 2); // Make function `onInterval` be called every half period
  } else {
    // Turning blinking off
    Asyn.remove(interval); // Stop calling function `onInterval`
    digitalWrite(LED_PIN, LOW);
  }
  
  buttonState = !buttonState;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  /*
    Hooking `onClick` action to button click.
    In pullup mode when button is pressed input voltage is low.
  */
  Asyn.click(onClick, BUTTON_PIN, LOW, INPUT_PULLUP);
}

void loop() {
  Asyn.loop();
}
