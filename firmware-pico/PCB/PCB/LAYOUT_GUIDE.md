# GPS Mechanical Clock - PCB Layout Guide

## Overview
This guide provides step-by-step instructions for laying out the PCB for the GPS-driven stepper motor mechanical clock display. The design accommodates 6 NEMA 17 stepper motors controlled via Raspberry Pi Pico with GPS time synchronization and TFT display output.

## Board Specifications

- **Target Size**: 150mm × 120mm (adjustable for 6 motors)
- **Layer Count**: 2-layer (or 4-layer for better power distribution with 24V)
- **Trace Width**: 10mil standard, 20mil for 24V power rail
- **Clearance**: 8mil minimum (10mil preferred)
- **Via Size**: 0.3mm (drill) / 0.6mm (pad)
- **Solder Mask**: Standard green on both sides
- **Power Rail**: 24V primary, 5V regulated

## Design Strategy

### Power Distribution (Critical)

1. **Multiple Ground Planes**
   - Use ground plane on Layer 2 (if 2-layer)
   - Connect via multiple vias (every 8mm) to minimize inductance
   - Handle high motor currents (up to 4A per motor)

2. **Power Rails**
   - **24V Rail**: Use wide traces (≥ 25mil) from barrel jack through buck converter to motor power connectors
   - **5V Rail**: Use wide traces (≥ 20mil) from buck converter output to all 5V components
   - **3.3V**: Distributed via Pico's internal regulator
   - Keep 24V and 5V traces separated to minimize noise coupling

3. **Bulk Capacitors**
   - 220µF electrolytic on 24V input (within 10mm of buck converter)
   - 100µF electrolytic on 5V output (within 10mm of buck converter)
   - 10µF tantalum on GPS module supply
   - 100nF decoupling capacitors within 5mm of each IC power pin

### Component Placement Strategy

```
        [Display Connector - External]

    [GPS Module]  [TFT Display]

[Motor Driver]  [PICO]  [Motor Driver]
[U2-U7]        [U1]    [U2-U7]

[USB Connector]  [Power Jack]  [Motor Power]
```

#### Hall Effect Sensor Placement Strategy

Hall effect sensors (A1104) must be positioned to detect a magnet on each motor shaft at the home position:

1. **Sensor Mount Location**
   - Position A1104 sensor 5-10mm from motor shaft
   - Mount perpendicular to magnet approach direction
   - Use small PCB cutout or bracket to hold sensor at fixed distance
   - Ensure magnet on shaft will pass sensor during homing routine

2. **Magnet Placement**
   - Small neodymium magnet (6×3mm cylinder typical) glued to motor shaft
   - Positioned to activate sensor during one specific shaft rotation angle
   - Magnet should pass sensor only once per full rotation (home position marker)

3. **Sensor Routing**
   - Keep sensor wiring separate from motor power lines
   - Use twisted pair for VOUT signal and GND return
   - Shielding optional but recommended if EMI issues occur
   - Route through edge connector to motor assembly

### Recommended Placement:

1. **Raspberry Pi Pico (U1)** - Center of board
   - Horizontal mounting
   - Leave 5mm clearance on all sides for trace routing

2. **Stepper Drivers (U2-U7)** - Arranged around Pico
   - Place drivers 15mm from Pico edges
   - Arrange in logical pairs (Motor 0-1 left, Motor 2-3 top, Motor 4-5 right)
   - All facing same direction for consistent layout

3. **MP1584EN Buck Converter** - Near power connector
   - Input within 20mm of barrel jack
   - Output capacitor within 10mm of IC
   - Thermal relief pads for heat dissipation

4. **GPS Module (NEO-6M)** - Upper left, separate from digital noise
   - Place 30mm from stepper drivers if possible
   - Antenna clear of metal and ground planes (2cm minimum)
   - 10mm clearance from board edge

5. **TFT Display Connector** - Board edge
   - Mount perpendicular to main board surface
   - Position for external display mounting
   - Use right-angle connector (0.1" pitch)

6. **Power Connectors**
   - USB Micro-B: One corner (for programming)
   - Barrel Jack (12V): Opposite corner
   - Motor Power: Third corner (JST-XH 4-pin)

7. **Button Connectors** - Top edge
   - 2-pin connectors for timezone and 24H/12H buttons
   - Use right-angle headers for external mounting

### Signal Routing

#### High-Speed Signals (SPI Display)
- Keep SPI traces (SCK, MOSI, MISO, CS, DC) grouped and short (< 50mm)
- Route together but separate from ground by < 5mm
- Provide ground return plane beneath traces
- Add series resistors (33Ω) if signal integrity issues arise

#### Motor Control Signals (STEP/DIR)
- Route motor signals in twisted pairs when possible
- Keep away from GPS antenna area
- Motor signals can be routed on bottom layer if needed
- Each motor driver should have short traces to corresponding motor connector

#### GPS Serial (UART1)
- Keep RX and TX signals away from fast switching (motors, SPI)
- Separate by 3mm minimum from digital signals
- Use ground guard traces alongside if crossing other signals
- Prefer top layer routing for better shielding

#### Hall Effect Sensor Inputs (A1104)
- Each A1104 sensor connects 5V supply, GND, and analog output
- Route sensor output signal with ground return nearby (twisted if possible)
- Add 100nF capacitor at sensor output for noise filtering
- Connect analog outputs to Pico GPIO or ADC inputs (ADC0-ADC3 on GPIO26-29)
- Keep sensor wiring away from high-current motor traces (minimum 1cm separation)
- If using GPIO comparator, add optional 10kΩ pull-up from 3.3V to GPIO

### Connector Placement

1. **Motor Output Connectors** (JST-XH or similar)
   - 6 × 4-pin connectors (2 coils + GND + NC)
   - Position on bottom edge of board
   - Space 15mm apart for easy access
   - Label clearly: M0 M1 M2 M3 M4 M5 (Hours, Minutes, Seconds)

2. **Hall Sensor Connectors**
   - 6 × 3-pin connectors (VCC, GND, VOUT) for A1104 sensors
   - Mount on motor side of board
   - Label clearly: HS0-HS5 (corresponding to motors)
   - Use JST-PH or similar for reliability

3. **Button Input Connectors**
   - 2 × 2-pin right-angle headers
   - Mount on top edge, clearly labeled
   - Spacing: 10mm apart

4. **Power Input**
   - 24V Barrel Jack (5.5mm × 2.1mm) rated for 4-5A
   - Robust mechanical mounting with strain relief
   - Voltage markings (+24V/−) clearly visible on silkscreen
   - Fuse holder optional but recommended (5-6A fuse)

5. **USB Connection**
   - Micro-B connector for Pico programming
   - Direct connection to Pico via USB pins
   - Consider strain relief cable management

6. **GPS Antenna Connector**
   - SMA or U.FL connector if modular antenna desired
   - Or direct solder pad if integrated antenna

### Via Placement and Thermal Management

1. **Vias through Ground Plane**
   - Place vias every 10mm along power traces
   - Minimum 3 vias per IC power pin for proper return path
   - Use 0.3mm drill / 0.6mm pad size

2. **Thermal Vias (For MP6524 Buck Converter)**
   - Place 3×3 grid of vias under buck converter IC (high current: 2A continuous)
   - Use 0.3mm vias, spaced 1mm apart
   - Connect to ground plane for heat dissipation
   - Consider adding thermal pad on bottom layer if PCB space allows

3. **Return Path Vias**
   - Ensure every signal return path has via back to ground
   - Avoid star-pointing; use plane for returns

### Routing Order (Recommended Sequence)

1. **Power Rails** (12V and 5V)
   - Route wide traces from connectors to all supplies
   - Ensure adequate current capacity (calculate per section)

2. **Ground Connections**
   - Use ground plane (Layer 2)
   - Connect all grounds to plane via multiple vias
   - Create ground plane exclusion zones around sensitive areas (GPS antenna)

3. **High-Speed Signals** (SPI)
   - Route clock and data signals with return ground
   - Keep traces short and grouped

4. **Motor Signals** (STEP/DIR)
   - Route with some flexibility for routing
   - Can be lower-speed, not time-critical

5. **Home Sensors** (GPIO inputs)
   - Final routing, lowest priority
   - Can use remaining board space

6. **Decoupling Capacitors**
   - Place within 5mm of each IC power pin
   - Short vias to ground plane

### Design for Manufacturing (DFM)

1. **Trace & Space**
   - Minimum 10mil spacing for prototype
   - Aim for 12mil for reliability
   - No acute angles (use 45° preferred, minimum 90° acceptable)

2. **Pad Sizes**
   - IC pads: Follow manufacturer recommendations
   - Header pads: Minimum 0.25mm (10mil) diameter
   - Connector pads: 1.5mm diameter minimum

3. **Silkscreen**
   - Label all components clearly
   - Mark polarity for capacitors and diodes
   - Label GPIO pins on Pico pads
   - Mark motor connections (M0-M5, coil order)

4. **Test Points**
   - Add 0.1" test points for:
     - 12V rail
     - 5V rail
     - Ground
     - Key GPIO signals for debugging

5. **Solder Mask Clearance**
   - Keep pads clear with 4mil minimum clearance
   - Allow solder mask to cover trace areas
   - Avoid solder mask between closely-spaced pads

### Recommended PCB Checklist

- [ ] All components placed and positioned
- [ ] Power distribution complete (12V, 5V, 3.3V, GND)
- [ ] All decoupling capacitors placed and routed
- [ ] SPI signals routed and verified
- [ ] Motor signals routed to drivers and connectors
- [ ] Hall sensor (A1104) signals routed with ground returns and filtering capacitors
- [ ] Hall sensor supply (5V) routed separately from analog outputs
- [ ] Button signals routed to Pico
- [ ] GPS UART signals routed (separate from noise)
- [ ] All connectors accessible and labeled
- [ ] No crossing traces (2-layer constraint)
- [ ] Ground plane continuous (check with netlist)
- [ ] Thermal vias under buck converter
- [ ] Mounting holes placed (M3 at corners recommended)
- [ ] Electrical rule check (ERC) passed
- [ ] Design rule check (DRC) passed (10mil minimum)
- [ ] Silkscreen reviewed and corrected
- [ ] Test points added for debugging
- [ ] Solder paste stencil layer verified

### Expected Current Draw

**5V Rail:**
- **Pico**: 50-100mA
- **GPS Module**: 50mA
- **TFT Display**: 30-50mA
- **Stepper Driver Logic** (6x): ~60mA total
- **Total 5V**: ~250-300mA (peak)

**24V Rail (Motor Power):**
- **6 Stepper Motors** (NEMA 11, 0.67A each):
  - Single motor: 0.67A @ 24V = 16W
  - All 6 motors simultaneous: 4A @ 24V = 96W
  - Typical operation (2-3 stepping): 1.3-2A

**Buck Converter**: MP6524 (or equivalent) rated 2A continuous @ 5V output. Sized for simultaneous 5V loads (all LEDs, GPS, display, Pico running at once) while motors run on 24V primary supply.

**Total Barrel Jack Current**: Avg 2A @ 24V (motors) + 0.25A (5V logic) = ~2.3A; Peak 4-5A during full motor acceleration.

### Prototype Assembly Notes

1. **Hand Soldering**
   - Start with smallest components (decoupling caps)
   - Then ICs using toaster oven or hot plate
   - Then connectors and larger components
   - Install buck converter carefully (high current handling)
   - Test power rails before powering up

2. **Initial Testing - CRITICAL FOR 24V SYSTEM**
   - **First**: Check 24V input on power jack (polarity!)
   - **Second**: Verify buck converter output = 5V ±0.25V (no load)
   - **Third**: Check no shorts between 24V and GND
   - **Fourth**: Check no shorts between 5V and GND
   - Only THEN power motors
   - Program Pico via USB before motor connections
   - Test individual motors one at a time initially

3. **Safety Considerations**
   - 24V system can cause severe burns - insulate all exposed connections
   - Use fused power supply or add inline 5-6A fuse
   - Disconnect motors when programming via USB
   - Never hold motor windings while powered (high torque)

4. **GPS Antenna Placement**
   - Keep antenna away from metal and ground planes
   - Best performance: antenna vertical or at 45°
   - Test outdoors for initial lock

---

**Version**: 1.0
**Date**: 2026-09-02
**Status**: Ready for KiCad layout implementation