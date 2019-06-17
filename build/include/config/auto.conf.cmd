deps_config := \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/app_update/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/aws_iot/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/console/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/esp8266/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/esp_http_client/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/esp_http_server/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/freertos/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/libsodium/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/log/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/lwip/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/mdns/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/mqtt/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/newlib/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/pthread/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/spiffs/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/ssl/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/tcpip_adapter/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/util/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/vfs/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/wifi_provisioning/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/wpa_supplicant/Kconfig \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/bootloader/Kconfig.projbuild \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/esptool_py/Kconfig.projbuild \
	/home/sunka/esp/ESP8266_RTOS_SDK/components/partition_table/Kconfig.projbuild \
	/home/sunka/esp/ESP8266_RTOS_SDK/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
