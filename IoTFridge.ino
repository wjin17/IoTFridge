#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"
#include "fan_frames.h"

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

// Mapping NodeMCU Ports to Arduino GPIO Pins
// Allows use of NodeMCU Port nomenclature in config.h
#define A0 0
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12 
#define D7 13
#define D8 15

unsigned long time_now = 0;

bool fan_on;

const int ThermistorPowerPin = THERMISTOR_POWER;
const int ThermistorReadPin = THERMISTOR_READ;
const int ThermistorDelay = THERMISTOR_DELAY;
const double Vcc = VCC;
const float r1 = R1;
const float c1 = C1;
const float c2 = C2;
const float c3 = C3;

float Temp;

float LowerTemp = LOWER_TEMP;
float UpperTemp = UPPER_TEMP;

int xx=22;
int yy=0;
int tt=200;

double get_thermistor_reading() {
  // returns thermistor value in F
  int Vo;
  float logR2, R2, T;
  
  digitalWrite(ThermistorPowerPin, HIGH);
  Vo = analogRead(ThermistorReadPin);
  //R2 = (R1 * Vo) / (Vcc - Vo);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0;
  digitalWrite(ThermistorPowerPin, LOW);

  return T;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(ThermistorPowerPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setCursor(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() - time_now > ThermistorDelay) {
    time_now = millis();
    
    Temp = get_thermistor_reading();

    Serial.print("Reading temp: ");
    Serial.print(Temp);
    Serial.print("\n");
  }

  if (Temp > UpperTemp) {
    // If temp is greater than upper bound, activate cooling
    digitalWrite(LED_BUILTIN, LOW);
    fan_on = true;
  }

  if (Temp < LowerTemp) {
    // If temp is less than lower bound, deactivate cooling
    digitalWrite(LED_BUILTIN, HIGH);
    fan_on = false;
  }

  if (fan_on) {
    display.clearDisplay();
    display.drawBitmap(xx, yy,frame0,24,24, 1);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,24);
    display.print("T: ");
    display.print(Temp);
    display.print("F\n");
    display.display();
    delay(tt);
    
    display.clearDisplay();
    display.drawBitmap(xx, yy,frame1,24,24, 1);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,24);
    display.print("T: ");
    display.print(Temp);
    display.print("F\n");
    display.display();
    delay(tt);
    
    display.clearDisplay();
    display.drawBitmap(xx, yy,frame2,24,24, 1);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,24);
    display.print("T: ");
    display.print(Temp);
    display.print("F\n");
    display.display();
    delay(tt);
  } else {
    display.clearDisplay();
    display.drawBitmap(xx, yy,frame0,24,24, 1);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,24);
    display.print("T: ");
    display.print(Temp);
    display.print("F\n");
    display.display();
    delay(tt);
  }
}
