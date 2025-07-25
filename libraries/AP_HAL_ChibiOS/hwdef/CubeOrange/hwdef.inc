
define HAL_CHIBIOS_ARCH_CUBE 1

# USB setup
USB_VENDOR 0x2DAE # ONLY FOR USE BY HEX! NOBODY ELSE
USB_PRODUCT 0x1016
USB_STRING_MANUFACTURER "Hex/ProfiCNC"

# crystal frequency
OSCILLATOR_HZ 24000000

# board ID. See Tools/AP_Bootloader/board_types.txt
APJ_BOARD_ID AP_HW_CUBEORANGE

FLASH_SIZE_KB 2048

# supports upto 8MBits/s
CANFD_SUPPORTED 8


FLASH_RESERVE_START_KB 128

define HAL_STORAGE_SIZE 32768

# order of I2C buses
I2C_ORDER I2C2 I2C1

# order of UARTs (and USB)
SERIAL_ORDER OTG1 USART2 USART3 UART4 UART8 UART7 OTG2

# default the 2nd interface to SLCAN
define HAL_OTG2_PROTOCOL SerialProtocol_SLCAN

# If the board has an IOMCU connected via a UART then this defines the
# UART to talk to that MCU. Leave it out for boards with no IOMCU.

# UART for IOMCU
IOMCU_UART USART6

# UART4 serial GPS
PA0 UART4_TX UART4
PA1 UART4_RX UART4 NODMA

PA2 BATT_VOLTAGE_SENS ADC1 SCALE(1)
PA3 BATT_CURRENT_SENS ADC1 SCALE(1)

# Now the VDD sense pin. This is used to sense primary board voltage.
PA4 VDD_5V_SENS ADC1 SCALE(2)

PA5 SPI1_SCK SPI1
PA6 SPI1_MISO SPI1
PA7 SPI1_MOSI SPI1

# This defines an output pin which will default to output HIGH. It is
# a pin that enables peripheral power on this board. It starts in the
# off state, then is pulled low to enable peripherals in
# peripheral_power_enable()
PA8 nVDD_5V_PERIPH_EN OUTPUT LOW

# This is the pin that senses USB being connected. It is an input pin
# setup as OPENDRAIN.
PA9 VBUS INPUT OPENDRAIN

# Now we define the pins that USB is connected on.
PA11 OTG_FS_DM OTG1
PA12 OTG_FS_DP OTG1

# These are the pins for SWD debugging with a STlinkv2 or black-magic probe.
PA13 JTMS-SWDIO SWD
PA14 JTCK-SWCLK SWD

# PWM output for buzzer
PA15 TIM2_CH1 TIM2 GPIO(77) ALARM

# Map the EXTERN_DRDY and !EXTERN_CS as analog inputs in
PB0 PB0_ADC ADC1 SCALE(1)
PB1 PB1_ADC ADC1 SCALE(1)
# also keep them available as a GPIO alt config
PB0 EXTERN_GPIO1 OUTPUT GPIO(1) ALT(2)
PB1 EXTERN_GPIO2 OUTPUT GPIO(2) ALT(2)

# This defines some input pins, currently unused.
PB2 BOOT1 INPUT
PB3 FMU_SW0 INPUT

# This defines the pins for the 2nd CAN interface, if available.
PB6 CAN2_TX CAN2
PB12 CAN2_RX CAN2

# Now the first I2C bus. The pin speeds are automatically setup
# correctly, but can be overridden here if needed.
PB8 I2C1_SCL I2C1
PB9 I2C1_SDA I2C1

# the 2nd I2C bus
PB10 I2C2_SCL I2C2
PB11 I2C2_SDA I2C2

# the 2nd SPI bus
PB13 SPI2_SCK SPI2
PB14 SPI2_MISO SPI2
PB15 SPI2_MOSI SPI2

# This input pin is used to detect that power is valid on USB.
PC0 VBUS_nVALID INPUT PULLUP

# This defines the CS pin for the magnetometer and first IMU. Note
# that CS pins are software controlled, and are not tied to a particular
# SPI bus.
PC1 MAG_CS CS
PC2 MPU_CS CS

# This defines more ADC inputs.
PC3 AUX_POWER ADC1 SCALE(1)
PC4 AUX_ADC2 ADC1 SCALE(1)

# And the analog input for airspeed (rarely used these days).
PC5 PRESSURE_SENS ADC1 SCALE(2)

#  USART6 to IO
PC6 USART6_TX USART6
PC7 USART6_RX USART6

# Now setup the pins for the microSD card
include sdcard.inc

# More CS pins for more sensors. The labels for all CS pins need to
# match the SPI device table later in this file.
PC13 GYRO_EXT_CS CS
PC14 BARO_EXT_CS CS
PC15 ACCEL_EXT_CS CS
PD7 BARO_CS CS
PE4 MPU_EXT_CS CS

# the first CAN bus
PD0 CAN1_RX CAN1
PD1 CAN1_TX CAN1

# Another USART, this one for telem1. This one has RTS and CTS lines.
# USART2 serial2 telem1
PD3 USART2_CTS USART2
PD4 USART2_RTS USART2
PD5 USART2_TX USART2
PD6 USART2_RX USART2

# telem1 RTS and CTS as GPIO in alt config 1
PD3 EXTERN_GPIO4 OUTPUT GPIO(4) ALT(1)
PD4 EXTERN_GPIO5 OUTPUT GPIO(5) ALT(1)

# The telem2 USART, also with RTS/CTS available.
# USART3 serial3 telem2
PD8 USART3_TX USART3
PD9 USART3_RX USART3
PD11 USART3_CTS USART3
PD12 USART3_RTS USART3

# The CS pin for FRAM (ramtron). This one is marked as using
# SPEED_VERYLOW, which matches the HAL_PX4 setup.
PD10 FRAM_CS CS SPEED_VERYLOW

# Now we start defining some PWM pins. We also map these pins to GPIO
# values, so users can set SERVOx_FUNCTION=-1 to determine which
# PWM outputs on the primary MCU are set up as GPIOs.
# To match HAL_PX4 we number the GPIOs for the PWM outputs
# starting at 50.
PE14 TIM1_CH4 TIM1 PWM(1) GPIO(50)
PE13 TIM1_CH3 TIM1 PWM(2) GPIO(51)
PE11 TIM1_CH2 TIM1 PWM(3) GPIO(52)
PE9  TIM1_CH1 TIM1 PWM(4) GPIO(53)
PD13 TIM4_CH2 TIM4 PWM(5) GPIO(54)
PD14 TIM4_CH3 TIM4 PWM(6) GPIO(55)

# Pin for PWM Voltage Selection
PB4 PWM_VOLT_SEL OUTPUT HIGH GPIO(3)

# This is the invensense data-ready pin. We don't use it in the
# default driver.
PD15 MPU_DRDY INPUT

# the 2nd GPS UART
# UART8 serial4 GPS2
PE0 UART8_RX UART8
PE1 UART8_TX UART8 NODMA

# Now setup SPI bus4.
PE2 SPI4_SCK  SPI4
PE5 SPI4_MISO SPI4
PE6 SPI4_MOSI SPI4

# This is the pin to enable the sensors rail. It can be used to power
# cycle sensors to recover them in case there are problems with power on
# timing affecting sensor stability. We pull it LOW on startup, which
# means sensors off, then it is pulled HIGH in peripheral_power_enable()
PE3 VDD_3V3_SENSORS_EN OUTPUT LOW

# UART7 maps to SERIAL5.
PE7 UART7_RX UART7
PE8 UART7_TX UART7

# Define a LED, mapping it to GPIO(0). LOW will illuminate the LED
PE12 FMU_LED_AMBER OUTPUT HIGH OPENDRAIN GPIO(0)

# Power flag pins: these tell the MCU the status of the various power
# supplies that are available. The pin names need to exactly match the
# names used in AnalogIn.cpp. 
PB5 VDD_BRICK_nVALID INPUT PULLUP
PB7 VDD_BRICK2_nVALID INPUT PULLUP
PE10 VDD_5V_HIPOWER_nOC INPUT PULLUP
PE15 VDD_5V_PERIPH_nOC INPUT PULLUP

SPIDEV ms5611         SPI1 DEVID3  BARO_CS      MODE3 20*MHZ 20*MHZ
SPIDEV ms5611_ext     SPI4 DEVID2  BARO_EXT_CS  MODE3 20*MHZ 20*MHZ
SPIDEV icm20948       SPI1 DEVID4  MPU_CS       MODE3  4*MHZ  8*MHZ
SPIDEV icm20948_ext   SPI4 DEVID1  MPU_EXT_CS   MODE3  4*MHZ  8*MHZ
SPIDEV icm20602_ext   SPI4 DEVID4  GYRO_EXT_CS  MODE3  4*MHZ  8*MHZ
SPIDEV ramtron        SPI2 DEVID10 FRAM_CS      MODE3  8*MHZ  8*MHZ
SPIDEV external0m0    SPI4 DEVID5  MPU_EXT_CS   MODE0  2*MHZ  2*MHZ
SPIDEV external0m1    SPI4 DEVID5  MPU_EXT_CS   MODE1  2*MHZ  2*MHZ
SPIDEV external0m2    SPI4 DEVID5  MPU_EXT_CS   MODE2  2*MHZ  2*MHZ
SPIDEV external0m3    SPI4 DEVID5  MPU_EXT_CS   MODE3  2*MHZ  2*MHZ
SPIDEV pixartPC15     SPI4 DEVID13 ACCEL_EXT_CS MODE3  2*MHZ  2*MHZ

# IMU set for newer cubes
IMU Invensense SPI:icm20602_ext ROTATION_ROLL_180_YAW_270
IMU Invensensev2 SPI:icm20948_ext ROTATION_PITCH_180
IMU Invensensev2 SPI:icm20948 ROTATION_YAW_270

# Sensor Check alias for validating board type
CHECK_ICM20649          spi_check_register_inv2("icm20948", INV2REG_WHOAMI, INV2_WHOAMI_ICM20649)
CHECK_ICM20602_EXT      spi_check_register("icm20602_ext", MPUREG_WHOAMI, MPU_WHOAMI_ICM20602)
CHECK_ICM20948_EXT      spi_check_register_inv2("icm20948_ext", INV2REG_WHOAMI, INV2_WHOAMI_ICM20948)
CHECK_MS5611            check_ms5611("ms5611")
CHECK_MS5611_EXT        check_ms5611("ms5611_ext")

# Sensor Check Macros to be used for validating board type
CHECK_IMU0_PRESENT   $CHECK_ICM20602_EXT
CHECK_IMU1_PRESENT   $CHECK_ICM20948_EXT
CHECK_IMU2_PRESENT   $CHECK_ICM20649
CHECK_BARO0_PRESENT  $CHECK_MS5611
CHECK_BARO1_PRESENT  $CHECK_MS5611_EXT

BOARD_VALIDATE $CHECK_IMU0_PRESENT $CHECK_IMU1_PRESENT $CHECK_IMU2_PRESENT $CHECK_BARO0_PRESENT $CHECK_BARO1_PRESENT


define HAL_DEFAULT_INS_FAST_SAMPLE 7

# two baros
BARO MS5611 SPI:ms5611_ext
BARO MS5611 SPI:ms5611

# one internal compass
COMPASS AK09916:probe_ICM20948 0 ROTATION_ROLL_180_YAW_90

# offset the internal compass for EM impact of the IMU heater
# this is in body frame mGauss
define HAL_HEATER_MAG_OFFSET {AP_HAL::Device::make_bus_id(AP_HAL::Device::BUS_TYPE_SPI,4,1,9),Vector3f(10,30,-235)}

# also probe for external compasses
define HAL_PROBE_EXTERNAL_I2C_COMPASSES

define HAL_CHIBIOS_ARCH_FMUV3 1

define BOARD_TYPE_DEFAULT 3

# allow to have have a dedicated safety switch pin
define HAL_HAVE_SAFETY_SWITCH 1

# Enable RAMTROM parameter storage.
define HAL_WITH_RAMTRON 1

# Setup the IMU heater
define HAL_HAVE_IMU_HEATER 1
define HAL_IMU_TEMP_DEFAULT 45
define HAL_IMUHEAT_P_DEFAULT 50
define HAL_IMUHEAT_I_DEFAULT 0.07
define HAL_IMU_TEMP_MARGIN_LOW_DEFAULT 5

# Enable all IMUs to be used and therefore three active EKF Lanes
define HAL_EKF_IMU_MASK_DEFAULT 7

# Enable FAT filesystem support (needs a microSD defined via SDMMC).
define HAL_OS_FATFS_IO 1

# Now setup the default battery pins driver analog pins and default
# scaling for the power brick.
define HAL_BATT_VOLT_PIN 14
define HAL_BATT_CURR_PIN 15
define HAL_BATT_VOLT_SCALE 10.1
define HAL_BATT_CURR_SCALE 17.0
define HAL_GPIO_PWM_VOLT_PIN 3
define HAL_GPIO_PWM_VOLT_3v3 1

# List of files to put in ROMFS. For fmuv3 we need an IO firmware so
# we can automatically update the IOMCU firmware on boot. The format
# is "ROMFS ROMFS-filename source-filename". Paths are relative to the
# ardupilot root.
ROMFS io_firmware.bin Tools/IO_Firmware/iofirmware_cube_highpolh.bin

# enable support for dshot on iomcu
ROMFS io_firmware_dshot.bin Tools/IO_Firmware/iofirmware_cube_dshot_highpolh.bin
define HAL_WITH_IO_MCU_DSHOT 1

define AP_IOMCU_PROFILED_SUPPORT_ENABLED 1

DMA_NOSHARE SPI1* SPI4* USART6*

# for users who have replaced their CubeSolo with a CubeOrange:
define AP_NOTIFY_OREOLED_ENABLED 1
define HAL_SOLO_GIMBAL_ENABLED HAL_MOUNT_ENABLED

undef AP_BATTERY_SMBUS_SOLO_ENABLED
define AP_BATTERY_SMBUS_SOLO_ENABLED AP_BATTERY_SMBUS_ENABLED

# Enable Sagetech MXS ADSB transponder
define HAL_ADSB_SAGETECH_MXS_ENABLED HAL_ADSB_ENABLED

# enable DFU reboot for installing bootloader
# note that if firmware is build with --secure-bl then DFU is
# disabled
ENABLE_DFU_BOOT 1
