# MP1584EN DC-DC Buck Converter - KiCAD Symbol & Footprint

## Product Information
**Amazon ASIN:** B0B779ZYN1  
**Module:** Generic Mini MP1584EN DC-DC Buck Converter  
**Manufacturer:** Monolithic Power Systems (MPS)

## Specifications

| Parameter | Value |
|-----------|-------|
| Input Voltage | 5-30V (typically 7-28V) |
| Output Voltage | Adjustable (default 5V) |
| Output Current | up to 3A (1.8A typical) |
| Efficiency | ~97% |
| Output Ripple | <30mV |
| Module Size | 17.5 x 12.3 x 4.3 mm |

## Pinout (DIP-6 Configuration)

```
      GND(3)  EN(4)
        |      |
  +-----+------+-----+
  |                 |
  |  MP1584EN      |
  |      MODULE    |
  |                 |
  +-----+------+-----+
        |      |
      FB(5)   GND(6)
      
Left Column (top to bottom): VIN(1), GND(3), FB(5)
Right Column (top to bottom): VOUT(2), EN(4), GND(6)
```

### Pin Descriptions

| Pin # | Name | Type | Description |
|-------|------|------|-------------|
| 1 | VIN | Power In | Input voltage (5-30V) |
| 2 | VOUT | Power Out | Regulated output voltage |
| 3 | GND | Ground | Ground reference (input side) |
| 4 | EN | Input | Enable/Shutdown (optional, tie to GND for always-on) |
| 5 | FB | Input | Feedback for voltage adjustment (optional) |
| 6 | GND | Ground | Ground reference (output side) |

## Usage in KiCAD

### 1. Add the Symbol
1. In the **Schematic Editor**, go to `Preferences → Manage Symbol Libraries`
2. Add the `MP1584EN_Module.kicad_sym` file to your symbol library paths
3. Add the symbol to your schematic from the Symbol Browser

### 2. Add the Footprint
1. In the **PCB Editor**, go to `Preferences → Manage Footprint Libraries`
2. Add the directory containing `MP1584EN_Module.kicad_mod` to your footprint library paths
3. When you assign footprints to your schematic, select `MP1584EN_DIP6` from the library

### 3. Link Symbol to Footprint
1. In the symbol properties, set the **Footprint** field to `MP1584EN_Module:MP1584EN_DIP6`

## Typical Connection Diagram

```
VIN ──[L]──── VOUT
(12V)  │      (5V)
    [R_sense]
       │
       ├──────── LOAD +5V
       
GND ────┬───────── LOAD GND
        │
       [C_out]
        │
       GND

Optional Feedback Network (for voltage adjustment):
VOUT ──[R1]──┬──── FB
            [R2]
             │
            GND

Optional Enable Pin:
EN ──┬─ VIN (always enabled)
     └─ GND (shutdown)
```

## Typical Component Values for 5V Output

| Component | Value | Purpose |
|-----------|-------|---------|
| C_in | 10-22µF (min) | Input filtering |
| C_out | 10-47µF | Output filtering |
| L (on module) | 4.7µH | Energy storage |
| R_sense | 10mΩ (typical) | Current sensing |

## Assembly Notes

1. **Input Decoupling**: Add 10-22µF capacitor close to VIN and GND pins
2. **Output Filtering**: Add 10-47µF capacitor close to VOUT and GND pins
3. **Keepouts**: Leave adequate space around module for heat dissipation
4. **Trace Width**: Use 0.5-1mm traces for input/output power
5. **Via Placement**: Use multiple vias (2-4 per pad) for low impedance connection

## Soldering
- **Temperature**: 250-260°C (peak)
- **Time**: 3-5 seconds
- **Method**: Through-hole soldering (wave or hand soldering recommended)

## Datasheet References
- MP1584EN IC: https://www.monolithicpower.com (search for MP1584EN datasheet)
- Module manufacturers: RCmall, Generic (various suppliers)

## Notes
- Pad diameter: 1.7mm on 0.8mm drill for standard 0.1" breadboard compatibility
- The module includes integrated inductor and switching FET
- Feedback pins (FB, EN) are optional for basic 5V operation
- Module has built-in current limiting and thermal shutdown

## File Contents
- `MP1584EN_Module.kicad_sym` - Symbol library file
- `MP1584EN_Module.kicad_mod` - Footprint definition file
- `MP1584EN_README.md` - This documentation

## License
These symbol and footprint files are provided as-is for personal and commercial use.
