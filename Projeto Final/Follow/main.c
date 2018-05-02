#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "hardware.h"
#include "motors.h"
#include "sensors.h"
#include "utils.h"
#include "timer.h"


int main(void) {
	int velL = 50,velR = 50, contM = 0, velcL = 0, velcR = 0, virar = 0; 
	// int conts = 0;
	// int threshold = 800;
	// hardware_init();
	// //set_motors(velL,velR);
	// for (;;) {
	// 	if(sensors[0]<threshold)
	// 		led_control(RED, ON);
	// 	else
	// 		led_control(RED, OFF);

	// 	if(sensors[1]<threshold)
	// 		led_control(BLUE, ON);
	// 	else
	// 		led_control(BLUE, OFF);

	// 	if(sensors[2]<threshold)
	// 		led_control(YELLOW, ON);
	// 	else
	// 		led_control(YELLOW, OFF);

		// sensors_update();
		// int i = 0;
		// conts = 0;
		// for(i = 0; i < 7;i++){
		// 	if(sensors[i]<400){
		// 		conts++;
		// 	}
		// }
		// if(conts==1){
		// 	led_control(YELLOW,ON);
		// 	led_control(BLUE, OFF);
		// 	led_control(RED,OFF);
		// }
		// else if(conts==2){
		// 	led_control(YELLOW,OFF);
		// 	led_control(BLUE,ON);
		// 	led_control(RED,OFF);
		// }else if(conts==3){
		// 	led_control(YELLOW,OFF);
		// 	led_control(BLUE,OFF);
		// 	led_control(RED,ON);
		// }else if(conts == 4){
		// 	led_control(YELLOW,ON);
		// 	led_control(BLUE,ON);
		// 	led_control(RED,OFF);
		// }else if(conts == 5){
		// 	led_control(YELLOW,ON);
		// 	led_control(BLUE,OFF);
		// 	led_control(RED,ON);

		// }else if(conts == 6){
		// 	led_control(YELLOW,OFF);
		// 	led_control(BLUE,ON);
		// 	led_control(RED,ON);
		// }else if(conts == 7){
		// 	led_control(YELLOW,ON);
		// 	led_control(BLUE,ON);
		// 	led_control(RED,ON);
		// }
			if(sensors[5] > 500 || sensors[6] > 0){
				virar = 1;
				
			}else{
				virar = 0;
			}
			if(sensors[2] < 500 ){//virar esquerda
					set_motors(velcL,50);
					sensors_update();
					while(sensors[2] < 500){
						sensors_update();
						velL-=2;
						set_motors(velL,velR);//mudar a velocidade dos motores para fazer a rotação à esquerda
						velcL = velL;
					}
				}
			else if(sensors[4] < 500){//virar direita
					set_motors(50,velcR);
					sensors_update();
					while(sensors[4] < 500){
						sensors_update();
						velR-=2;
						set_motors(velL,velR);//mudar a velocidade dos motores para fazer a rotação à direita
						velcR = velL;
					}
				}
		
	// }
	return 0;
}
