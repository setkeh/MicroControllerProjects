#include "blink.h"
#include "wifi.h"
#include "os_type.h"
#include "ets_sys.h"
#include "osapi.h"
#include "user_interface.h"

void blink_timerfunc(void *arg)
{
  wifi_get_ip_info(0, &info);

  //Do blinky stuff
  if (GPIO_REG_READ(GPIO_OUT_ADDRESS) & (1 << blink_pin))
  {
    // set gpio low
    gpio_output_set(0, (1 << blink_pin), 0, 0);
    os_printf("LED state - %s IP: %d.%d.%d.%d\n", "LOW", IP2STR(&info.ip.addr));
  }
  else
  {
    // set gpio high
    gpio_output_set((1 << blink_pin), 0, 0, 0);
    os_printf("LED state - %s IP: %d.%d.%d.%d\n", "HIGH", IP2STR(&info.ip.addr));
  }
}