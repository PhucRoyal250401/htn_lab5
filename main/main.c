#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "sdkconfig.h"
#include "freertos/timers.h"
#include <time.h>
#include <stdio.h>

void vTimerCallback(TimerHandle_t xTimer)
{
    const uint32_t ulNumberTimer1 = 10;
    const uint32_t ulNumberTimer2 = 5;
    uint32_t ulCount;

    ulCount = (uint32_t)pvTimerGetTimerID(xTimer);
    // printf("%d\n", ulCount);
    ulCount++;

    if (ulCount / 1000 == 1) // do timer1
    {
        printf("ahihi: %d\n", (int)clock() / 1000);
        if (ulCount % 1000 >= ulNumberTimer1)
        {
            xTimerStop(xTimer, 0);
        }
    }
    else if (ulCount / 1000 == 2) // do timer2
    {
        printf("ihaha: %d\n", (int)clock() / 1000);
        if (ulCount % 1000 >= ulNumberTimer2)
        {
            xTimerStop(xTimer, 0);
        }
    }
    vTimerSetTimerID(xTimer, (void *)ulCount);
}

void app_main(void)
{
    TimerHandle_t timer1;
    TimerHandle_t timer2;

    timer1 = xTimerCreate("Timer1", 200, pdTRUE, (void *)1000, vTimerCallback);
    // callback every 200*10ms = 2s, set pvTimerID = 1000
    timer2 = xTimerCreate("Timer2", 300, pdTRUE, (void *)2000, vTimerCallback);
    // callback every 300*10ms = 3s, set pvTimerID = 2000

    if (xTimerStart(timer1, 0) != pdPASS || xTimerStart(timer2, 0) != pdPASS)
    {
        printf("Timer start false");
    }
}