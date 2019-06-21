/*
 * user_wifi.h
 *
 *  Created on: 2018年10月21日
 *      Author: lenovo
 */

#ifndef __USER_WIFI_H__
#define __USER_WIFI_H__

#define WIFI_SCAN_NUM		20

#ifndef WIFI_SSID_LEN
	#define WIFI_SSID_LEN	32
#endif

#ifndef WIFI_MAC_LEN
	#define WIFI_MAC_LEN 	20
#endif

#define WIFI_AUTHMODE_LEN 	15

typedef enum {
	WIFI_SCAN_STATUS_IDLE = 0,
	WIFI_SCAN_STATUS_BUSY,
	WIFI_SCAN_STATUS_FINISH

} WIFI_SCAN_STATUS;


typedef struct tagWifiScan
{
	char 				szSsid[WIFI_SSID_LEN];	//wifi名称
	char 				szMac[WIFI_MAC_LEN];	//mac地址
	int8_t				iRssi;					//信号强度单位是dbm，负值越接近0信号越好
	int8_t				ucChannel;				//信道
	char 				szAuthMode[WIFI_AUTHMODE_LEN];	//加密类型

}WIFI_SCAN_S;

typedef struct tagWifiInfo
{
	uint32_t 				uiIp;
	uint32_t				uiGetWay;
	uint32_t				uiNetMask;

}WIFI_INFO_S;

uint32_t WIFI_SetWifiModeStation( void );


#endif /* __USER_WIFI_H__ */
