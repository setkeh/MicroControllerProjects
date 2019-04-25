#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "uart.h"
#include "user_interface.h"
#include "user_config.h"
#include "espconn.h"
#include "wifi.h"
#include "irc.h"
#include "irc_cb.h"

LOCAL void ICACHE_FLASH_ATTR
send_user_timer(void *arg) {
  struct espconn *pespconn=(struct espconn *)arg;
  char *data = "USER ESP8266 1 x : ESP8266Bot";
  espconn_sent(pespconn, data, strlen(data));
}

LOCAL void ICACHE_FLASH_ATTR
send_nick_timer(void *arg) {
  struct espconn *pespconn=(struct espconn *)arg;
  char *data = "NICK ESP8266Bot";
  espconn_sent(pespconn, data, strlen(data));
}

LOCAL void ICACHE_FLASH_ATTR
send_join_timer(void *arg) {
  struct espconn *pespconn=(struct espconn *)arg;
  char *data = "JOIN #thesetkehproject";
  espconn_sent(pespconn, data, strlen(data));
}

LOCAL void ICACHE_FLASH_ATTR
send_hello_timer(void *arg) {
  struct espconn *pespconn=(struct espconn *)arg;
  char *data = "PRIVMSG #thesetkehproject : ESP8266 Hello World";
  espconn_sent(pespconn, data, strlen(data));
}

void ICACHE_FLASH_ATTR
init_irc_on_connect(struct espconn *pespconn) {
  os_timer_disarm(&user_timer); 
  os_timer_setfn(&user_timer, send_user_timer, pespconn);
  os_timer_arm(&user_timer, 3000 , 0);

  os_timer_disarm(&nick_timer); 
  os_timer_setfn(&nick_timer, send_nick_timer, pespconn);
  os_timer_arm(&nick_timer, 5000 , 0);

  os_timer_disarm(&join_timer); 
  os_timer_setfn(&join_timer, send_join_timer, pespconn);
  os_timer_arm(&join_timer, 7000 , 0);

  os_timer_disarm(&hello_timer); 
  os_timer_setfn(&hello_timer, send_hello_timer, pespconn);
  os_timer_arm(&hello_timer, 9000 , 0);
}

LOCAL void ICACHE_FLASH_ATTR
tcp_sent_cb(void *arg) {
  os_printf("Data Sent\r\n");
}

LOCAL void ICACHE_FLASH_ATTR
tcp_recv_cb(void *arg, char *pusrdata, unsigned short lenght) {
  os_printf("%s \r\n", pusrdata);
}

void ICACHE_FLASH_ATTR
tcp_connected_callback(void *arg) {
  struct espconn *pespconn = arg;

  os_printf("Connect to IRC Successful !! \r\n");

  espconn_regist_recvcb(pespconn, tcp_recv_cb);
  espconn_regist_sentcb(pespconn, tcp_sent_cb);

  espconn_set_opt(pespconn, 0x04);
  init_irc_on_connect(pespconn);
}

void ICACHE_FLASH_ATTR
tcp_reconnected_callback(void *arg, sint8 err) {
  os_printf("IRC ERRROR %d: Attempting reconnect!!\r\n", err);
  tcp_client_connect();
}