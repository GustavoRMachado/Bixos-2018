OBJECTS = main.o motors.o sensors.o timer.o utils.o
all: main.hex

main.hex:main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.elf: $(OBJECTS)
	rm -f main.elf
	avr-gcc -o main.elf $(OBJECTS) -mmcu=atmega168 -std=c99 -Wall -Wextra -Os

.c.o:
	avr-gcc -c $< -o $@ -mmcu=atmega168 -std=c99 -Wall -Wextra -Os

clean:
	rm -f $(OBJECTS) main.hex main.elf

flash:
	avrdude -c usbasp -p atmega168 -U flash:w:main.hex:i