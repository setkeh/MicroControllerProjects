#include "os_type.h"

// Define Pin GPIO_2 as the LED test Pin
static const int blink_pin = 2;

static volatile os_timer_t blink_timer;

void blink_timerfunc(void *arg);