#ifndef DEBOUNCEDBUTTON_H
#define DEBOUNCEDBUTTON_H

#include <Arduino.h>


class DebouncedButton {
public:
    DebouncedButton(uint8_t pin, unsigned long debounceMs, unsigned long longPressMs);
    void initialize();

    enum PressType {
        None,
        Short,
        Long
    };

    PressType checkButton();

private:
    uint8_t pin_;
    unsigned long debounceMs_;
    unsigned long longPressMs_;
    bool lastState_ = HIGH;
    unsigned long lastChangeTime_ = 0;
    PressType pendingPress_ = PressType::None;
};

#endif
