# GPS Clock Stepper Driver PCB

## Overview
This PCB design integrates 6 TMC2208 stepper drivers for NEMA 11 motors with a Raspberry Pi Pico GPS clock.

## Power Architecture
- **24V Input**: Main power supply connector with reverse-polarity protection and fuse
- **Buck Converter**: MP1584 converts 24V to 5V for Pico and logic circuits
- **Motor Supply**: Direct 24V to all stepper drivers
- **Logic Supply**: 5V regulated for Pico and driver logic

## Key Features
- Robust power delivery with bulk and local decoupling capacitors
- Individual TMC2208 driver sections with complete support circuitry
- Motor and stepper connectors for each driver
- Pico connector for programming and GPS interface
- Pull-down resistors on STEP/DIR signals
- Current sense resistors for driver programming
- Reverse polarity protection on 24V input

## Design Notes
- All drivers share 24V and GND planes for low impedance
- Each driver has local 100µF + 10µF + 0.1µF capacitor network
- 470µF bulk capacitor on 24V rail for transient response
- TMC2208 logic operates at 5V (compatible with Pico 3.3V outputs via pull-ups)
- Recommend 2oz copper for power planes for heat dissipation

## Assembly Notes
1. Start with bulk capacitors and buck converter
2. Install driver support components (resistors, capacitors)
3. Mount TMC2208 drivers with thermal interface to PCB
4. Install connectors last
5. Test 24V and 5V rails before connecting Pico

## Testing
1. Verify 5V output before powering Pico
2. Check current with multimeter on sense resistor
3. Program current limit via TMC2208 interface
