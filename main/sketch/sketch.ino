#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//pins
const int PIN_ENC_A = 4;
const int PIN_ENC_B = 5;
const int PIN_BTN = 6;
const int PIN_LED = 7;

//timer states

enum TimerState {
  STATE_PICKING,
  STATE_LOCKED,
  STATE_RUNNING,
  STATE_PAUSED
};

TimerState currentState = STATE_PICKING;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8,9);

  //init oled display w/ default i2c adress
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

unsigned long startTime  = 0;

void loop() {
  // put your main code here, to run repeatedly:
//calculate time so u can time without using delay()
  unsigned long elapsedMillis = millis() - startTime;
  unsigned long totalSeconds = elapsedMillis / 1000;

  int minutes = totalSeconds / 60;
  int seconds = totalSeconds % 60;
  int tenths = (elapsedMillis % 1000) / 100;

  //clear display
  display.ClearDisplay();

  //Header text
  display.setTetSize(1);
  display.setCursor(20,4);
  display.print("SYSTEM TIMER");
  display.drawLine(0, 14, 128, 14, SSD1306_WHITE);

  //draw main display timer
  display.setTextSize(2);
  display.setCursor(12,30);

  if (minutes < 10) display.print("0");
  display.print(minutes);
  display.print(":");

  if (seconds< 10) display.print("0");
  display.print(seconds);
  display.print(".");
  display.print(tenths);

  //push the stuff to the screen
  display.Display();
  delay(50); //write every 50ms
}
