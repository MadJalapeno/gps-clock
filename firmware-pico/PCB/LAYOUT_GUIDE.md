# PCB Layout Guidelines

## Board Size & Layers
- **Recommended Size**: 100mm × 80mm (suitable for 6 driver sections + buck converter)
- **Layers**: 4-layer (power, signal, signal, ground) or minimum 2-layer with ground plane
- **Copper Weight**: 2oz+ for power planes (heat dissipation)
- **Trace Width**:
  - 24V rail: 20mil minimum (prefer 30mil for low inductance)
  - 5V rail: 15mil minimum
  - Signal traces: 8mil minimum
  - Ground vias: abundant, distributed

## Component Placement Strategy

### Zone 1: Power Input (Left Edge)
- Place J1 (24V connector) at far left corner
- Immediately next to connector: D1 (diode) + F1 (fuse) in series
- Very close to fuse: C1 (bulk 470µF capacitor) - minimize loop area
- This zone handles high current, keep traces wide and short

### Zone 2: Buck Converter (Left-Center)
- Place U1 (MP1584) near C1 for tight input coupling
- L1 inductor between U1 output and C3/C4
- Input capacitors (C2) close to U1 VIN pin
- Output capacitors (C3, C4, C5) clustered near L1 output
- Feedback network (R1, R2) near U1 feedback pin
- Keep feedback trace away from high-current paths

### Zone 3: TMC2208 Driver Array (Right Side)
- Arrange 6 drivers in 2 columns (3 per column) for symmetry
- Equal spacing between drivers (20-25mm preferred)
- Each driver gets dedicated local capacitor cluster:
  - C_vm1 (100µF bulk)
  - C_vm2 (10µF ceramic)
  - C_vm3 (100nF ceramic)
  - C_vio (100nF ceramic)
  - All within 5mm of driver pins

### Zone 4: Motor Connectors (Right Edge)
- Place motor connectors (J2-J7) at right edge
- Route motor traces directly from driver outputs to connectors
- Minimize loop area for motor phase traces
- Keep motor traces away from logic signals

### Zone 5: Pico Connector (Top or Bottom)
- Place J8 on opposite edge from power input for clean signal routing
- Route STEP/DIR signals from Pico to each driver with consistent path lengths
- Add 100Ω series resistor near Pico for signal protection
- Pull-down resistors (R9-R20) placed near driver inputs

## Critical Design Rules

### Power Plane Topology
```
Layer 1: +24V plane (top side)
Layer 2: GND plane (internal)
Layer 3: GND plane (internal)
Layer 4: +5V plane (bottom side)
```

### Via Strategy
- Place vias frequently under all power planes
- Via pads: 0.3mm diameter minimum, 0.4mm spacing
- Thermal vias: under driver chips and power resistors
- Ground vias: at least 4 per driver

### Trace Routing Priority
1. **24V rail**: Shortest path from battery → buck input → all drivers (wide trace)
2. **GND returns**: Abundant vias to ground plane from every driver
3. **5V rail**: From buck converter output to all logic components
4. **STEP/DIR signals**: Routed with 100Ω series resistor, then to 10kΩ pull-down
5. **Motor phases**: Direct from driver to connector, isolated from logic

### High-Current Paths
- D1→F1→C1: Keep trace width 30mil, length < 5cm
- C1→L1→C3: Wide trace (25mil), short path
- U1 pins to capacitors: Use at least 15mil traces
- Driver VM pin to capacitors: Dedicated 20mil traces

## Thermal Considerations

### Power Dissipation
- TMC2208 @ 1A per phase: ~0.5W per driver (3W total for 6 drivers)
- MP1584 buck converter: ~0.3-0.5W typical
- Sense resistors: 0.11Ω × I² = 0.1W typical

### Heat Management
- Pad drivers with thermal vias (4 vias minimum per driver)
- Copper pour around sense resistors
- Consider thermal pads on back layer for drivers if possible
- Adequate solder paste thickness (0.15-0.2mm) for thermal coupling

## Signal Integrity

### STEP/DIR Signals
- Route from Pico with 100Ω series resistor
- Place 10kΩ pull-down resistor to GND at driver input
- Trace length < 10cm preferred
- Keep signal traces away from 24V and motor traces
- Use ground plane return paths (vias near each signal point)

### Feedback Network (Buck Converter)
- Feedback trace from R1/R2 junction to U1 FB pin
- Keep feedback trace short and away from high-current paths
- Shield with ground if available

## Creepage & Clearance
- 24V to GND: minimum 3mm creepage distance
- 24V to 5V: minimum 2mm creepage distance
- Use solder mask to define creepage paths
- Test points recommended for debugging: +24V, +5V, GND

## Manufacturing Recommendations

### Solder Mask & Silkscreen
- Open vias under components (100mil keepout from vias under ICs)
- Silkscreen reference designators on both sides
- Polarity marks for C1 (bulk capacitor) and all polarized components
- Component value labels for key parts (U1, C1, sense resistors)

### Testing Points
- Add test pads for:
  - +24V input (before diode)
  - +5V output (buck converter)
  - GND (multiple locations)
  - Motor output nodes (for driver verification)

## Assembly Order
1. **Reflow first pass** (SMD):
   - All SMD resistors and capacitors (except bulk C1)
   - IC chips (U1, U2-U7)
   - Sense resistors (R3-R8)

2. **Wave solder or hand solder** (THD):
   - J1 (power connector)
   - Bulk capacitor C1
   - Motor connectors (J2-J7)
   - Pico connector (J8)

3. **Post-solder**:
   - Inspect solder joints with microscope
   - Test 24V and 5V rails before powering up
   - Program current limits via Pico I2C if available

## Design Checklist
- [ ] All 6 TMC2208 drivers have complete capacitor network
- [ ] Ground plane connectivity verified (continuity test)
- [ ] No acute angles in traces (45° or curves preferred)
- [ ] Sense resistors have ferrite beads or capacitors
- [ ] Pull-down resistors on all STEP/DIR signals
- [ ] Series resistors on signal lines from Pico
- [ ] Reverse polarity diode on 24V input
- [ ] Adequate trace width for current (check amperage/trace width charts)
- [ ] Motor connectors properly labeled (Motor 1-6)
- [ ] Pico connector pinout matches Configuration.h
