#include "DebouncedButton.h"


DebouncedButton::DebouncedButton(uint8_t pin, unsigned long debounceMs, unsigned long longPressMs)
    : pin_(pin), debounceMs_(debounceMs), longPressMs_(longPressMs) {
}


void DebouncedButton::initialize() {
    pinMode(pin_, INPUT_PULLUP);
}

DebouncedButton::PressType DebouncedButton::checkButton() {
    // keep track of state between calls (now per instance)
    if (lastChangeTime_ == 0) lastChangeTime_ = millis();

    // read the current state and time
    bool currentState = digitalRead(pin_);
    unsigned long currentTime = millis();

    // default return is no press
    PressType retVal = PressType::None;

    // debounce
    if( currentState != lastState_ ) {
        lastState_ = currentState;
        lastChangeTime_ = currentTime;
    }
    unsigned long stableTime = currentTime - lastChangeTime_;

    if( currentState == LOW ) {

        // if the button has been held down long enough, we have a candidate short press
        if( pendingPress_ == PressType::None && stableTime > debounceMs_ ) {
            pendingPress_ = PressType::Short;
        }

        // if the button has been held down even longer, we have a long press
        if( pendingPress_ == PressType::Short && stableTime > longPressMs_ ) {
            retVal = PressType::Long;
            pendingPress_ = PressType::Long; // remember this so we don't return it again
        }

    } else { // currentState == HIGH

        // release a pending short press on button release, if any
        if( pendingPress_ == PressType::Short ) {
            retVal = PressType::Short;
        }

        // clear any pending press (short because we're about to return it, or long because we returned it earlier)
        pendingPress_ = PressType::None;

    }

    return retVal;

    return retVal;
}

