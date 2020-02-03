/*
 * File:   main.c
 * Author: Luis Gómez
 *
 * Created on 26 de enero de 2020, 1:16
 */

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT       // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <pic16f887.h>
#define _XTAL_FREQ 4000000 //Libreria de Delay
#include <language_support.h>

//Variables 
unsigned int contador = 0;
unsigned int contador2 = 0;
unsigned int start = 0;

//****************************************************************
//              Prototipos de funciones
//****************************************************************
void CONFIG_IO(void);
void oscilador(void);

void main(void) {
    CONFIG_IO(); //Configuración de los puertos de entrada y salida
    oscilador();  //Configuración oscilador interno 


    while (1) { //LOOP

        if (PORTAbits.RA0 == 1) { //Configuración del boton de inicio
            PORTA = 0;
            PORTD = 0x4F;         //Se despliega cada 200ms el semaforo y el display
            PORTE = 1;
            __delay_ms(200);
            PORTD = 0x5B;
            PORTE = 2;
            __delay_ms(200);
            PORTD = 0x06;
            PORTE = 4;
            __delay_ms(200);
            PORTD = 0x3F;
            PORTE = 0;
            __delay_ms(200);
            start = 1;  //La variable de inicio es activada

        }


        if (PORTAbits.RA1 == 1 && start == 1) { //Configuracion para el jugador 1
            __delay_ms(200);
            contador++; //incrementa cada vez que start es 1 y se presiona el boton del jugador 1
            if (contador == 1) { //condicion de incremento y la funcion es desplegar un contador de decadas de 8 bits
                PORTB = 1;
                PORTAbits.RA3 = 0;
                PORTD = 0;
                PORTE = 0;
            } else if (contador == 2) {
                PORTB = 2;
            } else if (contador == 3) {
                PORTB = 4;
            } else if (contador == 4) {
                PORTB = 8;
            } else if (contador == 5) {
                PORTB = 16;
            } else if (contador == 6) {
                PORTB = 32;
            } else if (contador == 7) {
                PORTB = 64;
            } else if (contador == 8) {
                PORTB = 128;
            } else if (contador == 9) {
                PORTB = 0;
                PORTC = 0;
                contador = 0; //Esta condicion despliega el ganador y se limpian amabas variables para reiniciar el juego pulsando RA1
                contador2 = 0;
                start = 0;
                PORTD = 0x06;
                PORTAbits.RA3 = 1;
            }
        }


        if (PORTAbits.RA2 == 1 && start == 1) {// Configuración del boton del jugador 2
            __delay_ms(200);
            contador2++; //incremento de la 2da variable
            if (contador2 == 1) { //condicion de incremento y la funcion es desplegar un contador de decadas de 8 bits
                PORTC = 1;
                PORTAbits.RA4 = 0;
                PORTD = 0;
                PORTE = 0;
            } else if (contador2 == 2) {
                PORTC = 2;
            } else if (contador2 == 3) {
                PORTC = 4;
            } else if (contador2 == 4) {
                PORTC = 8;
            } else if (contador2 == 5) {
                PORTC = 16;
            } else if (contador2 == 6) {
                PORTC = 32;
            } else if (contador2 == 7) {
                PORTC = 64;
            } else if (contador2 == 8) {
                PORTC = 128;
            } else if (contador2 == 9) {
                PORTC = 0;
                PORTB = 0;
                contador2 = 0;
                contador = 0;
                start = 0; //Esta condicion despliega el ganador y se limpian amabas variables para reiniciar el juego pulsando RA1
                PORTD = 0x5B;
                PORTAbits.RA4 = 1;
            }
        }
    }

    return;

}
//****************************************************************
//         Funcion de inicializacion de puertos
//****************************************************************

void CONFIG_IO(void) { //Configuracion de puertos 
    TRISA = 0b00000111;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;

    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    ANSELH = 0;
    ANSEL = 0;
}

void oscilador(void) { //Configuracion para un oscilador de 4MHz

    OSCCON = 0b11000001;

}


