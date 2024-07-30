#ifndef __SLEEP_MODE_H
#define __SLEEP_MODE_H

void set_sysclk_low_power(void);

void enable_pwc_clk(void);

void standby_mode_peripheral_deinit(void);

void low_power_consumption(void);

#endif /* __SLEEP_MODE_H  */