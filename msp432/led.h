

#ifndef __MICROPY_INCLUDED_MSP432P401R_LED_H__
#define __MICROPY_INCLUDED_MSP432P401R_LED_H__

typedef enum {
    // MSP432 LAUNCHPAD onboard LEDS
    LED_RED   = 1,
    LED_GREEN = 2,
    LED_BLUE  = 3,
    LED_0     = 4,
} pyb_led_t;


void led_init(void);
void led_state(pyb_led_t led, int state);
void led_toggle(pyb_led_t led);

extern const mp_obj_type_t pyb_led_type;

#endif // __MICROPY_INCLUDED_MSP432P401R_LED_H__
