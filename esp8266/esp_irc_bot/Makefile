SDK=/opt/esp8266-nonos-sdk
CC = xtensa-lx106-elf-gcc
CFLAGS = -I. -I$(SDK)/include -I$(SDK)/include/json -I$(SDK)/driver_lib/include/driver -I$(SDK)/driver_lib/driver -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lc -ldriver -lgcc -lcrypto -lphy -lpp -lnet80211 -llwip -lwpa -lwpa2 -lcrypto -lmain -ljson -lupgrade -lmbedtls -lwps -lsmartconfig -lairkiss -Wl,--end-group -lgcc
LDDIR = ../ld
LDFLAGS = -T$(LDDIR)/eagle.app.v6.ld -L$(SDK)/lib -L$(SDK)/driver_lib/driver -L$(SDK)/driver_lib/include/driver
MAIN = main
SRC = blink.c wifi.c main.c flashmap.c
OBJ = main.o blink.o wifi.o flashmap.o

all: 
	$(MAKE) $(MAIN)
	$(MAKE) $(MAIN)-0x00000.bin
	$(MAKE) flash

$(MAIN)-0x00000.bin: $(MAIN)
	$(ESP_TOOL) elf2image $^

$(MAIN): $(OBJ)

$(MAIN).o: $(SRC)

flash: $(MAIN)-0x00000.bin
	$(ESP_TOOL) write_flash 0x0 $(MAIN)-0x00000.bin 0x10000 $(MAIN)-0x10000.bin

details: 
	$(ESP_TOOL) image_info $(MAIN)-0x00000.bin
	$(ESP_TOOL) esp8266 image_info $(MAIN)-0x10000.bin

clean:
	rm -f $(OBJ) $(MAIN)-0x00000.bin $(MAIN)-0x10000.bin

clean_flash:
	$(ESP_TOOL) erase_flash
	$(MAKE) flash-factory

# Flash the factory Interupt and control binaries.
flash-factory:
	$(ESP_TOOL) write_flash 0xFC000 $(SDK)/bin/esp_init_data_default_v05.bin
