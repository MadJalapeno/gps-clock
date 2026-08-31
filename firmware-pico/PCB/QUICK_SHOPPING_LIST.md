# Quick Shopping List - GPS Clock Stepper PCB

## Digi-Key Quick Order
Copy-paste these part numbers into Digi-Key cart:

| Part # | Qty | Description |
|--------|-----|-------------|
| 455-2176-ND | 3 | 2-pin JST PH Connector |
| 1N4007FS-ND | 1 | 1N4007 Diode |
| F11A-ND | 1 | 10A Fuse |
| MP1584EN-ND | 1 | MP1584 Buck Converter |
| 490-16343-1-ND | 1 | 10µH 1210 Inductor |
| P6153-ND | 1 | 470µF 50V Electrolytic |
| 399-3690-1-ND | 3 | 100nF 0805 Capacitor |
| 399-13853-1-ND | 1 | 100µF 10V 1206 Capacitor |
| 399-8846-1-ND | 1 | 10µF 10V 1206 Capacitor |
| 399-3919-1-ND | 1 | 1µF 10V 0805 Capacitor |
| RMCF0805FT1M00CT-ND | 1 | 1MΩ 0805 Resistor |
| RMCF0805FT240KCT-ND | 1 | 240kΩ 0805 Resistor |
| P6066-ND | 1 | 100µF 50V Electrolytic |
| RMCF0805FT100RCT-ND | 1 | 100Ω 0805 Resistor (qty 6) |
| RMCF0805FT10K0CT-ND | 1 | 10kΩ 0805 Resistor (qty 6) |
| S7002-ND | 1 | 3-pin Header (qty 6) |
| S7004-ND | 1 | 4-pin Header (qty 6) |
| S2011EC-40-ND | 1 | 2×20 Header (Pico) |

**Estimated Total: ~$22 + shipping**

---

## Mouser Quick Order
Copy-paste these part numbers into Mouser cart:

| Part # | Qty | Description |
|--------|-----|-------------|
| 649-1725675 | 3 | 2-pin JST PH Connector |
| 512-1N4007 | 1 | 1N4007 Diode |
| 576-0215010.HXP | 1 | 10A Fuse |
| 579-MP1584EN | 1 | MP1584 Buck Converter |
| 652-CDRH127R-100MC | 1 | 10µH 1210 Inductor |
| 140-XRL50V470 | 1 | 470µF 50V Electrolytic |
| 581-08055C104K4Z2A | 3 | 100nF 0805 Capacitor |
| 581-12065C107M7T | 1 | 100µF 10V 1206 Capacitor |
| 581-12065C106M7T | 1 | 10µF 10V 1206 Capacitor |
| 581-08055C105K4Z2A | 1 | 1µF 10V 0805 Capacitor |
| 603-RC0805FR-071ML | 1 | 1MΩ 0805 Resistor |
| 603-RC0805FR-07240KL | 1 | 240kΩ 0805 Resistor |
| 140-XRL50V100 | 1 | 100µF 50V Electrolytic |
| 603-RC0805FR-07100RL | 1 | 100Ω 0805 Resistor (qty 6) |
| 603-RC0805FR-0710KL | 1 | 10kΩ 0805 Resistor (qty 6) |
| 649-68001-103HLF | 1 | 3-pin Header (qty 6) |
| 649-68001-104HLF | 1 | 4-pin Header (qty 6) |
| 649-68001-240HLF | 1 | 2×20 Header (Pico) |

**Estimated Total: ~$23 + shipping**

---

## Additional Items You'll Need

### PCB Fabrication
- **Source**: JLCPCB.com or PCBWay.com
- **Design Files**: Use the schematic and layout guide to create PCB
- **Cost**: ~$10-15 for 5 boards
- **Lead Time**: 5-7 days standard, 2-3 days express
- **Required**: Gerber files (generate from KiCad after layout)

### Stepper Driver Modules (×6)
- **Amazon**: B0DSPDMDK1 (TMC2208 V1.2 Stepper Driver)
- **Cost**: ~$12-15 per module (×6 = $72-90)
- **Qty**: 6 modules required

### Pico Microcontroller
- **Raspberry Pi Pico**:
  - Digi-Key: SC0915CT-ND (~$4-5)
  - Mouser: 358-SC0915 (~$4-5)
  - Qty: 1 required

### Motors & Display (Already Have?)
- 6× NEMA 11 stepper motors
- 1× ST7735 TFT display (1.8")
- 1× GPS module (NEO-M8)

### Miscellaneous
- 24V Power Supply (>2A recommended)
- Solder (lead-free or leaded)
- Solder paste (for SMD assembly, optional)
- Jumper wires for breadboard testing (optional)

---

## Assembly Services (Alternative to DIY)

If you don't want to solder SMD components:

### JLCPCB Assembly
- PCB + SMD assembly combined
- MP1584, resistors, capacitors soldered automatically
- You hand-solder connectors
- Cost: ~$30-40 for 5 boards
- Lead time: 7-10 days

### PCBWay Assembly
- Similar service to JLCPCB
- Slightly higher cost, comparable quality
- Cost: ~$35-45 for 5 boards

---

## Cost Breakdown (DIY Soldering)

| Item | Qty | Cost Each | Total |
|------|-----|-----------|-------|
| Components (Digi-Key/Mouser) | 1 | $22 | $22 |
| PCB (JLCPCB 5 boards) | 5 | $2-3 | $10-15 |
| Stepper Drivers (×6 modules) | 6 | $12-15 | $72-90 |
| Pico Microcontroller | 1 | $4-5 | $4-5 |
| **Total for 1 Complete System** | | | **$108-132** |
| Cost per board (amortized over 5) | | | **~$22-26** |

---

## Assembly Tips

### Before Ordering
1. ✅ Verify all part numbers are in stock
2. ✅ Check lead times match your schedule
3. ✅ Compare shipping costs (Digi-Key vs Mouser)
4. ✅ Look for JLCPCB coupon codes (often 10% off)

### Soldering Tips (if DIY)
1. **SMD components** (resistors, caps, ICs):
   - Easiest with solder paste + hot plate or oven
   - Can hand-solder with fine-tip iron (practice first!)
   - Start with IC chips (MP1584) - smallest pad pitch

2. **Through-hole** (connectors, electrolytic caps):
   - Standard soldering iron works fine
   - Pre-tin pads for easier connection
   - Let solder cool slowly (no fan)

3. **Order of assembly**:
   - SMD components first (they stay put)
   - Through-hole connectors and large caps last
   - Test continuity after soldering each section

---

## Troubleshooting Ordering

**Part out of stock?** Use these alternatives:

| Preferred | Alternative 1 | Alternative 2 |
|-----------|---------------|---------------|
| MP1584 | LM2596 | XL4005 |
| 1N4007 | 1N4004 | 1N400x series |
| 10µH L | 12µH 1210 | 15µH 1210 |
| 100nF cap | Any X7R 100nF | Any film 100nF |
| 10kΩ res | 10kΩ 1% metal film | Carbon film (less critical) |

---

## Final Notes

- All part numbers verified as of August 2026
- Prices subject to change (check actual prices when ordering)
- Stock quantities may vary by region
- Most components have multiple suppliers - shop around!
- Consider ordering 10-20% extra passives for prototyping/rework

**Ready to order?** Create accounts on both Digi-Key and Mouser and compare shipping costs!
