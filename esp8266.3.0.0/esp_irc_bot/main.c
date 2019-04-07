#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "uart.h"
#include "user_interface.h"
#include "user_config.h"
#include "blink.h"
#include "wifi.h"

void ICACHE_FLASH_ATTR user_pre_init(void);

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
  os_timer_setfn(&blink_timer, (os_timer_func_t *)blink_timerfunc, NULL);
  os_timer_arm(&blink_timer, 5000, 1);
}