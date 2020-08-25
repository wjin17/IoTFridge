#ifndef Thermistor_h
#define Thermistor_h

class Thermistor
{
  public:
    Thermistor(int power_pin, int read_pin);
    void get_reading();
  private:
    int _power_pin;
    int _read_pin
};

#endif
