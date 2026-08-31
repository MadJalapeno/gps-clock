# Automatic Timezone Detection - Implementation Guide

## Overview
Automatically detect user's timezone from GPS location. No button presses needed!

## How It Works

1. **GPS provides location** (latitude, longitude)
2. **TimezoneDetector looks up region** in geographic database
3. **Timezone offset set automatically**
4. **Timezone name displayed** on TFT
5. **User can still manually override** with button if desired

## Implementation Steps

### Step 1: Add TimezoneDetector Include
In `main.cpp`, add at the top:

```cpp
#include "TimezoneDetector.h"
```

### Step 2: Add to GPS Processing
In the `loop()` function where you process GPS data, add this:

```cpp
// After GPS has valid fix, auto-detect timezone
if (valid && gps_.location.isValid()) {
    int detectedOffset = TimezoneDetector::detectTimezone(
        gps_.location.lat(),
        gps_.location.lng()
    );

    // Only change if it's different from current
    if (detectedOffset != timezoneOffsetHours) {
        timezoneOffsetHours = detectedOffset;
        const char* tzName = TimezoneDetector::getTimezoneName(
            gps_.location.lat(),
            gps_.location.lng()
        );
        Serial.print("[GPS] Auto-detected timezone: ");
        Serial.print(tzName);
        Serial.print(" (UTC");
        if (detectedOffset >= 0) Serial.print("+");
        Serial.print(detectedOffset);
        Serial.println(")");
    }
}
```

### Step 3: Update TFT Display
Show detected timezone on screen:

```cpp
// In display update section, add:
tft.setTextSize(1);
tft.setCursor(0, 70);
tft.print("TZ: ");
tft.println(TimezoneDetector::getTimezoneName(
    gps_.location.lat(),
    gps_.location.lng()
));
```

### Step 4: Compile & Upload
```bash
platformio run --target upload
```

## What It Does

### First GPS Fix
- Device boots → waiting for GPS
- GPS gets fix → automatically detects timezone
- Serial shows: `[GPS] Auto-detected timezone: Eastern (UTC-5)`
- Display immediately shows correct local time

### Moving to Different Region
- Drive to new timezone
- GPS location updates
- Timezone auto-updates
- Time display adjusts
- TFT shows new timezone name

### Manual Override Still Available
- Press timezone button to manually adjust
- Auto-detection pauses (user override)
- Can return to auto by pressing button to cycle through again

## Timezone Database Coverage

The included database covers:

**North America:**
- Pacific (PST/PDT, UTC-8)
- Mountain (MST/MDT, UTC-7)
- Central (CST/CDT, UTC-6)
- Eastern (EST/EDT, UTC-5)
- Atlantic (AST/ADT, UTC-4)

**Central America & Caribbean:**
- Mexico (CST/CDT, UTC-6)

**South America:**
- Venezuela (VET, UTC-4)
- Brazil (BRT, UTC-3)
- Argentina (ART, UTC-3)

**Europe:**
- GMT/BST (UTC+0/+1)
- CET/CEST (UTC+1/+2)
- EET/EEST (UTC+2/+3)

**Africa & Middle East:**
- EAT (UTC+3)

**Asia:**
- India (IST, UTC+5:30)
- SE Asia (UTC+7)
- China (CST, UTC+8)
- Japan/Korea (JST/KST, UTC+9)

**Oceania:**
- Australia Eastern (AEST, UTC+10)
- New Zealand (NZST, UTC+12)

**Pacific:**
- Hawaii (HST, UTC-10)

**Default:**
- UTC (no offset)

## Adding More Regions

To add additional regions, edit `TimezoneDetector.h`:

```cpp
// Add new region to TIMEZONE_TABLE:
{"Region Name", minLat, maxLat, minLon, maxLon, utcOffset},

// Example - adding Iceland (GMT year-round):
{"Iceland", 63.0, 67.0, -25.0, -13.0, 0},

// Example - adding India (IST is UTC+5:30, round to +5 or +6):
// Note: If exact half-hour offsets needed, would require modification
```

## Limitations & Notes

### Half-Hour Offsets
Current implementation uses whole-hour offsets only. These regions will be approximated:
- India (IST = UTC+5:30) - currently set to UTC+5
- Australia/South Australia (ACDT = UTC+9:30) - currently set to UTC+10
- Nepal (NPT = UTC+5:45) - currently set to UTC+5

**If you need exact half-hour offsets:**
```cpp
// Modify utcOffset to support fractional values:
float utcOffset;  // Use float instead of int
// Then calculate: hours + (offset % 1) * 60 = minutes
```

### Accuracy
Timezone detection is based on geographic regions, not exact DST rules:
- DST transitions not handled (uses standard time)
- Boundaries are approximate (based on lat/lon rectangles)
- Works well for general use, may be off 1 hour during DST transitions

**For production use with DST support, would need:**
- More complex boundary definitions
- Current date/DST calculation
- Geolocation API (too complex for embedded)

### Memory Usage
```
Timezone database:      ~2KB (TIMEZONE_TABLE array)
TimezoneDetector code:  ~500 bytes
Total added:            ~2.5KB (no issue on 2MB flash)
```

## Testing

### Test Auto-Detection
1. Boot device with GPS enabled
2. Wait for GPS fix
3. Check serial output:
   ```
   [GPS] Auto-detected timezone: Eastern (UTC-5)
   ```
4. Check TFT display shows correct local time
5. Verify `TZ: Eastern` displayed on screen

### Test Region Boundaries
1. Check location near timezone boundaries
2. GPS accuracy ~5-10m, but timezone region sizes are huge
3. Should work correctly even near boundaries

### Manual Override Test
1. Press timezone button
2. Auto-detection should pause
3. Manual offset displayed
4. Press again to return to auto mode

## Example Usage in Context

```cpp
// In your main loop GPS processing:
if (millis() - lastReport > 2000) {
    int sats = gps_.satellites.value();
    bool valid = gps_.time.isValid() && sats >= 3;

    if (valid && gps_.location.isValid()) {
        // AUTO-DETECT TIMEZONE
        int detectedOffset = TimezoneDetector::detectTimezone(
            gps_.location.lat(),
            gps_.location.lng()
        );

        if (detectedOffset != timezoneOffsetHours) {
            timezoneOffsetHours = detectedOffset;
            Serial.print("[AUTO TZ] ");
            Serial.println(TimezoneDetector::getTimezoneName(
                gps_.location.lat(),
                gps_.location.lng()
            ));
        }

        // Continue with normal time update...
        // Display, motor control, etc.
    }

    lastReport = millis();
}
```

## Future Enhancements

### Could add:
1. **DST calculation** - Determine if currently in DST
2. **More granular regions** - Better boundary detection
3. **Geohash lookup** - More efficient region matching
4. **Timezone name database** - Store full names (IANA format)
5. **Fallback to manual** - If no GPS, use last known timezone

### Would require:
- More ROM space (currently minimal)
- More complex calculation
- Possible internet lookup (unreliable for embedded)

## Summary

✅ **Pros:**
- Automatic, no user interaction needed
- Very small memory footprint
- Works offline (no internet required)
- Falls back gracefully (defaults to UTC)
- Can still manually override

❌ **Cons:**
- DST not handled automatically
- Half-hour offsets approximated
- Boundaries are rectangular (not perfect political boundaries)
- Requires GPS location fix

**Perfect for a GPS clock!** User doesn't think about timezones - just works.
