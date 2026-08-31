#include <Arduino.h>
#include <SPI.h>
#include <TinyGPS++.h>

// Include configuration
#include "Configuration.h"

// Include our classes
#include "TFTDisplay.h"
#include "DebouncedButton.h"
#include "TimeData.h"

// GPS object
TinyGPSPlus gps_;

// Display object
TFTDisplay tftDisplay(TFT_CS_PIN, TFT_DC_PIN, TFT_RST_PIN);

// Button objects
DebouncedButton timeZoneButton(TIMEZONE_BUTTON_PIN, BUTTON_DEBOUNCE_MS, BUTTON_LONG_PRESS_MS);
DebouncedButton h24Button(H24_BUTTON_PIN, BUTTON_DEBOUNCE_MS, BUTTON_LONG_PRESS_MS);

// Settings
int timezoneOffsetHours = 0;
bool is24HourFormat = true;

void setup() {
    // Initialize serial communication for console output
    Serial.begin(SERIAL_BAUD_RATE);
    delay(500);
    Serial.println("\n\n=== GPS Mechanical Clock ===");
    Serial.println("With TFT Display, LED feedback, and button controls\n");

    // Initialize LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("[SETUP] LED initialized");

    // Initialize TFT display
    Serial.println("[SETUP] Initializing TFT display...");
    tftDisplay.initialize();
    tftDisplay.showWaitingForGpsScreen();
    Serial.println("[SETUP] TFT display initialized");

    // Initialize buttons
    timeZoneButton.initialize();
    h24Button.initialize();
    Serial.println("[SETUP] Buttons initialized");
    Serial.println("  - Timezone button (GPIO " + String(TIMEZONE_BUTTON_PIN) + "): increment offset");
    Serial.println("  - 24H button (GPIO " + String(H24_BUTTON_PIN) + "): toggle format");

    // Configure GPS UART pins
    Serial1.setRX(GPS_RX_PIN);
    Serial1.setTX(GPS_TX_PIN);
    Serial1.begin(GPS_BAUD_RATE);

    Serial.println("[SETUP] GPS initialized at 9600 baud\n");
    Serial.println("Waiting for GPS data...");
    Serial.println("Current timezone offset: " + String(timezoneOffsetHours) + " hours");
    Serial.println("Time format: " + String(is24HourFormat ? "24H" : "12H") + "\n");

    // Signal core 1 that setup is complete
    rp2040.fifo.push(1);
}

void setup1() {
    // block core 1 until we get the signal
    rp2040.fifo.pop();
    delay(500);
    Serial.println("\n[SETUP1] Core 1 startup - setup completed!");
    Serial.flush();
}

// Helper function to assess signal strength
const char* getSignalStrength(double hdop, int satellites) {
    if (satellites < 3) {
        return "NO SIGNAL";
    }
    if (hdop < 1.0 && satellites >= 8) {
        return "EXCELLENT";
    } else if (hdop < 2.0 && satellites >= 6) {
        return "GOOD";
    } else if (hdop < 5.0 && satellites >= 4) {
        return "MODERATE";
    } else if (hdop < 10.0 && satellites >= 3) {
        return "FAIR";
    } else {
        return "POOR";
    }
}

// Main loop on core 0
void loop() {
    // Check buttons
    DebouncedButton::PressType tzPress = timeZoneButton.checkButton();
    if (tzPress == DebouncedButton::Short) {
        timezoneOffsetHours++;
        if (timezoneOffsetHours > 12) {
            timezoneOffsetHours = -12;
        }
        Serial.print("[BUTTON] Timezone changed to: ");
        Serial.print(timezoneOffsetHours);
        Serial.println(" hours");
    }

    DebouncedButton::PressType h24Press = h24Button.checkButton();
    if (h24Press == DebouncedButton::Short) {
        is24HourFormat = !is24HourFormat;
        Serial.print("[BUTTON] Time format changed to: ");
        Serial.println(is24HourFormat ? "24H" : "12H");
    }

    // Process GPS data
    static unsigned long lastReport = 0;
    static bool lastValidState = false;

    while (Serial1.available()) {
        char c = Serial1.read();
        if (gps_.encode(c)) {
            // Complete NMEA sentence parsed
        }
    }

    // Update display and report GPS status every 2 seconds
    if (millis() - lastReport > 2000) {
        int sats = gps_.satellites.value();
        double hdop = gps_.hdop.hdop();
        bool valid = gps_.time.isValid() && sats >= 3;
        const char* signalStr = getSignalStrength(hdop, sats);

        // Toggle LED when valid, off when invalid
        if (valid != lastValidState) {
            digitalWrite(LED_BUILTIN, valid ? HIGH : LOW);
            lastValidState = valid;
        }

        if (valid) {
            // Calculate local time with timezone offset
            int utcHour = gps_.time.hour();
            int utcMin = gps_.time.minute();
            int utcSec = gps_.time.second();

            int localHour = utcHour + timezoneOffsetHours;
            if (localHour < 0) localHour += 24;
            if (localHour >= 24) localHour -= 24;

            // Determine AM/PM for 12H format
            bool isPm = false;
            if (!is24HourFormat) {
                if (localHour >= 12) isPm = true;
                if (localHour == 0) localHour = 12;
                if (localHour > 12) localHour -= 12;
            }

            // Create TimeData for display
            TimeData timeData = {
                utcHour, utcMin, utcSec,
                localHour, utcMin, utcSec,
                sats,
                true,
                signalStr,
                is24HourFormat,
                isPm
            };

            // Update display
            tftDisplay.updateTime(timeData);

            // Serial output
            Serial.print("[GPS] Sats: ");
            Serial.print(sats);
            Serial.print(" | Time: ");
            if (localHour < 10) Serial.print("0");
            Serial.print(localHour);
            Serial.print(":");
            if (utcMin < 10) Serial.print("0");
            Serial.print(utcMin);
            Serial.print(":");
            if (utcSec < 10) Serial.print("0");
            Serial.print(utcSec);
            if (!is24HourFormat) {
                Serial.print(" ");
                Serial.print(isPm ? "PM" : "AM");
            }
            Serial.println();
        } else {
            // Waiting for fix
            TimeData timeData = {
                0, 0, 0,
                0, 0, 0,
                sats,
                false,
                signalStr,
                is24HourFormat,
                false
            };
            tftDisplay.updateTime(timeData);
            Serial.println("[GPS] Acquiring satellite lock...");
        }
        lastReport = millis();
    }
}

// Main loop on core 1
void loop1() {
    delay(100);  // Minimal work - just keep core 1 alive
}