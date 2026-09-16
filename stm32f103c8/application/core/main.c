#include "rtos_start.h"
#include "system_init.h"

int main(void)
{
    system_init();
    rtos_start();

    while(1)
    {
    }
}
