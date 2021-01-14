/*
              UNKNOWN PUBLIC LICENSE

 Copyright (C) 2020 Achmadi S.T. M.T.

 Currently no license applied because author liv in
 Indonesia, a country which doesn't really concern
 about digital content copyright.

 */

/**
 * @file    iot_data.c
 * @brief   Main data processing code.
 *
 * @addtogroup IoT
 * @{
 */

#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

#include "mem.h"
#include "ip_addr.h"
#include "espconn.h"
#include "user_interface.h"

#include "driver/uart.h"
#include "driver/gpio16.h"

#include "wifi_sta.h"
#include "user_config.h"
#include "http_client.h"
#include "mqtt_client.h"
#include "mux.h"
#include "iot_data.h"
#include "blinky.h"

/**
 * @brief Timer for Data loop
 */
LOCAL os_timer_t data_timer;

/**
 * @brief ADC for PH output
 */
LOCAL uint16 vadc0;

/**
 * @brief ADC for limiter output
 */
LOCAL uint16 vadc1;

/**
 * @brief ADC for Temp output
 */
LOCAL uint16 vadc2;

/**
 * @brief ADC for TDS output
 */
LOCAL uint16 vadc3;

/**
 * @brief Loop timer handler function
 */
LOCAL void ICACHE_FLASH_ATTR data_timer_handler(void *prv){

    mux_channel(0); vadc0 = system_adc_read();
    mux_channel(1); vadc1 = system_adc_read();
    mux_channel(2); vadc2 = system_adc_read();
    mux_channel(3); vadc3 = system_adc_read();

#if LOOP_MSG
    os_printf("ADC: %4d |  %4d | %4d | %4d\r\n",vadc0,vadc1,vadc2,vadc3);
#endif
}

/**
 * @brief Loop starter function
 * @param uint8 Interval option
 * @details Options: 0 (stop), 1 (500ms), 2 (5s)
 */
void run_loop(uint8 interval){

    switch(interval){
        case 0:
            os_timer_disarm(&data_timer);
            os_printf("data loop stopped\r\n");
            blinky_loop_stop();
        break;

        case 1:
            os_timer_disarm(&data_timer);
            os_timer_setfn(&data_timer, (os_timer_func_t *)data_timer_handler, NULL);
            os_timer_arm(&data_timer, 500, 1);
            os_printf("data loop every 500ms\r\n");
            blinky_loop_run();
        break;

        case 2:
            os_timer_disarm(&data_timer);
            os_timer_setfn(&data_timer, (os_timer_func_t *)data_timer_handler, NULL);
            os_timer_arm(&data_timer, 5000, 1);
            os_printf("data loop every 5s\r\n");
            blinky_loop_run();
        break;

        default:
            os_timer_disarm(&data_timer);
            os_printf("data loop option unrecognized\r\n");
            blinky_loop_stop();
        break;
    }
}
/** @} */
