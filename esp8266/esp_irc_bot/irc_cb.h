os_timer_t user_timer;
os_timer_t nick_timer;
os_timer_t join_timer;
os_timer_t hello_timer;

LOCAL void ICACHE_FLASH_ATTR send_user_timer(void *arg);
LOCAL void ICACHE_FLASH_ATTR send_nick_timer(void *arg);
LOCAL void ICACHE_FLASH_ATTR send_join_timer(void *arg);
LOCAL void ICACHE_FLASH_ATTR send_hello_timer(void *arg);

LOCAL void ICACHE_FLASH_ATTR tcp_sent_cb(void *arg);
LOCAL void ICACHE_FLASH_ATTR tcp_recv_cb(void *arg, char *pusrdata, unsigned short lenght);
LOCAL void ICACHE_FLASH_ATTR tcp_write_finish();

void ICACHE_FLASH_ATTR tcp_connected_callback(void *arg);
void ICACHE_FLASH_ATTR tcp_reconnected_callback(void *arg, sint8 err);

void ICACHE_FLASH_ATTR init_irc_on_connect(struct espconn *pespconn);