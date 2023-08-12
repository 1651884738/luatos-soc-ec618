#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"
#include "cJSON.h"
#include "cmsis_os2.h"
#include "app_matt.h"


void test_json_2()
{
	cJSON *root;
	cJSON *fmt;
	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));

	cJSON_AddNullToObject(root, "null");
	cJSON_AddTrueToObject(root, "true");
	cJSON_AddFalseToObject(root, "false");
	cJSON_AddBoolToObject(root, "bool", 1);
	cJSON_AddNumberToObject(root, "number", 88);
	cJSON_AddStringToObject(root, "string", "Welcome to luatOS");
	cJSON_AddRawToObject(root, "Raw", "Welcome to luatOS raw");

	luat_debug_print("json data = %s\n", cJSON_Print(root));

	cJSON_Delete(root);
}



static void task_run(void *param)
{

	test_json_2();

	// mqtt
	osThreadId_t tMqttThread = NULL;
	osThreadAttr_t mqtt_attr;
    memset(&mqtt_attr, 0, sizeof(mqtt_attr));

    mqtt_attr.name = "mqtt";
    mqtt_attr.stack_size = 8 * 1024;
    mqtt_attr.priority = osPriorityBelowNormal;

    if(tMqttThread == NULL)
    {
        tMqttThread = osThreadNew(mqtt_thread, NULL,&mqtt_attr);
		luat_debug_print("mqtt thread init failed\r\n");
    }

	while(1)
	{
		luat_rtos_task_sleep(3000);
		luat_debug_print("hello world!!!");		
	}
}


void task_init(void)
{
	luat_debug_set_fault_mode(LUAT_DEBUG_FAULT_RESET);

	luat_rtos_task_handle task_handle;
	luat_rtos_task_create(&task_handle, 32 * 1204, 50, "test", task_run, NULL, 32);
}

INIT_TASK_EXPORT(task_init, "0");
