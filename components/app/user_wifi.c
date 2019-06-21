#include "../include/user_common.h"


const CHAR szWifiModeString[][15] = {
	"none",
	"station",
	"AP",
	"station_AP",

	"buff"
};

const CHAR szWifiAuthModeString[][15] = {
	"open",
	"WEP",
	"WPA_PSK",
	"WPA2_PSK",
	"WPA_WPA2_PSK",
	"unknow"
};

const CHAR szWifiStatusString[][20] = {
	"idle",
	"connecting",
	"password is wrong",
	"can not find AP",
	"fail to connect AP",
	"got IP from AP",

	"unknow"
};

static EventGroupHandle_t wifi_event_group;
static const int CONNECTED_BIT = BIT0;
static const int ESPTOUCH_DONE_BIT = BIT1;

static void sc_callback(smartconfig_status_t status, void *pdata)
{
    switch (status) {
        case SC_STATUS_WAIT:
        	LOG_OUT(INFO, "SC_STATUS_WAIT");
            break;
        case SC_STATUS_FIND_CHANNEL:
        	LOG_OUT(INFO, "SC_STATUS_FIND_CHANNEL");
            break;
        case SC_STATUS_GETTING_SSID_PSWD:
        	LOG_OUT(INFO, "SC_STATUS_GETTING_SSID_PSWD");
            break;
        case SC_STATUS_LINK:
        	LOG_OUT(INFO, "SC_STATUS_LINK");
            wifi_config_t *wifi_config = pdata;
            LOG_OUT(INFO, "SSID:%s", wifi_config->sta.ssid);
            LOG_OUT(INFO, "PASSWORD:%s", wifi_config->sta.password);
            ESP_ERROR_CHECK( esp_wifi_disconnect() );
            ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, wifi_config) );
            ESP_ERROR_CHECK( esp_wifi_connect() );
            break;
        case SC_STATUS_LINK_OVER:
        	LOG_OUT(INFO, "SC_STATUS_LINK_OVER");
            if (pdata != NULL) {
                sc_callback_data_t *sc_callback_data = (sc_callback_data_t *)pdata;
                switch (sc_callback_data->type) {
                    case SC_ACK_TYPE_ESPTOUCH:
                    	LOG_OUT(INFO, "Phone ip: %d.%d.%d.%d", sc_callback_data->ip[0], sc_callback_data->ip[1], sc_callback_data->ip[2], sc_callback_data->ip[3]);
                    	LOG_OUT(INFO, "TYPE: ESPTOUCH");
                        break;
                    case SC_ACK_TYPE_AIRKISS:
                    	LOG_OUT(INFO, "TYPE: AIRKISS");
                        break;
                    default:
                    	LOG_OUT(ERROR, "TYPE: ERROR");
                        break;
                }
            }
            xEventGroupSetBits(wifi_event_group, ESPTOUCH_DONE_BIT);
            break;
        default:
            break;
    }
}

void smartconfig_example_task(void * parm)
{
    EventBits_t uxBits;
    ESP_ERROR_CHECK( esp_smartconfig_set_type(SC_TYPE_ESPTOUCH_AIRKISS) );
    ESP_ERROR_CHECK( esp_smartconfig_start(sc_callback) );
    while (1) {
        uxBits = xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT | ESPTOUCH_DONE_BIT, true, false, portMAX_DELAY);
        if(uxBits & CONNECTED_BIT) {
        	LOG_OUT(INFO, "WiFi Connected to ap");
        }
        if(uxBits & ESPTOUCH_DONE_BIT) {
        	LOG_OUT(INFO, "smartconfig over");
            esp_smartconfig_stop();
            vTaskDelete(NULL);
        }
    }
}


static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
    	//在这里判断要不要重新进行smartconfig配置
        xTaskCreate(smartconfig_example_task, "smartconfig_example_task", 4096, NULL, 3, NULL);
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}



uint32_t WIFI_SetWifiModeStation( void )
{
    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_start() );

	return RET_Ok;
}









