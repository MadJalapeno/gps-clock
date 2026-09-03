# Digi-Key Passive Component Sourcing Guide

## Quick Summary
**Total passive components needed**: 28 items
**Estimated cost**: $3-5 USD
**Search site**: https://www.digikey.com

---

## Component Details & Search Instructions

### Resistors (10kΩ, 1/4W, 5%)

**Quantity needed**: 8
**Specifications**:
- Resistance: 10,000 Ω (10kΩ)
- Power rating: 0.25W (1/4W)
- Tolerance: 5%
- Type: Carbon film or metal film (metal film preferred for stability)
- Package: Through-hole, standard 0.25" leads

**Digi-Key Search**:
1. Go to https://www.digikey.com
2. Click "Resistors" category
3. Filter by:
   - Resistance: 10 kΩ
   - Power: 0.25 W
   - Type: Through Hole
4. Sort by price (low to high)

**Common part numbers**:
- CFM14JT10K0 (Stackpole, very common, ~$0.08)
- MFR-25FBF52-10K (Yageo, ~$0.10)
- RSF25JT10K (Bourns, ~$0.12)

**Buy**: Order 10-12 for spare parts

---

### Capacitors - 100nF (0.1µF, 50V)

**Quantity needed**: 10
**Specifications**:
- Capacitance: 100nF (0.1µF)
- Voltage: 50V DC minimum (can be higher)
- Type: Ceramic, X7R dielectric (stable across temperature)
- Package: Through-hole, 5mm pitch
- ESR: Low ESR preferred

**Digi-Key Search**:
1. Click "Capacitors" category
2. Filter by:
   - Capacitance: 0.1 µF
   - Voltage: 50 V
   - Type: Ceramic
   - Dielectric: X7R
   - Pitch: 5 mm (or 0.2")
3. Sort by price

**Common part numbers**:
- K104K50X7RF53H5 (Vishay, ~$0.10)
- ECE-A1VKS101 (Panasonic, ~$0.12)
- KEMET C315C104M5U5TA (KEMET, ~$0.15)

**Buy**: Order 12-15 for spares (always good to have extras)

---

### Capacitors - 100µF, 16V (Electrolytic)

**Quantity needed**: 2
**Specifications**:
- Capacitance: 100µF
- Voltage: 16V DC minimum (or higher)
- Type: Aluminum electrolytic, radial leads
- Package: 5.08mm pitch (standard)
- Ripple current: ≥1A at 120Hz

**Digi-Key Search**:
1. Click "Capacitors" category
2. Filter by:
   - Capacitance: 100 µF
   - Voltage: 16 V or 25 V
   - Type: Aluminum Electrolytic
   - Lead spacing: 5.08 mm
3. Sort by price

**Common part numbers**:
- UPL1C101MDD (Nichicon, ~$0.15)
- EEU-FC1C101 (Panasonic, ~$0.18)
- 100UX16MEFC8X11.5 (Cornell Dubilier, ~$0.20)

**Buy**: Order 4 (2 needed, but extras for testing)

---

### Capacitors - 220µF, 50V (Electrolytic)

**Quantity needed**: 1
**Specifications**:
- Capacitance: 220µF
- Voltage: 50V DC minimum (high voltage for 24V input buck converter)
- Type: Aluminum electrolytic, radial leads
- Package: 10mm pitch or larger
- Ripple current: ≥2A @ 120Hz

**Digi-Key Search**:
1. Click "Capacitors" category
2. Filter by:
   - Capacitance: 220 µF
   - Voltage: 50 V or 63 V
   - Type: Aluminum Electrolytic
3. Sort by price

**Common part numbers**:
- EEU-FC1H221 (Panasonic, ~$0.40)
- UPL1H221MDD (Nichicon, ~$0.35)
- 220UX50MEFC10X20 (Cornell Dubilier, ~$0.45)

**Buy**: Order 2 (1 needed, spare for backup)

---

### Capacitors - 10µF, 10V (Tantalum)

**Quantity needed**: 1
**Specifications**:
- Capacitance: 10µF
- Voltage: 10V DC minimum
- Type: Tantalum or polymer (tantalum preferred for GPS supply filtering)
- Package: Case A or B (small through-hole)
- ESR: Low ESR

**Digi-Key Search**:
1. Click "Capacitors" category
2. Filter by:
   - Capacitance: 10 µF
   - Voltage: 10 V or 16 V
   - Type: Tantalum
3. Sort by price

**Common part numbers**:
- TAJB106K010RNJ (AVX, ~$0.40)
- T491D106K010AH (Kemet, ~$0.35)
- 293D106X9010D2T (Vishay, ~$0.45)

**Buy**: Order 2 (1 needed, spare recommended)

---

## Complete Shopping List

| Component | Quantity | Est. Unit Price | Est. Total | Digi-Key Filter |
|-----------|----------|-----------------|-----------|-----------------|
| 10kΩ 1/4W Resistor | 10 | $0.08 | $0.80 | Resistors, 10k, 0.25W |
| 100nF 50V Ceramic | 12 | $0.10 | $1.20 | Capacitors, 100n, 50V, X7R |
| 100µF 16V Electrolytic | 4 | $0.18 | $0.72 | Capacitors, 100u, 16V, Radial |
| 220µF 50V Electrolytic | 2 | $0.40 | $0.80 | Capacitors, 220u, 50V, Radial |
| 10µF 10V Tantalum | 2 | $0.40 | $0.80 | Capacitors, 10u, 10V, Tantalum |
| | | **SUBTOTAL** | **$4.32** | |
| | | **Shipping (est.)** | **$5-10** | Depends on shipping speed |
| | | **TOTAL** | **$10-15** | |

---

## Ordering Tips

1. **Minimum Order**: Digi-Key typically has no minimum
2. **Bulk Discount**: Prices shown are often for single units; small bulk discounts may apply
3. **Shipping**:
   - Standard (5-7 days): ~$5-8
   - Ground (3-5 days): ~$8-12
   - Overnight: ~$20+
4. **Lead Time**: These are common components—stock is usually available same-day
5. **Add to Cart**: You can add multiple items to cart and checkout in one order

---

## Digi-Key Quick Links

- **Main site**: https://www.digikey.com
- **Resistors category**: https://www.digikey.com/en/products/filter/resistors-through-hole/797
- **Capacitors category**: https://www.digikey.com/en/products/filter/capacitors/645

---

## Alternative Suppliers

If Digi-Key is out of stock or shipping is too slow:
- **Mouser Electronics**: https://www.mouser.com (similar selection, sometimes different shipping rates)
- **Newark/element14**: https://www.newark.com (good for bulk orders)
- **Amazon Electronics**: Often have these components with Prime shipping
- **Local electronics shops**: RadioShack (where available) or local hobby shops

---

## Storage Notes

Once received, store in:
- **Resistors**: Plastic bag, dry cabinet (humidity-sensitive component tape)
- **Capacitors**: Plastic bag, cool dry location
- **Electrolytic caps**: Avoid moisture and temperature extremes
- **Tantalum caps**: Handle carefully—static sensitive, do not short leads

