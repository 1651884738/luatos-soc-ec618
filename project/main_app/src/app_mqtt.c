#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"
#include "cJSON.h"
#include "cmsis_os2.h"
#include "MQTTClient.h"



    // "mqtt": {
    //     "broker-port": 1883,
    //     "password": "vVWwQC5Fz5HD5INwxOfjij6jyds=",
    //     "keep-alive": 120,
    //     "user-name": "Signature|LTAI5tGmrCcrPP4qCNBV7ZEo|post-cn-tl32ay9ui1g",
    //     "cert-update": 0,
    //     "subscribe-topic": "szaf/GJ1009900001",
    //     "client-id": "GID_szaf_01@@@GJ1009900001",
    //     "publish-topic": "Serv-Listen-BJ01",
    //     "broker-ip": "post-cn-tl32ay9ui1g.mqtt.aliyuncs.com"
    // }

// TODO 
int hosttoip(char *hostname, char *ipaddr){


}

void messageParse(MessageData* data){
    luat_debug_print("recv data is %s\r\n",data);
}


static MQTTClient mqttClient;
int app_mqtt_connect(void)
{
    Network mqttNetwork = {0};
    MQTTMessage *message;

    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
    connectData.MQTTVersion = 4;
    connectData.clientID.cstring = "GID_szaf_01@@@GJ1009900001";
    connectData.username.cstring = "Signature|LTAI5tGmrCcrPP4qCNBV7ZEo|post-cn-tl32ay9ui1g";
    connectData.password.cstring = "vVWwQC5Fz5HD5INwxOfjij6jyds=";
    connectData.keepAliveInterval = 120;

    mqtt_connect(&mqttClient,&mqttNetwork,"47.112.223.225",1883,&connectData);
    return MQTTIsConnected(&mqttClient);
}

int mqtt_processing()
{
    int ret;
    ret = app_mqtt_connect();
    if (!ret){
        luat_debug_print("mqtt connect failed\r\n");
    }else
    {
        ret = MQTTSubscribe(&mqttClient, "szaf/GJ1009900001", 0, messageParse);
        luat_debug_print("mqtt subscribe ret is %d\r\n",ret);
        while (1)
        {
            ret = MQTTYield(&mqttClient, 1000);            
            luat_rtos_task_sleep(2000);
        }
        
    }
    return ret;
}

void mqtt_thread(){
    while (1)
    {
        mqtt_processing();
        luat_rtos_task_sleep(3000);
        luat_debug_print("this mqtt thread\r\n");
    }
    
}