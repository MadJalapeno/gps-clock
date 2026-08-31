#include "TimezoneDetector.h"

// Initialize static const
constexpr TimezoneDetector::TimezoneRegion TimezoneDetector::TIMEZONE_TABLE[];

int TimezoneDetector::detectTimezone(double latitude, double longitude) {
    // Normalize longitude to -180 to 180 range
    double lon = longitude;
    if (lon > 180.0) {
        lon -= 360.0;
    }
    if (lon < -180.0) {
        lon += 360.0;
    }

    // Search through timezone table for matching region
    for (int i = 0; i < TIMEZONE_TABLE_SIZE; i++) {
        const TimezoneRegion& region = TIMEZONE_TABLE[i];

        // Check if coordinates fall within this region
        if (latitude >= region.minLat && latitude <= region.maxLat) {
            if (lon >= region.minLon && lon <= region.maxLon) {
                return region.utcOffset;
            }
        }
    }

    // No match found - default to UTC
    return 0;
}

const char* TimezoneDetector::getTimezoneName(double latitude, double longitude) {
    // Normalize longitude to -180 to 180 range
    double lon = longitude;
    if (lon > 180.0) {
        lon -= 360.0;
    }
    if (lon < -180.0) {
        lon += 360.0;
    }

    // Search through timezone table for matching region
    for (int i = 0; i < TIMEZONE_TABLE_SIZE; i++) {
        const TimezoneRegion& region = TIMEZONE_TABLE[i];

        // Check if coordinates fall within this region
        if (latitude >= region.minLat && latitude <= region.maxLat) {
            if (lon >= region.minLon && lon <= region.maxLon) {
                return region.name;
            }
        }
    }

    // No match found - return UTC
    return "UTC";
}
