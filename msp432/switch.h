

#ifndef __MICROPY_INCLUDED_MSP432P401R_SWITCH_H__
#define __MICROPY_INCLUDED_MSP432P401R_SWITCH_H__

void switch_init(void);
int switch_get(int sw);

extern const mp_obj_type_t pyb_switch_type;

#endif // __MICROPY_INCLUDED_MSP432P401R_SWITCH_H__
