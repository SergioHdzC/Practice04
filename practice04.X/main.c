/*
 * File:   main.c
 * Author: Atzu2
 *
 * Created on March 29, 2022, 1:32 PM
 */


#include <xc.h>

#include "device_config.h"
//+++++++++++++++++++++++++++++++++++++| DIRECTIVES |+++++++++++++++++++++++++++++++++++++
#define _XTAL_FREQ 1000000
#define ONE_SECOND 1000

//+++++++++++++++++++++++++++++++++++++| DATA TYPES |+++++++++++++++++++++++++++++++++++++
enum por_dir{ output, input };              // output = 0, input = 1
enum por_ACDC { digital, analog };          // digital = 0, analog = 1
enum resistor_state { set_ON, res_ON };     // set_ON = 0, res_ON = 1
enum led_state { led_OFF, led_ON };         // led_OFF = 0, led_ON = 1
enum butto_state { pushed, no_pushed };     // pushed = 0, no_pushed = 1

//+++++++++++++++++++++++++++++++++++++| ISRs |+++++++++++++++++++++++++++++++++++++
// ISR for high priority
void __interrupt ( high_priority ) high_isr( void );
// ISR for low priority
void __interrupt ( low_priority ) low_isr( void ); 

//+++++++++++++++++++++++++++++++++++++| FUNCTION DECLARATIONS |+++++++++++++++++++++++++++++++++++++
void portsInit( void );

//+++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++
void main( void ){
    portsInit();
    while(1){
        if(PORTBbits.RB4 == pushed)         // If button is pushed then
            LATAbits.LATA6 = led_OFF;       // turn off RA4 LED
        else                                // Otherwise
            LATAbits.LATA6 = led_ON;        // turn on RA4 LED
        LATAbits.LATA7 = led_ON;            // Turn on RA4 LED   
        __delay_ms(ONE_SECOND);             // Delay function XC8 compiler
        LATAbits.LATA7 = led_OFF;           // Turn off RA4 LED
        __delay_ms(ONE_SECOND);             // Delay function XC8 compiler
    }
}

//+++++++++++++++++++++++++++++++++++++| FUNCTIONS |+++++++++++++++++++++++++++++++++++++
void portsInit( void ){
    
    ANSELA = digital;                       // Set Port A as digital port
    TRISAbits.TRISA7 = output;              // RA4 as output
    TRISAbits.TRISA6 = output;              // RA7 as output
    ANSELB = digital;                       // Set Port B as digital port
    TRISBbits.TRISB7 = input;               // Set RB4 as input

} 