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

enum State {Start, LOCK, PUSH, RELEASE, UNLOCK} state;
unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

void Tick() {
	switch(state) {
		case Start:
			state = LOCK;
			break;
		case LOCK:
			if (tmpA == 0x04) {
				state = PUSH;
			}	
			break;
		case PUSH:	
        		if (tmpA == 0x00) {
        			state = RELEASE;
        		}
			if(tmpA == 0x05 || tmpA == 0x06) {		
        			state = LOCK;
        		}
			break;
		case RELEASE:
			if (tmpA == 0x02) {
				state = UNLOCK;
			}
			if (tmpA == 0x01) {
				state = LOCK;
			}
			if (tmpA == 0x04) {
				state = PUSH;
			}
			break;
		case UNLOCK:
			if (tmpA == 0x80) {
				state = LOCK;
			}
			break;
		default:
			break;
	}
	switch(state) {
		case Start:
			break;
		case LOCK:
			tmpB = 0x00;
			break;
		case PUSH:
			break;
		case RELEASE:
			break;
		case UNLOCK:
			tmpB = 0x01;
			break;
		default:
			break;
	}
}


int main(void) {
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;   
    while (1) {
		tmpA = PINA;
		Tick();
  		PORTB = tmpB;
    }
    return 1;
}
