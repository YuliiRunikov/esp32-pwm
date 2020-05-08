#pragma once
#include <Arduino.h>

#define MODE_LINEAR             1
#define MODE_LOG                2

#define MODE_DEFAULT            MODE_LOG

#define SPEED_DEFAULT           5000
#define STEPS_DEFAULT           100
#define CHANNEL_DEFAULT         0

#define PWM_PREC_BIT            10
#define DEBUG

class ESP32_PWM
{
private:
    uint8_t     _pin;
    uint8_t     _channel;
    uint8_t     _steps;
    uint8_t     _mode;
    uint32_t    _speed;

    void init();

public:
    ESP32_PWM(uint8_t pin, uint8_t channel = CHANNEL_DEFAULT, uint8_t steps = STEPS_DEFAULT, uint8_t mode = MODE_DEFAULT, uint32_t speed = SPEED_DEFAULT);
    uint8_t setBrightness(uint8_t value);
};
