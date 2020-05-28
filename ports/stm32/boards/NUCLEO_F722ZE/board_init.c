#include "py/mphal.h"

<<<<<<< HEAD
void NUCLEO_F722ZE_board_early_init(void) {
=======
void board_early_init(void) {
>>>>>>> upstream/master
    // Turn off the USB switch
    #define USB_PowerSwitchOn pin_G6
    mp_hal_pin_output(USB_PowerSwitchOn);
    mp_hal_pin_low(USB_PowerSwitchOn);
}
