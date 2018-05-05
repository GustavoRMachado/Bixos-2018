ID = atmega168
OBJECTS = main.o motors.o sensors.o timer.o utils.o usart.o
all: main.hex

main.hex:main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.elf: $(OBJECTS)
	rm -f main.elf
	avr-gcc -DF_CPU=16000000 -o main.elf $(OBJECTS) -mmcu=$(ID) -std=c99 -Wall -Wextra -Os

.c.o:
	avr-gcc -DF_CPU=16000000 -c $< -o $@ -mmcu=$(ID) -std=c99 -Wall -Wextra -Os

clean:
	rm -f $(OBJECTS) main.hex main.elf

flash:
	avrdude -c usbasp -p m168pb -U flash:w:main.hex:i
