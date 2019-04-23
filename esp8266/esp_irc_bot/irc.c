#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "uart.h"
#include "user_interface.h"
#include "user_config.h"
#include "espconn.h"
#include "wifi.h"

void ICACHE_FLASH_ATTR
tcp_recv_cb(void *arg, char *pusrdata, unsigned short lenght) {
  os_printf("Data Recived: %s \r\n", pusrdata);
}

LOCAL void ICACHE_FLASH_ATTR
tcp_connected_callback(void *arg) {
  struct espconn *pespconn = arg;

  os_printf("Connect to IRC Successful !! \r\n");

  espconn_regist_recvcb(pespconn, tcp_recv_cb);
  //espconn_regist_sentcb(pespconn, tcp_sent_cb);
}

LOCAL void ICACHE_FLASH_ATTR
tcp_reconnected_callback() {
  tcp_client_connect();
}

void ICACHE_FLASH_ATTR
tcp_client_connect() {
  LOCAL struct espconn conn;
  static esp_tcp tcp_s;
  LOCAL uint8 esp_tcpip_server[4] = {195, 154, 200, 232};

  os_printf("Entered tcpConnect\r\n");
  conn.proto.tcp = &tcp_s;
  conn.type = ESPCONN_TCP;
  conn.proto.tcp->local_port = espconn_port();
  conn.proto.tcp->remote_port = 6667;
  conn.state = ESPCONN_NONE;
  os_memcpy(conn.proto.tcp->remote_ip, esp_tcpip_server, 4);

  espconn_regist_connectcb(&conn, tcp_connected_callback);
  espconn_regist_reconcb(&conn, tcp_reconnected_callback);
  //espconn_regist_disconcb(&conn, tcp_disconnected_callback);

  espconn_connect(&conn);
}