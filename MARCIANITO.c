/*
 * File:   MARCIANITO.c
 * Author: HP
 *
 * Created on 22 de diciembre de 2019, 09:03 PM
 */


// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define DO  19
#define DOb_RES 18 
#define RE  17
#define REb_MIs 16
#define MI  15
#define FA 14
#define FAb_SOLs 13
#define SOL  12
#define LA  11
#define SI  10

#define NEGRA 360
#define BLANCA (NEGRA*2)
#define REDONDA (BLANCA*2)
#define CORCHEA (NEGRA/2)
#define SEMICORCHEA (CORCHEA/2)
#define FUSA (SEMICORCHEA/2)
#define SEMIFUSA (FUSA/2)

#define _XTAL_FREQ 20000000

#define Xpos PORTBbits.RB0
#define Xmen PORTBbits.RB1
#define Ymen PORTBbits.RB2
#define Ypos PORTBbits.RB3

void timer_0_init() {
    T0CONbits.TMR0ON = 1; //Activamos el timer0
    T0CONbits.T08BIT = 1; //Ponemos el timer0 a 8 bits
    T0CONbits.T0CS = 0; //La entrada de reloj del cristal 
    T0CONbits.T0SE = 0; //Esto no importa en modo tempo
    T0CONbits.PSA = 1; //Asignamos el prescaler
    T0CONbits.T0PS = 0b000; //Factor de cuenta de 2
}

void notas(int nota, int tiempo) {
    int a, b;
    for (b = 0; b < tiempo; b++) {
        PORTD = 0;
        for (a = 0; a < nota; a++) {
            TMR0L = 244; // tiempo base de 100 useg
SENSA1:
            if (INTCONbits.TMR0IF == 0) goto SENSA1;
            INTCONbits.TMR0IF = 0;
        }
        PORTD = 1;
        for (a = 0; a < nota; a++) {
            TMR0L = 244; // tiempo base de 100 useg
SENSA2:
            if (INTCONbits.TMR0IF == 0)goto SENSA2;
            INTCONbits.TMR0IF = 0;
        }
    }
}

void time_muerto() {
    LATDbits.LATD0 = 0;
    __delay_ms(10);
}

//void main(void) {
//    int a = 0;
//    TRISD = 0x00;
//    timer_0_init();
//    TMR0 = 0;
//    while (1) {
//        notas(DO, NEGRA);
//        time_muerto();
//        notas(RE, CORCHEA);
//        time_muerto();
//        notas(MI, NEGRA);
//        time_muerto();
//        notas(SOL, NEGRA);
//        time_muerto();
//        notas(SOL, NEGRA);
//        time_muerto();
//        notas(FAb_SOLs, CORCHEA);
//        time_muerto();
//        notas(SOL, CORCHEA);
//        time_muerto();
//        notas(FAb_SOLs, CORCHEA);
//        time_muerto();
//        notas(SOL, CORCHEA);
//        time_muerto();
//        notas(MI, REDONDA);
//        time_muerto();
//
//        notas(DO, NEGRA);
//        time_muerto();
//        notas(RE, CORCHEA);
//        time_muerto();
//        notas(MI, NEGRA);
//        time_muerto();
//        notas(SOL, NEGRA);
//        time_muerto();
//        notas(SOL, NEGRA);
//        time_muerto();
//        notas(FAb_SOLs, CORCHEA);
//        time_muerto();
//        notas(SOL, CORCHEA);
//        time_muerto();
//        notas(FAb_SOLs, CORCHEA);
//        time_muerto();
//        notas(SOL, CORCHEA);
//        time_muerto();
//        notas(DO, REDONDA);
//        time_muerto();
//
//        notas(LA, CORCHEA);
//        time_muerto();
//        notas(SOL, CORCHEA);
//        time_muerto();
//        notas(FAb_SOLs, CORCHEA);
//        time_muerto();
//        notas(MI, CORCHEA);
//        time_muerto();
//        notas(RE, CORCHEA);
//        time_muerto();
//        notas(DO, CORCHEA);
//        time_muerto();
//        notas(DO, NEGRA);
//        time_muerto();
//        
//                notas(LA, CORCHEA);
//        time_muerto();
//        notas(SOL, CORCHEA);
//        time_muerto();
//        notas(FAb_SOLs, CORCHEA);
//        time_muerto();
//        notas(MI, CORCHEA);
//        time_muerto();
//        notas(RE,CORCHEA);
//        time_muerto();
//        notas(DO, CORCHEA);
//        time_muerto();
//        notas(DO, NEGRA);
//        time_muerto();
//
//    }
//    return;
//}

void main ()
{
    TRISB = 0X00;
    
    while (1)
    {
        for ( int cuenta = 0 ; cuenta <= 15;  cuenta ++)
        {
            PORTB = cuenta;
            __delay_ms(250);
        }
        return;
    }
    
}