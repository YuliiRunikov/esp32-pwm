#include "esp32-pwm.h"
#include <Arduino.h>
#include <math.h>

ESP32_PWM::ESP32_PWM(uint8_t pin, uint8_t channel, uint8_t steps, uint8_t mode, uint32_t speed)
{
    _pin = pin;
#ifdef DEBUG
    Serial.print("Pin: ");
    Serial.println(_pin);
#endif
    _channel = channel;
#ifdef DEBUG
    Serial.print("Channel: ");
    Serial.println(_channel);
#endif
    _steps = steps;
    _mode = mode;
    _speed = speed;

    this->init();
}

void ESP32_PWM::init()
{
    pinMode(_pin, OUTPUT);
    ledcSetup(_channel, _speed, PWM_PREC_BIT);
    ledcAttachPin(_pin, _channel);
}

uint8_t ESP32_PWM::setBrightness(uint8_t value)
{
#ifdef DEBUG
    Serial.print("Input value:");
    Serial.println(value);
#endif
    value = constrain(value, 0, _steps - 1);
#ifdef DEBUG
    Serial.print("Normalized value:");
    Serial.println(value);
#endif
    int percent = (int)100 * value / _steps;
#ifdef DEBUG
    Serial.print("Percent:");
    Serial.println(percent);
#endif   
    int v_min = 0;
    int v_max = 2 ^ PWM_PREC_BIT - 1;
    int v_value = (int)100 * percent / v_max;
    if (_mode == MODE_LOG)
    {
        float a = 0.4; //0.33..0.5
        v_value = (int)pow(v_max * percent / 100, 1 / a) + 0.5;
    }
    ledcWrite(_channel, v_value);
    return v_value;
}
