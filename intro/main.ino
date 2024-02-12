#define INT0_vect _VECTOR(1)        /* External Interrupt Request 0 */
#define TIMER1_OVF_vect _VECTOR(13) /* Timer 1 Overflow */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

char red =0;
char green =0;
ISR(INT0_vect){
   red=~red;
   if(red==0){PORTB = PORTB & 0b111011111;}
   else	   {PORTB = PORTB   | 0b00010000;}
}

ISR(TIMER1_OVF_vect) {
   green = ~green;
   if(green ==0){PORTB = PORTB & 0b1101111;}
   else 		{PORTB = PORTB  | 0b00100000;}
   }
   
   int main(){
      //set port direecton
      DDRB = 0b00110000; //  PB5/D13  PB4/D12  output
      
      //set INT0
      EICRA =EICRA| 0b00000010 ;//INT0 Falling Edge
      EIMSK =1;					//Enable INT0
      
      
      // set TMR1
      TCCR1A =0b00000000;
      TCCR1B= 0b00000101;// 1024 prescale
      
      TCNT1 = 3036; //65536-62500
      TIFR1 = 0b00000001;//Clear Overflow Status
      TIMSK1= 0b00000001;//Enable Overflow Interrupt
      
      //Turn on global interrupts
      sei();
      
      while(1); //No nothing
      
      return 0;
      
   }
