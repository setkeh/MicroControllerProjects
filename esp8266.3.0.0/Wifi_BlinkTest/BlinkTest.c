#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "uart.h"
#include "user_interface.h"
#include "user_config.h"

static const partition_item_t at_partition_table[] = {
    { SYSTEM_PARTITION_BOOTLOADER,          0x0,                                    0x1000},
    { SYSTEM_PARTITION_OTA_1,               0x1000,                                 SYSTEM_PARTITION_OTA_SIZE},
    { SYSTEM_PARTITION_OTA_2,               SYSTEM_PARTITION_OTA_2_ADDR,            SYSTEM_PARTITION_OTA_SIZE},
    { SYSTEM_PARTITION_RF_CAL,              SYSTEM_PARTITION_RF_CAL_ADDR,           0x1000},
    { SYSTEM_PARTITION_PHY_DATA,            SYSTEM_PARTITION_PHY_DATA_ADDR,         0x1000},
    { SYSTEM_PARTITION_SYSTEM_PARAMETER,    SYSTEM_PARTITION_SYSTEM_PARAMETER_ADDR, 0x3000},
};

void ICACHE_FLASH_ATTR user_pre_init(void) {
   if(!system_partition_table_regist(at_partition_table, sizeof(at_partition_table) / sizeof(at_partition_table[0]), SPI_FLASH_SIZE_MAP)){
      os_printf("system_partition_table_regist fail\r\n");
      while(1);
   }
}

// Define Pin GPIO_2 as the LED test Pin
static const int pin = 2;
static volatile os_timer_t some_timer;
struct ip_info info;

void some_timerfunc(void *arg)
{
  wifi_get_ip_info(0, &info);

  //Do blinky stuff
  if (GPIO_REG_READ(GPIO_OUT_ADDRESS) & (1 << pin))
  {
    // set gpio low
    gpio_output_set(0, (1 << pin), 0, 0);
    os_printf("LED state - %s IP: %d.%d.%d.%d\n", "LOW", IP2STR(&info.ip.addr));
  }
  else
  {
    // set gpio high
    gpio_output_set((1 << pin), 0, 0, 0);
    os_printf("LED state - %s IP: %d.%d.%d.%d\n", "HIGH", IP2STR(&info.ip.addr));
  }
}

void ICACHE_FLASH_ATTR 
user_init()
{
  uart_div_modify(0, UART_CLK_FREQ / 115200);
  system_set_os_print(TRUE);

  // Init Wifi
  const char ssid[32] = wifi_ssid;
  const char password[32] = wifi_password;

  struct station_config stationConf;

  wifi_set_opmode( STATION_MODE );
  os_memcpy(&stationConf.ssid, ssid, 32);
  os_memcpy(&stationConf.password, password, 32);
  wifi_station_set_config_current(&stationConf);
  
  // init gpio subsytem
  gpio_init();
  
  // configure UART TXD to be GPIO1, set as output
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2); 
  gpio_output_set(0, 0, (1 << pin), 0);

  // setup timer (500ms, repeating)
  os_timer_setfn(&some_timer, (os_timer_func_t *)some_timerfunc, NULL);
  os_timer_arm(&some_timer, 12000, 1);
}