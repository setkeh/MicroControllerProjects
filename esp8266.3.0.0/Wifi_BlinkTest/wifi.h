// Init Wifi
const char ssid[32] = wifi_ssid;
const char password[32] = wifi_password;

struct station_config stationConf;
struct ip_info info;

void ICACHE_FLASH_ATTR wifi_init(void);