#ifndef TIMEZONE_DETECTOR_H
#define TIMEZONE_DETECTOR_H

#include <Arduino.h>

// Timezone detection based on GPS coordinates
class TimezoneDetector {
public:
    struct TimezoneRegion {
        const char* name;
        float minLat, maxLat;
        float minLon, maxLon;
        int utcOffset;  // in hours, can be negative
    };

    // Detect timezone from GPS coordinates
    static int detectTimezone(double latitude, double longitude);

    // Get timezone name
    static const char* getTimezoneName(double latitude, double longitude);

private:
    // Timezone database - covers major regions worldwide
    static constexpr TimezoneRegion TIMEZONE_TABLE[] = {
        // North America - PST/PDT
        {"Pacific", 32.0, 49.0, -130.0, -114.0, -8},

        // North America - MST/MDT
        {"Mountain", 30.0, 49.0, -114.0, -102.0, -7},

        // North America - CST/CDT
        {"Central", 25.0, 49.0, -102.0, -87.0, -6},

        // North America - EST/EDT
        {"Eastern", 24.0, 49.0, -87.0, -66.0, -5},

        // Atlantic
        {"Atlantic", 24.0, 50.0, -66.0, -52.0, -4},

        // Mexico - CST/CDT
        {"Mexico Central", 14.0, 32.0, -117.0, -87.0, -6},

        // South America - Venezuela/Colombia
        {"Venezuela", -1.0, 13.0, -73.0, -59.0, -4},

        // South America - Brazil (Eastern)
        {"Brazil East", -33.0, 5.0, -60.0, -34.0, -3},

        // South America - Argentina/Chile
        {"Argentina", -56.0, -21.0, -76.0, -53.0, -3},

        // UK/Ireland
        {"GMT/BST", 49.0, 59.0, -9.0, 2.0, 0},

        // Central Europe
        {"CET/CEST", 43.0, 56.0, -1.0, 18.0, 1},

        // Eastern Europe
        {"EET/EEST", 40.0, 66.0, 18.0, 40.0, 2},

        // Middle East
        {"EAT", 0.0, 35.0, 25.0, 55.0, 3},

        // India
        {"IST", 8.0, 35.0, 68.0, 97.0, 5},  // IST = UTC+5:30 (approximated)

        // Southeast Asia
        {"SE Asia", -10.0, 20.0, 92.0, 140.0, 7},

        // East Asia - China
        {"China", 18.0, 54.0, 73.0, 135.0, 8},

        // Japan/Korea
        {"JST/KST", 30.0, 55.0, 125.0, 145.0, 9},

        // Australia - Eastern
        {"AEST/AEDT", -44.0, -10.0, 113.0, 154.0, 10},

        // New Zealand
        {"NZST/NZDT", -47.0, -34.0, 166.0, 179.0, 12},

        // Pacific Islands - Hawaii
        {"Hawaii", 18.0, 23.0, -160.0, -154.0, -10},

        // UTC/London
        {"UTC", 0.0, 0.0, 0.0, 0.0, 0},
    };

    static constexpr int TIMEZONE_TABLE_SIZE = sizeof(TIMEZONE_TABLE) / sizeof(TIMEZONE_TABLE[0]);
};

#endif // TIMEZONE_DETECTOR_H
