# Simplified PCB Layout Guide

## Board Size & Design
- **Recommended Size**: 80mm × 100mm (more compact than IC-based design)
- **Layers**: 2-layer minimum (power plane beneficial but not critical)
- **Copper Weight**: 1-2oz adequate (less heat dissipation needed)
- **Trace Width**:
  - 24V rail: 15mil minimum (prefer 20mil)
  - 5V rail: 10mil minimum
  - Signal traces: 8mil minimum
  - Ground vias: abundant, distributed

## Component Placement Strategy

### Zone 1: Power Input (Left Edge)
- J1 (24V connector) at far left corner
- D1 (diode) immediately after connector
- F1 (fuse) in series with D1
- C1 (bulk 470µF) very close to fuse - minimize loop area
- Goal: Create low-inductance 24V rail from input to distribution

### Zone 2: Buck Converter (Left-Center)
- U1 (MP1584) near C1 input
- L1 inductor between U1 output and C3/C4
- C2 (input cap) close to U1 VIN
- C3, C4, C5 clustered near L1 output
- R1, R2 feedback network near U1 FB pin
- Keep feedback trace away from 24V and motor switching noise

### Zone 3: Power Distribution Rails (Bottom)
- Heavy copper pour for +24V rail
- Run +24V along entire bottom edge
- Multiple vias (4-6 per distribution point) to stepper module connectors
- +5V distribution rail from buck converter output
- Decoupling caps C6, C7, C8 at distribution points

### Zone 4: Stepper Module Headers (Right Side)
- Arrange 6 connectors (J4-J9) in 2 columns for symmetry
- Each connector = 3 pins (24V, GND, SIGNAL)
- Spacing: 10-15mm between each module connector
- Direct 24V and GND traces from power rails (wide, short traces)
- Signal traces with protective resistors routed separately

### Zone 5: Motor Connectors (Right Edge)
- Mount J10-J15 (motor outputs) just right of module connectors
- Motor traces routed directly from module connectors
- Short, direct paths minimize EMI
- Twisted pairs recommended if cable runs > 20cm

### Zone 6: Pico Connector (Top or Bottom)
- J16 opposite side from power input for clean separation
- All signal traces route cleanly to stepper module area
- Decoupling cap C8 near Pico supply pins
- Pull-down resistors (R9-R14) placed between Pico and stepper modules

## Schematic Organization

```
INPUT (left)                DISTRIBUTION (center)        OUTPUT (right)
+24V ───D1──F1──C1───────(24V RAIL)──────→ J4-J9
                               │
                            Buck U1                    J10-J15 (motors)
                               │
                            +5V RAIL────→ J16 (Pico)
```

## Critical Design Rules

### Ground Plane (if 2-layer design)
- Dedicate entire bottom layer to ground plane
- All components connected to ground via vias
- Multiple vias under high-current paths (buck converter, 24V rail)
- Via spacing: 5-10mm grid pattern

### Signal Integrity
- STEP/DIR signals:
  - 100Ω series resistor near Pico output
  - 10kΩ pull-down near stepper module input
  - Trace length kept < 15cm if possible
  - Ground return vias placed every 2-3cm along signal traces

### Power Delivery
- 24V rail: Continuous heavy copper pour on bottom or internal layer
- Multiple connection points from distribution to each stepper header
- C1 bulk cap directly fed from fuse
- C6 bulk cap for 24V distribution redundancy
- Decoupling caps (C7, C8) close to distribution points

### Trace Routing Priority
1. 24V input → Fuse → C1 (shortest possible)
2. Buck converter feedback (clean routing away from noise)
3. 24V distribution rail to all module headers
4. 5V distribution from buck output
5. GND returns (via ground plane)
6. STEP/DIR signals with series resistors
7. Motor phase signals (twisted pair if long runs)
8. Pico connector signals

## Simplified Component Placement Tips

### Buck Converter Section
- Keep input (VIN, GND) and output (VOUT, GND) sides separated
- Inductor L1 in the middle
- Use wide traces to/from L1 (20+ mil)
- Feedback resistors off to the side, away from power

### Stepper Module Distribution
- 24V rail should be "backbone" of PCB
- Module headers tapped directly to this backbone
- Ground plane provides return paths automatically
- Minimal trace routing needed for power

### Signal Integrity Setup
```
Pico GPIO ──R_series(100Ω)── Signal trace ──|
                                             ├── Stepper Module
                                        ┌────|
                                  R_pd (10kΩ)
                                        │
                                       GND
```

## Manufacturing Simplifications

### No Thermal Concerns
- Stepper modules handle heat internally
- No thermal vias needed on this PCB
- Standard solder paste thickness fine

### Solder Mask & Silkscreen
- Label all connectors: J1 (24V), J2-J7 (Stepper 1-6), J8-J13 (Motor 1-6), J14 (Pico)
- Mark +24V rail clearly
- Polarity marks on C1 (bulk cap)
- Component values on key parts (U1, C1, L1)

### Test Points (Optional but helpful)
- +24V after fuse
- +5V from buck converter
- GND reference (multiple locations)
- STEP/DIR signal before stepper module (for oscilloscope testing)

## Assembly & Testing

### Assembly Order
1. **Surface Mount**: All SMD components (SMD resistors, capacitors, IC)
   - Buck converter section first
   - Decoupling caps throughout
   - Series and pull-down resistors for signals

2. **Through-Hole**: Connectors
   - Power connector J1 (24V input)
   - Stepper module headers (J4-J9)
   - Motor connectors (J10-J15)
   - Pico header (J16)
   - Electrolytic capacitors (C1, C6)

### Pre-Power Checklist
- [ ] Visually inspect all solder joints
- [ ] Continuity test: +24V rail (should be continuous)
- [ ] Continuity test: +5V rail (should be continuous)
- [ ] Continuity test: GND plane (everywhere)
- [ ] Resistance test: +24V to GND (should be > 10kΩ before power)
- [ ] Resistance test: +5V to GND (should be > 10kΩ before power)

### Power-Up Testing
1. Apply 24V with current-limiting power supply
2. Check +24V rail voltage (should be ~24V)
3. Check +5V output from buck converter (should be 5.0V ±0.25V)
4. If voltages correct, connect Pico and stepper modules one at a time
5. Test each stepper module independently with signal generator

## PCB Design Checklist
- [ ] 24V input protection (diode + fuse) in place
- [ ] Bulk capacitor C1 close to fuse
- [ ] Buck converter feedback network correct (5V output)
- [ ] All stepper module headers have 24V + GND routed
- [ ] STEP/DIR signals have series resistors (100Ω each)
- [ ] STEP/DIR signals have pull-down resistors (10kΩ each)
- [ ] Ground plane provides continuous return path
- [ ] Decoupling capacitors placed near power distribution points
- [ ] Pico connector has all required signals routed
- [ ] Motor connectors clearly labeled and routed directly from modules
- [ ] No acute angles in traces (use 45° or curves)
- [ ] All connectors clearly labeled in silkscreen

## Cost & Time Savings

**Simplified Approach vs. IC-Based:**
- Component cost: ~$22 vs. ~$27 (same or cheaper!)
- PCB complexity: Much simpler (faster layout)
- Assembly: Fewer parts to solder (faster/easier)
- Testing: Easier to debug (swap modules)
- Reliability: Better (module handles driver complexity)

**Recommended PCB Manufacturer:**
- JLCPCB: ~$10-15 for 5 boards
- PCBWay: ~$12-18 for 5 boards
- Lead time: 5-7 days standard
