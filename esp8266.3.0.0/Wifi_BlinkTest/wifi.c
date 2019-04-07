#include "wifi.h"
#include "user_config.h"

void ICACHE_FLASH_ATTR wifi_init(void)
{
  wifi_set_opmode( STATION_MODE );
  os_memcpy(&stationConf.ssid, ssid, 32);
  os_memcpy(&stationConf.password, password, 32);
  wifi_station_set_config_current(&stationConf);
}