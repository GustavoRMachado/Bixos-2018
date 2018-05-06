#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"
#include "usart.h"

#define VEL_MAX 180
#define VEL_MED 120
#define LINE_THRESHOLD 600
#define DISTANCE_THRESHOLD 400

void check_edge(){
    
    update_line_sensors();

    if (line_sensors[0] < LINE_THRESHOLD && line_sensors[1] < LINE_THRESHOLD){
        motors (-VEL_MED, -VEL_MED);
        _delay_ms(400);
    }

    if (line_sensors[0] < LINE_THRESHOLD && line_sensors[1] > LINE_THRESHOLD){
        motors (VEL_MED, -VEL_MED);
        _delay_ms(350);
    }

    if (line_sensors[0] > LINE_THRESHOLD && line_sensors[1] < LINE_THRESHOLD){
        motors (-VEL_MED, VEL_MED);
        _delay_ms(350);
    }
}

int facing(){ //funçao que verifica se o adversario esta frente a frente

    update_distance_sensors();

    return (distance_sensors[0] > DISTANCE_THRESHOLD || distance_sensors[1] > DISTANCE_THRESHOLD);
}

void search(){ //funçao que gira o sumo ate ficar de frente para o adversario

        motors (0, VEL_MED);
}

int main () {
    
    motors_init();
    timer_init();
    sensors_init();
    usart_init();

    for (;;) {
        
        check_edge();

        if (facing()) //se estiver de frente para o adversario, acelera em direção a ele
           motors (VEL_MAX, VEL_MAX);
        else
           search(); //se não estiver de frente, procura o adversario
    }

    return 0;
}
