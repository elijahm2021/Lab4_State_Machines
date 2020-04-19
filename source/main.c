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

enum State {Start, ONE, TWO, BETWEEN_ONE_TWO, BETWEEN_TWO_ONE} state;
unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

void Tick() {
	switch(state) {
		case Start:
			state = ONE;
			break;
		case ONE:
			if (tmpA == 0x00) {
				state = BETWEEN_ONE_TWO;
			}
			else {
				state = ONE;
			}	
			break;
		case BETWEEN_ONE_TWO:	
			if (tmpA == 0x01) {
				state = TWO;
			}
			else {
				state = BETWEEN_ONE_TWO;
			}
			break;
		case TWO:
			if (tmpA == 0x00) {
				state = BETWEEN_TWO_ONE;
			}
			else {
				state = TWO;
			}
			break;
		case BETWEEN_TWO_ONE:
			if (tmpA == 0x01) {
				state = ONE;
			}
			else {
				state = BETWEEN_TWO_ONE;
			}
			break;
		default:
			break;
	}
	switch(state) {
		case Start:
			break;
		case ONE:
			tmpB = 0x01;
			break;
		case TWO:
			tmpB = 0x02;
			break;
		case BETWEEN_ONE_TWO:
			tmpB = 0x01;
			break;
		case BETWEEN_TWO_ONE:
			tmpB = 0x02;
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
