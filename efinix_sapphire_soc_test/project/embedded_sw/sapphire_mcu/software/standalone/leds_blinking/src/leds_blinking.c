// author      : siarhei baldzenka
// data        : 10.02.2025
// e-mail      : venera.electronica@gmail.com
// description : sapphire risc-v soc test led blinking

#include <stdint.h>
#include "bsp.h"
#include "gpio.h"

void main()
{
    bsp_init();
    gpio_setOutputEnable(SYSTEM_GPIO_0_IO_CTRL, 0xF);

    while(1)
    {
    	gpio_setOutput(SYSTEM_GPIO_0_IO_CTRL,0x1);
    	bsp_uDelay(200*1000);
    	gpio_setOutput(SYSTEM_GPIO_0_IO_CTRL,0x2);
        bsp_uDelay(200*1000);
    }
}
