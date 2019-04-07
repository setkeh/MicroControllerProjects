#include "os_type.h"

static volatile os_timer_t blink_timer;

void blink_timerfunc(void *arg);