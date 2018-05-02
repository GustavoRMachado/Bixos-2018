#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"

void virarEsquerda(){
     motors(0, 50);
}

void virarDireita(){
     motors(50, 0);
}

int main () {
    motors_init();
    timer_init();
    sensors_init();
    int velL = 50, velR = 50, estrategia = 0, relogio = 0;
    for (;;) {
        if(estrategia == 0){
            if(line_sensors[0] > 500){
               virarEsquerda();
            }
            if(line_sensors[1] > 500){
                virarDireita();               
            }
            if(distance_sensors[0]> 1000 || distance_sensors[1] > 1000){
                motors(255,255);
            }else{
                motors(-255, 255);
            }
        }else{
            if(line_sensors[0] > 500){
                motors(50, 0);
            }
            if(line_sensors[1] > 500){
                motors(40, 0);
            }
            if(distance_sensors[0]> 1000){
                relogio = get_tick() + 400;
                while(relogio > get_tick()){
                    update_line_sensors();
                    if(line_sensors[0] < 500 || line_sensors[1] < 500)
                    motors(255,-255);
                    else if (line_sensors[0] > 500){
                        virarEsquerda();
                    }else if{
                        virarDireita();
                    }
                    relogio ++;
                }
                relogio = get_tick() + 400;
                while(relogio > get_tick()){
                    motors(255,255);
                    relogio ++;
                }
            }else if(distance_sensors[1] > 1000){
                  relogio = get_tick() + 400;
                while(relogio > get_tick()){
                    update_line_sensors();
                    if(line_sensors[0] < 500 || line_sensors[1] < 500)
                    motors(255,-255);
                    else if (line_sensors[0] > 500){
                        virarEsquerda();
                    }else if{
                        virarDireita();
                    }
                    relogio ++;
                }
                relogio = get_tick() + 400;
                while(relogio > get_tick()){
                    motors(255,255);
                    relogio ++;
                }
            }else{
                motors(-255, 255);
            }
        }
    }
    return 0;
}