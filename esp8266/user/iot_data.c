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

LOCAL os_timer_t data_timer;

LOCAL uint16 vadc0, vadc1, vadc2, vadc3; // Po, Do, To, TDS

LOCAL void ICACHE_FLASH_ATTR data_timer_handler(void *prv){

    mux_channel(0); vadc0 = system_adc_read();
    mux_channel(1); vadc1 = system_adc_read();
    mux_channel(2); vadc2 = system_adc_read();
    mux_channel(3); vadc3 = system_adc_read();

#if LOOP_MSG
    os_printf("ADC: %4d |  %4d | %4d | %4d\r\n",vadc0,vadc1,vadc2,vadc3);
#endif
}

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
