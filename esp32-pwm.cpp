#include "esp32-pwm.h"
#include <Arduino.h>
#include <math.h>  

ESP32_PWM::ESP32_PWM(uint8_t pin)
{
    ESP32_PWM(pin, CHANNEL_DEFAULT);
}
ESP32_PWM::ESP32_PWM(uint8_t pin, uint8_t channel)
{
    ESP32_PWM(pin, channel, STEPS_DEFAULT);
}

ESP32_PWM::ESP32_PWM(uint8_t pin, uint8_t channel, uint8_t steps)
{
    ESP32_PWM(pin, channel, steps, MODE_DEFAULT);
}

ESP32_PWM::ESP32_PWM(uint8_t pin, uint8_t channel, uint8_t steps, uint8_t mode)
{
    ESP32_PWM(pin, channel, steps, mode, SPEED_DEFAULT);
}

ESP32_PWM::ESP32_PWM(uint8_t pin, uint8_t channel, uint8_t steps, uint8_t mode, uint32_t speed)
{
    this->pin = pin;
    this->channel = channel;
    this->steps = steps;
    this->mode = mode;
    this->speed = speed;

    this->init();
}
void ESP32_PWM::init()
{

    pinMode(this->pin, OUTPUT);
    // configure LED PWM functionalitites
    ledcSetup(this->channel, this->speed, 8);

    // attach the channel to the GPIO2 to be controlled
    ledcAttachPin(this->pin, this->channel);
}

uint8_t ESP32_PWM::setBrightness(uint8_t value)
{
    value = constrain(value, 0, this->steps - 1);
    int percent = (int)100 * value / this->steps;
    int v_min = 0;
    int v_max = 2 ^ 8 - 1;
    int v_value = (int)100 * percent / v_max;
    if (this->mode == MODE_LOG)
    {
      float a = 0.4;//0.33..0.5
        v_value = (int)pow(v_max*percent/100,1/a)+0.5;
    }
    ledcWrite(this->channel, v_value);
    return v_value;
}
