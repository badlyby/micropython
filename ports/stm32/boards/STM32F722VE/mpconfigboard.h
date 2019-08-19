// This board is only confirmed to operate using DFU mode and openocd.
// DFU mode can be accessed by setting BOOT0 (see schematics)
// To use openocd run "OPENOCD_CONFIG=boards/openocd_stm32f7.cfg" in
// the make command.

#define MICROPY_HW_BOARD_NAME       "STM32F722VE"
#define MICROPY_HW_MCU_NAME         "STM32F722"

#define MICROPY_HW_HAS_SWITCH       (1)
#define MICROPY_HW_HAS_FLASH        (1)
#define MICROPY_HW_ENABLE_RNG       (1)
#define MICROPY_HW_ENABLE_RTC       (1)
#define MICROPY_HW_ENABLE_DAC       (1)
#define MICROPY_HW_ENABLE_USB       (1)
#define MICROPY_HW_ENABLE_CAN       (1)
#define MODULE_CRC16_ENABLED        (1)
#define MODULE_CHECKSUM_ENABLED    (1)

#define MICROPY_BOARD_EARLY_INIT    STM32F722VE_board_early_init
void STM32F722VE_board_early_init(void);

// HSE is 16MHz
#define MICROPY_HW_CLK_PLLM (8)
#define MICROPY_HW_CLK_PLLN (216)
#define MICROPY_HW_CLK_PLLP (RCC_PLLP_DIV2)
#define MICROPY_HW_CLK_PLLQ (9)
#define MICROPY_HW_FLASH_LATENCY (FLASH_LATENCY_7) // 210-216 MHz needs 7 wait states

// UART config
#define MICROPY_HW_UART1_TX         (pin_A9)
#define MICROPY_HW_UART1_RX         (pin_A10)
#define MICROPY_HW_UART2_TX         (pin_D5)
#define MICROPY_HW_UART2_RX         (pin_D6)
#define MICROPY_HW_UART3_TX         (pin_D8)
#define MICROPY_HW_UART3_RX         (pin_D9)
#define MICROPY_HW_UART7_TX         (pin_E8)
#define MICROPY_HW_UART7_RX         (pin_E9)
#define MICROPY_HW_UART_REPL        PYB_UART_7
#define MICROPY_HW_UART_REPL_BAUD   115200

// I2C busses
#define MICROPY_HW_I2C1_SCL         (pin_B8)
#define MICROPY_HW_I2C1_SDA         (pin_B9)
#define MICROPY_HW_I2C2_SCL         (pin_B10)
#define MICROPY_HW_I2C2_SDA         (pin_B11)

// SPI
#define MICROPY_HW_SPI4_NSS         (pin_E11)
#define MICROPY_HW_SPI4_SCK         (pin_E12)
#define MICROPY_HW_SPI4_MISO        (pin_E13)
#define MICROPY_HW_SPI4_MOSI        (pin_E14)

// CAN busses
#define MICROPY_HW_CAN1_TX          (pin_B9)
#define MICROPY_HW_CAN1_RX          (pin_B8)

// USRSW is pulled high. Pressing the button makes the input go low.
#define MICROPY_HW_USRSW_PIN        (pin_B0)
#define MICROPY_HW_USRSW_PULL       (GPIO_PULLUP)
#define MICROPY_HW_USRSW_EXTI_MODE  (GPIO_MODE_IT_FALLING)
#define MICROPY_HW_USRSW_PRESSED    (0)

// SD card detect switch
#define MICROPY_HW_SDCARD_DETECT_PIN        (pin_B1)
#define MICROPY_HW_SDCARD_DETECT_PULL       (GPIO_PULLUP)
#define MICROPY_HW_SDCARD_DETECT_PRESENT    (GPIO_PIN_RESET)

// LEDs
#define MICROPY_HW_LED1             (pin_D0) // green
#define MICROPY_HW_LED2             (pin_D1) // blue
#define MICROPY_HW_LED3             (pin_D2) // red
#define MICROPY_HW_LED_ON(pin)      (mp_hal_pin_high(pin))
#define MICROPY_HW_LED_OFF(pin)     (mp_hal_pin_low(pin))

// USB config (CN13 - USB OTG FS)
#define MICROPY_HW_USB_FS              (1)
//#define MICROPY_HW_USB_VBUS_DETECT_PIN (pin_A9)
//#define MICROPY_HW_USB_OTG_ID_PIN      (pin_A10)

