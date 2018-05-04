#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"

#define VEL_MAX 150
#define LINE_THRESHOLD 200
#define DISTANCE_THRESHOLD 100

int facing(){ //funçao que verifica se o adversario esta frente a frente

    update_distance_sensors();

    return (distance_sensors[0] > DISTANCE_THRESHOLD && distance_sensors[1] > DISTANCE_THRESHOLD);
}

void search(){ //funçao que gira o sumo ate ficar de frente para o adversario

    while (!facing()){
        motors (0, VEL_MAX/2);
    }
    motors (0, 0);
}

void turn_left(){ //funçao para girar para a esquerda
     motors(20, VEL_MAX);
}

void turn_right(){ //funçao para girar para a direita
     motors(VEL_MAX, 20);
}

int main () {
    motors_init();
    timer_init();
    sensors_init();
   
    for (;;) {

        update_line_sensors();

	if (line_sensors[0] < LINE_THRESHOLD && line_sensors[1] < LINE_THRESHOLD) //se ler a linha pelos dois sensores, anda para trás
	    motors (-VEL_MAX, -VEL_MAX);

	    else if (line_sensors[0] < LINE_THRESHOLD) //se ler a linha do lado esquerdo, virar para a direita
            turn_right();

	    else if (line_sensors[1] < LINE_THRESHOLD) //se ler a linha do lado direito, virar para a esquerda
            turn_left();

        if (facing()) //se estiver de frente para o adversario, acelera em direção a ele
            motors (VEL_MAX, VEL_MAX);
        else
            search(); //se não estiver de frente, procura o adversario
    }

    return 0;
}
