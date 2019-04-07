#include "flashmap.h"

void ICACHE_FLASH_ATTR user_pre_init(void) {
   if(!system_partition_table_regist(at_partition_table, sizeof(at_partition_table) / sizeof(at_partition_table[0]), SPI_FLASH_SIZE_MAP)){
      os_printf("system_partition_table_regist fail\r\n");
      while(1);
   }
}