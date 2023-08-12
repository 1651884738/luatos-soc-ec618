#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"
#include "cJSON.h"
#include "cmsis_os2.h"



void mqtt_thread(){
    while (1)
    {
        luat_rtos_task_sleep(1500);
        luat_debug_print("this mqtt thread\r\n");
    }
    
}