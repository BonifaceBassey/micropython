#include <stdio.h>

//#include "py/nlr.h"
#include "py/runtime.h"
#include "py/mphal.h"
#include "led.h"
#include "drivers/driverlib/MSP432P4xx/gpio.h"

#define LED_ON (1)
#define LED_OFF (0)


typedef struct _pyb_led_obj_t {
    mp_obj_base_t base;
} pyb_led_obj_t;

STATIC const pyb_led_obj_t pyb_led_obj[] = {
    {{&pyb_led_type}},
    {{&pyb_led_type}},
    {{&pyb_led_type}},
    {{&pyb_led_type}},
};

#define NUM_LEDS MP_ARRAY_SIZE(pyb_led_obj)
#define LED_ID(obj) ((obj) - &pyb_led_obj[0] + 1)

// led init
void led_init(void) {
    // set led GPIO as outputs
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

    // turn off the LEDs
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1); 
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2); 
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

// led state
void led_state(pyb_led_t led, int state) {
    if (led < 1 || led > NUM_LEDS) {
        return;
    }
    int val = state ? LED_ON : LED_OFF;
    switch (led) {
        case 1: 
	    if(val==1) GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
	    else GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0); 
            break;
        case 2: 
	    if(val==1) GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
	    else GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1); 
            break;
        case 3: 
	    if(val==1) GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
	    else GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2); 
            break;
	case 4: 
	    if(val==1) GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
	    else GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0); 
            break;	
    }
}

// led toggle 
void led_toggle(pyb_led_t led) {
    if (led < 1 || led > NUM_LEDS) {
        return;
    }
    switch(led)
    {
	case 1:	GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0); break;
	case 2: GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN1); break;
	case 3: GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN2); break;
	case 4: GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0); break;
   
    }
}

/******************************************************************************/
/* Micro Python bindings                                                      */

void pyb_led_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    pyb_led_obj_t *self = self_in;
    mp_printf(print, "LED(%u)", LED_ID(self));
}


/// \classmethod \constructor(id)
/// Create an LED object associated with the given LED:
///
///   - `id` is the LED number, 1-4.
STATIC mp_obj_t pyb_led_make_new(const mp_obj_type_t *type, mp_uint_t n_args, mp_uint_t n_kw, const mp_obj_t *args) {
    // check arguments
    mp_arg_check_num(n_args, n_kw, 1, 1, false);

    // get led number
    mp_int_t led_id = mp_obj_get_int(args[0]);

    // check led number
    if (!(1 <= led_id && led_id <= NUM_LEDS)) {
        nlr_raise(mp_obj_new_exception_msg_varg(&mp_type_ValueError, "LED(%d) does not exist", led_id));
    }

    // return static led object
    return (mp_obj_t)&pyb_led_obj[led_id - 1];
}


/// \method on()
/// Turn the LED on.
mp_obj_t led_obj_on(mp_obj_t self_in) {
    pyb_led_obj_t *self = self_in;
    led_state(LED_ID(self), 1);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(pyb_led_on_obj, led_obj_on);

/// \method off()
/// Turn the LED off.
mp_obj_t led_obj_off(mp_obj_t self_in) {
    pyb_led_obj_t *self = self_in;
    led_state(LED_ID(self), 0);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(pyb_led_off_obj, led_obj_off);

/// \method toggle()
/// Toggle the LED between on and off.
mp_obj_t led_obj_toggle(mp_obj_t self_in) {
    pyb_led_obj_t *self = self_in;
    led_toggle(LED_ID(self));
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(pyb_led_toggle_obj, led_obj_toggle);

STATIC const mp_map_elem_t pyb_led_locals_dict_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_on), (mp_obj_t)&pyb_led_on_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_off), (mp_obj_t)&pyb_led_off_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_toggle), (mp_obj_t)&pyb_led_toggle_obj },
};

STATIC MP_DEFINE_CONST_DICT(pyb_led_locals_dict, pyb_led_locals_dict_table);

const mp_obj_type_t pyb_led_type = {
    { &mp_type_type },
    .name = MP_QSTR_LED,
    .print = pyb_led_print,
    .make_new = pyb_led_make_new,
    .locals_dict = (mp_obj_t)&pyb_led_locals_dict,
};
