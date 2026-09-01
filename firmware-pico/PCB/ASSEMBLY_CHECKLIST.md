# PCB Assembly & Setup Checklist

## Pre-Assembly

- [ ] Review FINAL_SCHEMATIC_WITH_HALL.txt
- [ ] Print out BOM_WITH_HALL_SENSORS.csv
- [ ] Order all parts from Digi-Key (~$8 total)
- [ ] Order PCB from JLCPCB or PCBWay (~$10-15)
- [ ] Gather tools: soldering iron, solder, flux, multimeter, tweezers

## Parts Received

- [ ] Check all Digi-Key parts against BOM
- [ ] Verify PCB quality (no cracks, traces intact)
- [ ] Test continuity: 24V rail, 5V rail, GND plane
- [ ] Verify Pico, GPS, display, buck module, stepper modules available

## SMD Component Assembly (If Hand Soldering)

### Bulk Capacitors (Through-Hole)
- [ ] C1 (470µF 50V) - solder pads first, then leads
- [ ] Verify polarity: + stripe toward marked side

### Resistors & Small Caps (SMD 0805/1206)
- [ ] R1-R6 (100Ω pull-ups for hall sensors) - use solder paste or hand solder
- [ ] R7-R12 (100Ω series resistors for STEP/DIR)
- [ ] R13-R18 (10kΩ pull-downs for STEP/DIR)
- [ ] C2 (100nF input filter)
- [ ] C3, C4, C5 (5V output filtering)
- [ ] C6-C11 (100nF hall sensor bypass caps)
- [ ] C12-C17 (10nF hall sensor debounce caps)

### Hall Effect Sensors (Through-Hole TO-92)
- [ ] U1 (A3144E sensor #1) - orientation matters! Flat side = marker
- [ ] U2-U6 (additional sensors)
- [ ] Verify each with continuity test

### Test Before Connectors
- [ ] Power up and check: 24V rail = 24V, 5V rail = 5V
- [ ] If incorrect, troubleshoot (check diode polarity, fuse continuity)

## Connector Assembly (Final Step)

### Power Connector (J1)
- [ ] Solder 24V and GND leads
- [ ] Insulate exposed leads with heat shrink
- [ ] Test continuity to 24V rail

### Buck Converter Connector (J2)
- [ ] 3 pins: 24V, GND, 5V output
- [ ] Verify traces to power rails

### Stepper Module Connectors (J3-J8)
- [ ] 6× 3-pin headers
- [ ] Label: Stepper 0, 1, 2, 3, 4, 5
- [ ] Each needs: 24V, GND, STEP/DIR signal

### Hall Sensor Connectors (J9-J14)
- [ ] 6× 3-pin headers
- [ ] Label: Home 0, 1, 2, 3, 4, 5 (or Hours Tens, Hours Ones, etc.)
- [ ] Pins: 5V, GND, OUTPUT to Pico GPIO

### Pico Connector (J15)
- [ ] 2×20 40-pin header
- [ ] Must align with Pico pin layout
- [ ] Verify: GPIO 0, 1 = GPS; GPIO 3, 5, 7, 9, 11, 13 = Home sensors; etc.

## Pre-Power Testing

### Continuity Tests
- [ ] 24V rail continuity (should be <0.5Ω)
- [ ] 5V rail continuity (should be <0.5Ω)
- [ ] GND plane continuity (multiple points, all <0.5Ω)
- [ ] No continuity between 24V and GND (should be >10kΩ)
- [ ] No continuity between 5V and GND (should be >10kΩ)

### Visual Inspection
- [ ] All solder joints shiny and full
- [ ] No bridges (solder connecting unintended pads)
- [ ] No cold joints (dull, cracked solder)
- [ ] All components seated fully (no lifted pads)
- [ ] Correct polarities on capacitors C1 (bulk), all electrolytics

## Power-Up Sequence

### Step 1: 24V Supply Test
1. Connect 24V power supply (with current-limiting if possible)
2. DO NOT connect Pico yet
3. Measure 24V rail with multimeter
   - Should read: 24.0V ±0.5V
   - If not: Stop and troubleshoot (diode, fuse, PCB traces)

### Step 2: Buck Converter Test
1. With 24V still applied
2. Measure 5V rail output
   - Should read: 5.0V ±0.25V
   - If not: Check buck module connections, C3/C4/C5 capacitors

### Step 3: Hall Sensor Test (Without Pico)
1. Measure voltage on each sensor OUTPUT pin:
   - Should read ~5V (pulled up by R1-R6)
   - With magnet near: Should drop to ~0V
   - Without magnet: Should return to ~5V
2. Test each of 6 sensors individually
3. If any sensor fails: Check pull-up resistor, bypass cap, sensor IC

### Step 4: Connect Pico & Verify Boot
1. With 24V and 5V confirmed good:
2. Carefully insert Pico into J15 connector
3. Connect USB to Pico (for serial console)
4. Open serial monitor at 115200 baud
5. You should see startup messages:
   ```
   === GPS Mechanical Clock ===
   [SETUP] LED initialized
   [SETUP] TFT display initialized
   ...
   ```

## Firmware Configuration

### Enable Homing in Configuration.h
```cpp
#define ENABLE_MOTOR_HOMING 1  // Change from 0 to 1
```

### Set Correct GPIO Pins
Verify these match your PCB in Configuration.h:
```cpp
#define HOURS_TENS_HOME_PIN      13   // GPIO 13
#define HOURS_ONES_HOME_PIN      11   // GPIO 11
#define MINUTES_TENS_HOME_PIN    9    // GPIO 9
#define MINUTES_ONES_HOME_PIN    7    // GPIO 7
#define SECONDS_TENS_HOME_PIN    5    // GPIO 5
#define SECONDS_ONES_HOME_PIN    3    // GPIO 3

#define HOURS_TENS_STEP_PIN      12   // GPIO 12
#define HOURS_ONES_STEP_PIN      10   // GPIO 10
#define MINUTES_TENS_STEP_PIN    8    // GPIO 8
#define MINUTES_ONES_STEP_PIN    6    // GPIO 6
#define SECONDS_TENS_STEP_PIN    4    // GPIO 4
#define SECONDS_ONES_STEP_PIN    2    // GPIO 2
```

### Rebuild & Upload
```bash
platformio run --target upload
```

## First Run - Homing Sequence

### What Should Happen
1. Pico boots and reads GPS
2. Firmware detects GPS has no fix yet
3. Homes each motor in sequence:
   - Pulses STEP signal on stepper module
   - Motor moves
   - When hall sensor triggers (magnet detected): Motor stops
   - Firmware verifies position
4. Once all motors homed: Waits for GPS fix
5. When GPS provides time: Motors move to display time

### Monitoring Homing
1. Watch serial console for status messages
2. Listen for motor sounds (clicking = stepping, smooth = moving)
3. After each motor homes: Console should show "Motor X homed"
4. Total homing time: ~30-60 seconds for all 6 motors

### If Motor Doesn't Home
- Check hall sensor magnet placement (should trigger at desired position)
- Verify GPIO wire connection
- Test sensor manually with magnet
- Check firmware homing logic enables that motor
- Verify stepper module is powered and functional

## Stepper Driver Module Connection

### Typical Stepper Module Pinout (check your module docs):
- VCC: 24V supply
- GND: Ground
- STEP: Pulse input (from Pico GPIO via 100Ω resistor)
- DIR: Direction input (from Pico GPIO via 100Ω resistor)
- OUT A+, A-, B+, B-: Motor phase connections

### Motor Winding Connections
For NEMA 11 motors:
- A+ and A- = Motor coil A
- B+ and B- = Motor coil B
- Order matters for direction

## Testing Checklist

### GPS Module
- [ ] LED blinks when acquiring signal
- [ ] Serial shows satellite count increasing
- [ ] Time updates once fix achieved

### Display
- [ ] TFT shows welcome message on startup
- [ ] Displays update every 2 seconds
- [ ] Shows time in UTC and local (with timezone offset)

### Buttons
- [ ] Timezone button (GPIO 26) cycles through offsets
- [ ] 24H button (GPIO 27) toggles time format
- [ ] Serial confirms button presses

### Hall Sensors
- [ ] Each sensor measured ~5V with no magnet
- [ ] Each sensor drops to ~0V when magnet near
- [ ] Firmware recognizes all 6 home positions

### Motors
- [ ] Each motor responds to STEP/DIR signals
- [ ] Moving in correct direction
- [ ] Stopping at home position (magnet detection)
- [ ] Display rotates smoothly through homing sequence

## Troubleshooting Guide

| Problem | Symptoms | Solution |
|---------|----------|----------|
| 24V rail low | ~18V instead of 24V | Check fuse continuity, diode polarity |
| 5V rail low | ~3V instead of 5V | Check buck module connections, C3/C4 caps |
| Hall sensor always reads 5V | Magnet present but no trigger | Move magnet closer or check sensor IC |
| Motor doesn't home | STEP/DIR signals present but no motion | Check stepper module power, verify wiring |
| GPS not locking | Satellite count stays at 0 | Move antenna to window/outside, verify GPS module |
| Display shows garbage | Corrupted text | Check SPI wiring for TFT (GPIO 17-21) |
| Pico not booting | No serial output | Check 5V rail, verify USB connection, check buck output |

## Final Setup

Once everything tests good:
1. Place circuit in enclosure
2. Mount magnetic detents on motor shafts
3. Calibrate display position (manually set digits to match actual position)
4. Set timezone offset with button
5. Connect to GPS and let it acquire fix
6. Motors automatically home and display correct time!

## Documentation to Keep

- [ ] PCB schematic (FINAL_SCHEMATIC_WITH_HALL.txt)
- [ ] BOM with part numbers (BOM_WITH_HALL_SENSORS.csv)
- [ ] Digi-Key receipt (for warranty/returns)
- [ ] Motor specifications (11HS12-0674S datasheet)
- [ ] GPS module notes
- [ ] Hall sensor orientation (flat side = marker)
- [ ] GPIO pin assignments (saved in firmware)

---

**You're building a professional-grade GPS clock with hardware homing!**
This is a solid project with all the bells and whistles.
