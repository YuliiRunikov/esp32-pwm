#pragma once
#include <Arduino.h>

#define MODE_LINEAR 1
#define MODE_LOG 2

#define MODE_DEFAULT MODE_LOG

#define SPEED_DEFAULT 5000
#define STEPS_DEFAULT 100
#define CHANNEL_DEFAULT 0

class ESP32_PWM
{
private:
    uint8_t pin;
    uint8_t channel;
    uint8_t steps;
    uint8_t mode;
    uint32_t speed;
    void init();

public:
    ESP32_PWM(uint8_t pin);
    ESP32_PWM(uint8_t pin, uint8_t channel);
    ESP32_PWM(uint8_t pin, uint8_t channel, uint8_t steps);
    ESP32_PWM(uint8_t pin, uint8_t channel, uint8_t steps, uint8_t mode);
    ESP32_PWM(uint8_t pin, uint8_t channel, uint8_t steps, uint8_t mode, uint32_t speed);
    uint8_t setBrightness(uint8_t value);
};