#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// ============================================================================
// COMMUNICATION SETTINGS
// ============================================================================
#define SERIAL_BAUD_RATE        115200  // Console serial port baud rate
#define GPS_BAUD_RATE           9600    // GPS serial port baud rate

// ============================================================================
// HARDWARE CONFIGURATION
// ============================================================================

// ============================================================================
// TFT Display (ST7735) Pin Assignments - SPI Interface
// ============================================================================
// Display Module Wiring:
//   Display GND   → Pico GND
//   Display VCC   → Pico 3.3V
//   Display SCL   → Pico GPIO 18 (SPI Clock)
//   Display SDA   → Pico GPIO 19 (SPI Data/MOSI)
//   Display RES   → Pico GPIO 21 (Reset)
//   Display DC    → Pico GPIO 20 (Data/Command)
//   Display CS    → Pico GPIO 17 (Chip Select)
//   Display BLK   → Pico 3.3V (Backlight - always on)
// ============================================================================
#define TFT_MISO_PIN            16       // Hardware SPI MISO (not used - write-only)
#define TFT_CS_PIN              17       // TFT chip select
#define TFT_SCK_PIN             18       // Hardware SPI SCK (Display SCL)
#define TFT_MOSI_PIN            19       // Hardware SPI MOSI (Display SDA)
#define TFT_DC_PIN              20       // TFT data/command
#define TFT_RST_PIN             21       // TFT reset

// GPS Serial Pin Assignments
#define GPS_TX_PIN              0
#define GPS_RX_PIN              1

// Motor 0 - Hours Tens Place
#define HOURS_TENS_STEP_PIN     12
#define HOURS_TENS_DIR_PIN      14      // Shared with Motor 1
#define HOURS_TENS_HOME_PIN     13      // Hall sensor input (A1104)

// Motor 1 - Hours Ones Place
#define HOURS_ONES_STEP_PIN     10
#define HOURS_ONES_DIR_PIN      14      // Shared with Motor 0
#define HOURS_ONES_HOME_PIN     11      // Hall sensor input (A1104)

// Motor 2 - Minutes Tens Place
#define MINUTES_TENS_STEP_PIN   8
#define MINUTES_TENS_DIR_PIN    15      // Shared with Motor 3
#define MINUTES_TENS_HOME_PIN   9       // Hall sensor input (A1104)

// Motor 3 - Minutes Ones Place
#define MINUTES_ONES_STEP_PIN   6
#define MINUTES_ONES_DIR_PIN    15      // Shared with Motor 2
#define MINUTES_ONES_HOME_PIN   7       // Hall sensor input (A1104)

// Motor 4 - Seconds Tens Place
#define SECONDS_TENS_STEP_PIN   4
#define SECONDS_TENS_DIR_PIN    22      // Shared with Motor 5
#define SECONDS_TENS_HOME_PIN   5       // Hall sensor input (A1104)

// Motor 5 - Seconds Ones Place
#define SECONDS_ONES_STEP_PIN   2
#define SECONDS_ONES_DIR_PIN    22      // Shared with Motor 4
#define SECONDS_ONES_HOME_PIN   3       // Hall sensor input (A1104)

// ============================================================================
// HALL EFFECT SENSOR CONFIGURATION (A1104 Sensors)
// ============================================================================
// Each motor has an A1104 Hall effect sensor for home position detection
// Sensors output 0-5V analog signal based on magnetic field strength
// Can be used with Pico ADC or comparator for home detection
#define HALL_SENSOR_0           13      // Motor 0 (Hours Tens) - also GPIO13
#define HALL_SENSOR_1           11      // Motor 1 (Hours Ones) - also GPIO11
#define HALL_SENSOR_2           9       // Motor 2 (Minutes Tens) - also GPIO9
#define HALL_SENSOR_3           7       // Motor 3 (Minutes Ones) - also GPIO7
#define HALL_SENSOR_4           5       // Motor 4 (Seconds Tens) - also GPIO5
#define HALL_SENSOR_5           3       // Motor 5 (Seconds Ones) - also GPIO3

// Hall sensor detection threshold (for digital input)
// When magnet passes sensor, output goes low (~0.2V) / high (~2.5V)
#define HALL_DETECTION_THRESHOLD_LOW    0.5     // Volts (if using ADC)
#define HALL_DETECTION_THRESHOLD_HIGH   2.0     // Volts (if using ADC)

// Hall sensor: 5V supply and GND from motor power board
// Output signal filtered with 100nF capacitor

// Control Pins
#define ENABLE_PIN              22      // Active low - enables all stepper motors
#define LED_PIN                 LED_BUILTIN  // Use Pico built-in LED (GPIO25)
#define DEBUG_PIN               28      // Debug timing pin for performance measurement
#define TIMEZONE_BUTTON_PIN     26      // Timezone offset button (active low with pull-up)
#define H24_BUTTON_PIN          27      // 24H/12H format toggle button (active low with pull-up)

// Button Debounce Configuration
#define BUTTON_DEBOUNCE_MS      50     // Debounce time in milliseconds
#define BUTTON_LONG_PRESS_MS    2000   // Long press time in milliseconds

// Watchdog Timer Configuration
#define WATCHDOG_TIMEOUT_MS     4000    // Watchdog timer timeout in milliseconds

// ============================================================================
// POWER SUPPLY CONFIGURATION
// ============================================================================
#define MOTOR_SUPPLY_VOLTAGE    24      // Motor supply voltage (24V direct from barrel jack)
#define LOGIC_SUPPLY_VOLTAGE    5       // Logic supply voltage (from MP6524 buck converter)
#define BUCK_CONVERTER_INPUT    24      // MP6524: 24V input -> 5V output
#define BUCK_CONVERTER_OUTPUT   5

// ============================================================================
// MOTOR CONFIGURATION - NEMA 11, 24V, 200 steps/rev
// ============================================================================
#define MOTOR_TYPE              "NEMA11_24V"
#define MOTOR_STEPS_PER_REV     200     // NEMA 11 stepper: 200 steps per revolution
#define MOTOR_VOLTAGE           24      // Motor rated for 24V
#define MOTOR_CURRENT_MAX       0.67    // Motor max current: 0.67A per phase

// Microstepping configuration (TMC2208 driver)
#define MICROSTEPS              8       // 8 microsteps per full step
#define STEPS_PER_FULL_STEP     200     // Full steps per revolution
#define STEPS_PER_MICROSTEP     (MOTOR_STEPS_PER_REV * MICROSTEPS)  // 1600 microsteps per rev

// Display positions (0-9 for each digit)
#define NUM_POSITIONS           10      // Each digit shows 0-9
#define STEPS_PER_POSITION      (STEPS_PER_MICROSTEP / NUM_POSITIONS)  // 160 microsteps per position

// Motor control speeds
#define MOTOR_HOMING_SPEED      2500    // Steps per second during homing
#define MOTOR_MAX_SPEED         5000    // Steps per second
#define MOTOR_ACCELERATION      10000   // Steps per second²

// Per-motor homing offset (steps to advance after Hall sensor triggers)
// Calibrated for mechanical lever position on each digit wheel
#define HOMING_OFFSET_STEPS_HOURS_TENS      (175 + STEPS_PER_POSITION * 10)
#define HOMING_OFFSET_STEPS_HOURS_ONES      (167 + STEPS_PER_POSITION * 10)
#define HOMING_OFFSET_STEPS_MINUTES_TENS    (175 + STEPS_PER_POSITION * 10)
#define HOMING_OFFSET_STEPS_MINUTES_ONES    (170 + STEPS_PER_POSITION * 10)
#define HOMING_OFFSET_STEPS_SECONDS_TENS    (175 + STEPS_PER_POSITION * 10)
#define HOMING_OFFSET_STEPS_SECONDS_ONES    (169 + STEPS_PER_POSITION * 10)

// ============================================================================
// STEPPER DRIVER CONFIGURATION - TMC2208-24V
// ============================================================================
#define STEPPER_DRIVER_MODEL    "TMC2208"
#define STEPPER_DRIVER_VOLTAGE  24      // TMC2208-24V rated for 24V
#define STEPPER_RMS_CURRENT     0.67    // RMS current limit matches NEMA 11 rating
// TMC2208 pins: STEP, DIR, ENA (shared enable on GPIO22)
// Motors 0-1 share DIR on GPIO14
// Motors 2-3 share DIR on GPIO15
// Motors 4-5 share DIR on GPIO22 (also used as ENABLE)

#endif // CONFIGURATION_H