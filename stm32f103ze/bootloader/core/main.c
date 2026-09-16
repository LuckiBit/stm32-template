#include "application_boot.h"
#include "led.h"
#include "system_init.h"

int main(void)
{
    bool application_valid;

    system_init();
    led_run();
    application_valid = application_is_valid();
    if(application_valid)
    {
        led_stop();
        application_start();
    }

    while(1)
    {
        led_run();
    }
}
