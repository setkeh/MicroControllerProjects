#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "uart.h"
#include "user_interface.h"
#include "user_config.h"
#include "blink.h"
#include "wifi.h"
#include "espconn.h"
#include "irc.h"

void ICACHE_FLASH_ATTR user_pre_init(void);
struct espconn esp_conn;
os_timer_t wifi_timer;

void ICACHE_FLASH_ATTR
wifi_timer_cb(void *arg) {

  os_timer_disarm(&wifi_timer);

  uint8 status;
  struct ip_info ipconfig;
  status = wifi_station_get_connect_status();

  wifi_get_ip_info(STATION_IF, &ipconfig);

  if (status == STATION_GOT_IP && ipconfig.ip.addr != 0) {
    tcp_client_connect();
    return;
  } else {
    os_timer_arm(&wifi_timer, 2000, 1);
  }
}

void ICACHE_FLASH_ATTR 
user_init()
{
  uart_div_modify(0, UART_CLK_FREQ / 115200);
  system_set_os_print(TRUE);

  wifi_init();

  // init gpio subsytem
  gpio_init();
  
  // configure UART TXD to be GPIO1, set as output
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2); 

  // setup timer (500ms, repeating)
  /*os_timer_setfn(&blink_timer, (os_timer_func_t *)blink_timerfunc, NULL);
  os_timer_arm(&blink_timer, 5000, 1);*/

  os_timer_disarm(&wifi_timer); 
  os_timer_setfn(&wifi_timer, wifi_timer_cb, NULL); /* Set callback for timer */
  os_timer_arm(&wifi_timer, 2000 , 1);
}