CPU	= msp430g2553
CFLAGS	= -mmcu=${CPU} -Os -I../h
LDFLAGS	= -L../lib -L/opt/ti/msp430_gcc/include/ -lTimer

CC	= msp430-elf-gcc
AS	= msp430-elf-as -mmcu=${CPU} -c

OBJECTS = main.o switches.o buzzer.o game.o wdt_handler.o ../lcdLib/lcdutils.o ../lcdLib/lcddraw.o ../lcdLib/font-5x7.o

all: toy.elf

toy.elf: ${OBJECTS}
	${CC} ${CFLAGS} -o $@ $^ ${LDFLAGS}


load: toy.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
