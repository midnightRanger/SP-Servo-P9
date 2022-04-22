#include <Arduino.h>

#define button_press_delay 100
bool flag = false; 
uint32_t btnTimer = 0; 

bool button_read(int button_pin){
    bool btnState = !digitalRead(button_pin);
    if (btnState && !flag && millis() - btnTimer > button_press_delay) {
        flag = true; 
        btnTimer = millis();
        return true; 
    }

    if (!btnState && flag && millis() - btnTimer > button_press_delay){
        flag = false;
        btnTimer = millis();
    }

    return false;
}