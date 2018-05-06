#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "hardware.h"
#include "motors.h"
#include "sensors.h"
#include "utils.h"
#include "timer.h"

// led_control(RED, ON);

#define THRESHOLD 500
#define VEL_MAX 250

int turn_left(){ //funçao para virar curva a esquerda e retornar a velocidade correta
    
    int count=1;
   
    while (sensors[2] < THRESHOLD){ //roda até acertar o angulo da curva
        set_motors (VEL_MAX-count, VEL_MAX);
        count++;
        sensors_update();
    }
    
    return (VEL_MAX-count);
}

int turn_right(){

    int count=1;
  
    while (sensors[4] < THRESHOLD){ //funçao para virar curva a direita e retornar a velocidade correta
        set_motors (VEL_MAX, VEL_MAX-count);
        count++;
        sensors_update();
    }

    return (VEL_MAX-count);
}

int main(void) {
	hardware_init();

	for (;;) {
            sensors_update();

            if (sensors[2] < THRESHOLD) //se o sensor 2 parar de ler a linha, vira a direita
                set_motors(VEL_MAX, turn_right());

            if (sensors[4] < THRESHOLD) //se o sensor 4 parar de lera linha, vira esquerda
                set_motors(turn_left(), VEL_MAX);

            if (sensors[2] > THRESHOLD && sensors[3] > THRESHOLD && sensors[4] > THRESHOLD) //se ler nos 3 sensores, continua reto
                set_motors(VEL_MAX, VEL_MAX);
	}
	return 0;
}
