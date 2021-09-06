
#ifndef CONFIG_H
#define	CONFIG_H


// PIC16F84A Configuration Bit Settings
// 'C' source line config statements
// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

//create boolean type for use in C
#define  bool int
#define  true 1
#define  false 0

//define função de looping infinito
#define loop() while(1)

#include <xc.h>                 // include for XC8 compiler

#define _XTAL_FREQ 4000000UL    // Crystal frequency

#endif	/* CONFIG_H */

