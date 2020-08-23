#include "config.h"

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
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if (Temp < LowerTemp) {
    digitalWrite(LED_BUILTIN, LOW);  
  }
}
