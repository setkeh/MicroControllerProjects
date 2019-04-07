SDK=/opt/esp8266-nonos-sdk.3.0.0
CC = xtensa-lx106-elf-gcc
CFLAGS = -I. -I$(SDK)/include -I$(SDK)/include/json -I$(SDK)/driver_lib/include/driver -I$(SDK)/driver_lib/driver -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lc -ldriver -lgcc -lcrypto -lphy -lpp -lnet80211 -llwip -lwpa -lwpa2 -lcrypto -lmain -ljson -lupgrade -lmbedtls -lwps -lsmartconfig -lairkiss -Wl,--end-group -lgcc
LDDIR = ../ld
LDFLAGS = -T$(LDDIR)/eagle.app.v6.ld -L$(SDK)/lib -L$(SDK)/driver_lib/driver -L$(SDK)/driver_lib/include/driver

all: 
	$(MAKE) BlinkTest
	$(MAKE) BlinkTest-0x00000.bin
	$(MAKE) flash

BlinkTest-0x00000.bin: BlinkTest
	esptool.py elf2image $^

BlinkTest: BlinkTest.o

BlinkTest.o: BlinkTest.c

flash: BlinkTest-0x00000.bin
	esptool.py write_flash 0x0 BlinkTest-0x00000.bin 0x10000 BlinkTest-0x10000.bin

details: 
	esptool.py image_info BlinkTest-0x00000.bin
	esptool.py esp8266 image_info BlinkTest-0x10000.bin

clean:
	rm -f BlinkTest BlinkTest.o BlinkTest-0x00000.bin BlinkTest-0x10000.bin
	esptool.py erase_flash
	$(MAKE) flash-factory

# Flash the factory Interupt and control binaries.
flash-factory:
	esptool.py write_flash 0xFC000 $(SDK)/bin/esp_init_data_default_v05.bin