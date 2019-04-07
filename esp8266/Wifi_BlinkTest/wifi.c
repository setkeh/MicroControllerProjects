#include "wifi.h"
#include "user_interface.h"
#include "os_type.h"
#include "ets_sys.h"
#include "osapi.h"

// Init Wifi
const char ssid[32] = wifi_ssid;
const char password[32] = wifi_password;

void ICACHE_FLASH_ATTR wifi_init() {
  wifi_set_opmode( STATION_MODE );
  os_memcpy(&stationConf.ssid, ssid, 32);
  os_memcpy(&stationConf.password, password, 32);
  wifi_station_set_config_current(&stationConf);
}