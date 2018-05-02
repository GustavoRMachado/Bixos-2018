MCU = atmega168

all : main.hex

main.elf : main.o hardware.o motors.o sensors.o timer.o utils.o
	avr-gcc -o main.elf main.o hardware.o motors.o sensors.o timer.o utils.o \
 -mmcu=$(MCU) -std=c99 -Wall -Wextra -Os

main.o : main.c hardware.h motors.h sensors.h utils.h timer.h
	avr-gcc -c main.c -o main.o -mmcu=$(MCU) -std=c99 -Wall -Wextra -Os

hardware.o : hardware.c hardware.h motors.h sensors.h timer.h
	avr-gcc -c hardware.c -o hardware.o -mmcu=$(MCU)  -std=c99 -Wall -Wextra -Os

motors.o : motors.c motors.h hardware.h utils.h
	avr-gcc -c motors.c -o motors.o -mmcu=$(MCU)  -std=c99 -Wall -Wextra -Os

sensors.o : sensors.c sensors.h utils.h
	avr-gcc -c sensors.c -o sensors.o -mmcu=$(MCU) -std=c99 -Wall -Wextra -Os

timer.o : timer.c timer.h
	avr-gcc -c timer.c -o timer.o -mmcu=$(MCU) -std=c99 -Wall -Wextra -Os

utils.o : utils.c utils.h
	avr-gcc -c utils.c -o utils.o -mmcu=$(MCU) -std=c99 -Wall -Wextra -Os

main.hex : main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

flash : 
	avrdude -c usbasp -p $(MCU) -U flash:w:main.hex:i

clean :
	rm main.elf main.hex main.o hardware.o motors.o sensors.o timer.o utils.o
