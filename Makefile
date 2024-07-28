
CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size

CFLAGS+= -I. -Os -DF_CPU=16000000UL -mmcu=atmega328p --std=c99
CFLAGS+= -ffunction-sections -fdata-sections

LDFLAGS+= -s -DF_CPU=16000000UL -mmcu=atmega328p
LDFLAGS+= -Wl,--gc-sections
LDFLAGS += -Wl,-u,vfprintf -lprintf_flt

MAIN_OBJS = main.o
MAIN_OBJS += uartio.o
MAIN_OBJS += fifo.o
MAIN_OBJS += tools.o
MAIN_OBJS += contr.o
MAIN_OBJS += spi.o
MAIN_OBJS += lcd.o
MAIN_OBJS += cons.o
MAIN_OBJS += font.o

MAIN_ELF = main.elf
MAIN_HEX = main.hex

all: $(MAIN_HEX)

$(MAIN_ELF): $(MAIN_OBJS)
	$(CC) $(LDFLAGS) -o $(MAIN_ELF) $(MAIN_OBJS)
	$(SIZE) --format=berkeley $@

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c -o $*.o
	$(CC) -MM $(CFLAGS) $*.c > $*.d


$(MAIN_HEX): $(MAIN_ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

AVRDUDE = sudo avrdude
TTY_PORT =  /dev/ttyUSB0
TTY_SPEED = 115200
BACKUP = $(MAIN_HEX).bak

upload: $(MAIN_HEX)
	$(AVRDUDE) -c arduino -p ATMEGA328P -P $(TTY_PORT) -b $(TTY_SPEED) -U flash:w:$<

download:
	$(AVRDUDE) -F -V -c arduino -p ATMEGA328P -P $(TTY_PORT) -b $(TTY_SPEED) -U flash:r:$(BACKUP):i

clean:
	rm -f *.i *.o *.s
	rm -f *.elf *.bin *~ *.hex
	rm -f *.d

-include $(MAIN_OBJS:.o=.d)

#EOF
