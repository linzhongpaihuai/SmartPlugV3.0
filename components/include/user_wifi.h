/*
 * user_wifi.h
 *
 *  Created on: 2018��10��21��
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
	char 				szSsid[WIFI_SSID_LEN];	//wifi����
	char 				szMac[WIFI_MAC_LEN];	//mac��ַ
	int8_t				iRssi;					//�ź�ǿ�ȵ�λ��dbm����ֵԽ�ӽ�0�ź�Խ��
	int8_t				ucChannel;				//�ŵ�
	char 				szAuthMode[WIFI_AUTHMODE_LEN];	//��������

}WIFI_SCAN_S;

typedef struct tagWifiInfo
{
	uint32_t 				uiIp;
	uint32_t				uiGetWay;
	uint32_t				uiNetMask;

}WIFI_INFO_S;

uint32_t WIFI_SetWifiModeStation( void );


#endif /* __USER_WIFI_H__ */
