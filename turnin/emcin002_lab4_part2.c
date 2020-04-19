/*	Author: emcin002
 *  Partner(s) Name: 
 *	Lab Section: 027
 *	Assignment: Lab 4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum State {Start, INIT, INCREMENT, DECREMENT, ZERO} state;
unsigned char tmpA = 0x00;
unsigned char tmpC = 0x00;

void Tick() {
	switch(state) {
		case Start:
			tmpC = 0x07;
			state = INIT;
			break;
		case INIT:
			if (tmpA == 0x01) {
				if (tmpC < 0x09) {
					tmpC++;
				}
				state = INCREMENT;
			}
			if (tmpA == 0x02) {
				if (tmpC > 0x00) {
					tmpC--;
				}
				state = DECREMENT;
			}	
			if (tmpA == 0x03) {
				state = ZERO;
			}
			break;
		case INCREMENT:	
			if (tmpA == 0x00) {
				state = INIT;
			}
			if (tmpA == 0x03) {
				state = ZERO;
			}
			break;
		case ZERO:
			if (tmpA == 0x00) {
				state = INIT;
			}
			break;
		case DECREMENT:
			if (tmpA == 0x00) {
				state = INIT;
			}
			if (tmpA == 0x03) {
				state = ZERO;
			}
			break;
		default:
			break;
	}
	switch(state) {
		case Start:
			break;
		case INIT:
			break;
		case INCREMENT:
			break;
		case DECREMENT:
			break;
		case ZERO:
			tmpC = 0x00;
			break;
		default:
			break;
	}
}


int main(void) {
	DDRA = 0x00; PORTA = 0x00;
	DDRC = 0xFF; PORTC = 0x00;   
    while (1) {
		tmpA = PINA;
		Tick();
  		PORTC = tmpC;
    }
    return 1;
}
