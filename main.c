/*
 * File:   main.c
 * Author: Fiona Bianchi
 *
 * Copied on 16th January 2022
 */


#include <xc.h>
#include <pic16f884.h> // Apparently this can get included automatically by xc.h

// CONFIG
// Refer to (for example) file:///Applications/microchip/xc8/v2.20/docs/chips/16f884.html
// for pragma config directives for a given device
//
#pragma config FOSC = INTRC_NOCLKOUT  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)

// Don't really need this for this program, in fact it should be off 
// otherwise it'll keep restarting your code!
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR Pin Function Select bit (RE3/MCLR is digital input)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD disabled)

// Make damn sure that this is OFF otherwise your PIC will behave strangely if you 
// even wave your hand near it or the circuit!  Do NOT waste the hours I did 
// on trying to 'debug' weird glitches and pauses
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3/PGM pin has PGM function, low-voltage programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#pragma config DEBUG = OFF      // In-Circuit debugger disabled ( RB6 and RB7 are available as I/O pins)


// The row values need to be inverted since the output drives
// PNP transistors which require 0V output to switch on.
unsigned char row_values_by_column[16] = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0
};

unsigned char porta_value = 0;
unsigned char portd_value = 0;
unsigned char portb_value = 0;

void delay(int delay) {
    while(--delay) {
        delay = delay;
    }
}

void setup_timer(void) {
    // Clear timer0 so it starts counting from 0
    TMR0 = 0; 
    
    // Setup TMR0 options, prescaler applies to Timer0
    // set to 1:64 so that gives 16ms "on" time for LEDs
    // and total time for 16 rows of 256ms or 128ms for 8 rows
    OPTION_REG = 0B00000101; // Setup TMR0 options
    
    // Enable overflow interrupt
    T0IE = 1;  
}

// TODO: Change this code to interleave LEDs and switch scan signals 
// TODO: also only use port A for output for the column/scan lines.
// TODO: Port D can be used for LED outputs (full 8 bits)
// TODO: Port C is going to be busy with PWM and serial comms
// TODO: Port E (0:2) or Port B could be used as switch input
void __interrupt()  isr(void) {
    // Check if Timer0 overflow interrupt is enabled and if 
    // the flag is set indicating that was what caused the interrupt
    // TODO: Refactor to pull this code into another function, ISR 
    // TODO: may be handling lots of interrupts
    if ( (T0IE == 1) && (T0IF == 1)) {
        T0IF = 0;  // Clear interrupt flag 
        
        // This is the starting state before the timer is 
        // setup and interrupts enabled
        if (porta_value == 0 && portd_value == 0) {
            porta_value = 1;
            
        } else if (porta_value > 0) {
            porta_value <<= 1;
            if (porta_value == 0) {
                portd_value = 1;
            }
                
        } else {
            portd_value <<=1;
            if (portd_value == 0) {
                porta_value = 1;
            }
        }
        
        PORTA = porta_value;
        PORTD = portd_value;
    }
}


/**
 * Main entry point for the code
 */
void main(void) {

    GIE = 1;          // Global interrupt enable
    PEIE = 0;         // Peripheral interrupt disable

    TRISA = 0;  // This is the 8 LSB of the column output
    TRISB = 0;  // This is the 8 bit row output for the LED matrix
    TRISD = 0;  // This is the 8 MSB of the column output
    TRISE = 0;  // Not currently used but set to output 
    
    // TODO: Sort this out for I2C comms
    TRISC = 0;  // In actual fact pins C3 and C4 will be used for I2C comms
    
    // Setup the ports in initial states
    PORTA = 0;
    PORTD = 0;
    PORTB = 0x00; // Port B is inverted, drives PNP transistors
    
    setup_timer();
    
    
    while(1) {
        PORTB = 0x7F; //portb_value;
        //PORTA = 0xF7;
        delay(1000);
        PORTB = 0x80; //portb_value += 1;
        //PORTA = 0x08;
        delay(1000);
        PORTB = 0x7F;
        //PORTA = 0xF7;
        delay(1000);
        PORTB = 0x80;
        //PORTA = 0x08;
        delay(1000);
    }
}
