 /**
  Hardware specific API Header File
	
  Company:
    Microchip Technology Inc.

  File Name:
    hardware.h

  Summary:
    Header file for initializing the hardware.

  Description:
     This header file provides APIs for initializing the hardware on PICDEM2 .net
     board.

 */

/*

©  [2015] Microchip Technology Inc. and its subsidiaries.  You may use this software 
and any derivatives exclusively with Microchip products. 
  
THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS, 
IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF 
NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS 
INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE 
IN ANY APPLICATION. 

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL 
OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED 
TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY 
OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S 
TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED 
THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS. 

 */

#ifndef HARDWARE_H
#define	HARDWARE_H


#define SCL_LAT          LATBbits.LATB1
#define SCL_TRIS         TRISBbits.TRISB1    //-- The SCL Direction Register Bit
#define SCL_PORT         PORTBbits.RB1 

#define SDA_PORT         PORTBbits.RB2       //-- The SDA output pin
#define SDA_LAT          LATBbits.LATB2
#define SDA_TRIS         TRISBbits.TRISB2    //-- The SDA Direction Register Bit

//#define GEST_RESET_LAT   LATCbits.LATC0
//#define GEST_RESET_TRIS  TRISCbits.TRISC0

//#define GEST_EIO_TRIS    TRISCbits.TRISC2
//#define GEST_EIO_LAT     LATCbits.LATC2
//#define GEST_EIO_PORT    PORTCbits.RC2

#define LED_TRIS         TRISEbits.TRISE2
#define LED_ON()         do{LATEbits.LATE2=1;}while(0)
#define LED_OFF()        do{LATEbits.LATE2=0;}while(0)
#define LED_TOGGLE()     do{LATEbits.LATE2^=1;}while(0)

#define  BACKLIGHT_TRIS   TRISAbits.TRISA0
#define  BACKLIGHT_ON()   do{LATAbits.LATA0=1;}while(0)
#define  BACKLIGHT_OFF()  do{LATAbits.LATA0=0;}while(0)

// SPI Port I/O pins and CS interrupt registers
#define  SPI_MOSI_TRIS    TRISCbits.TRISC4       
#define  SPI_MISO_TRIS    TRISCbits.TRISC5
#define  SPI_SCK_TRIS     TRISBbits.TRISB0

#define  SPI_MOSI_LAT    LATCbits.LATC4       
#define  SPI_MISO_LAT    LATCbits.LATC5
#define  SPI_SCK_LAT     LATBbits.LATB0

//#define  SPI_MOSI_PPS()   do{SSP1DATPPS = 0b00010100;}while(0)  // RC4 = MOSI
//#define  SPI_MISO_PPS()   do{RC5PPS = 0x10;}while(0) //0b00010101;}while(0)  // RC5 = MISO
//#define  SPI_CLK_PPS()    do{SSP1CLKPPS = 0b00001000;}while(0)  // RB0 = SCK

#define  SPI_MOSI_PPS()   do{RC4PPS = 0x10;}while(0) //0b00010000;}while(0)  // RC4 = MOSI this works
#define  SPI_MISO_PPS()   do{SSP1DATPPS = 0x15;}while(0) //0b00010101;}while(0)  //  RC5 = MISO
#define  SPI_CLK_PPS()    do{RB0PPS = 0x0F;}while(0) //0b00001111;}while(0)  // RB0 = SCK

#define  CLIK_CS_TRIS      TRISCbits.TRISC6 // CS TRIS 
#define  CLIK_CS_PORT      PORTCbits.RC6    // CS PORT 
#define  CLIK_CS_LAT       LATCbits.LATC6
#define  CLIK_CS_LOW       do{LATCbits.LATC6 = 0;}while(0)
#define  CLIK_CS_HI        do{LATCbits.LATC6 = 1;}while(0)

#define  PIM_CS_TRIS      TRISAbits.TRISA7 // CS TRIS 
#define  PIM_CS_PORT      PORTAbits.RA7    // CS PORT 
#define  PIM_CS_LAT       LATAbits.LATA7
#define  PIM_CS_LOW       do{LATAbits.LATA7 = 0;}while(0)
#define  PIM_CS_HI        do{LATAbits.LATA7 = 1;}while(0)

// MOSI pin to SPI Memory devices plugged in
#define SPI_DATAOUT_PORT  PORTCbits.RC4
#define SPI_DATAOUT_TRIS  TRISCbits.TRISC4
#define SPI_DATAOUT_LAT   LATCbits.LATC4

// AUDIO Hardware selection
#define AUDIO_P_TRIS      TRISB4     // Speaker Positive output
#define AUDIO_N_TRIS      TRISB5     // Speaker Negative output
#define AUDIO_P_LAT       LATB4
#define AUDIO_N_LAT       LATB5

#define AUDIO_TMR         TMR3    // Use Timer 3 for Audio Tick (1KHz for tune, 8Khz for sound )
#define AUDIO_FREQ_TMR    TMR5    // Use timer 5 for Frequency Generator
#define AUDIO_PWM         PWM3    // Use PWM3 for sound generation

// DPad - Directional Control Pad (buttons) - Tony ****************************
#define UP_TRIS           TRISCbits.TRISC0
#define UP_LAT            LATCbits.LATC0
#define UP_PORT           PORTCbits.RC0

#define DOWN_TRIS         TRISCbits.TRISC1
#define DOWN_LAT          LATCbits.LATC1
#define DOWN_PORT         PORTCbits.RC1

#define LEFT_TRIS         TRISCbits.TRISC2
#define LEFT_LAT          LATCbits.LATC2
#define LEFT_PORT         PORTCbits.RC2

#define RIGHT_TRIS        TRISCbits.TRISC3
#define RIGHT_LAT         LATCbits.LATC3
#define RIGHT_PORT        PORTCbits.RC3

#define KEY_UP            0b00000100
#define KEY_DOWN          0b00000010
#define KEY_LEFT          0b00001000
#define KEY_RIGHT         0b00000001
#define ALL_KEY_MASK      0b00001111


// ****************************************************************************

// Action Buttons - Tony ******************************************************
#define A_TRIS            TRISAbits.TRISA5
#define A_LAT             LATAbits.LATA5
#define A_PORT            PORTAbits.RA5
// KEY B is on Pin 17
#define B_TRIS            TRISBbits.TRISB7
#define B_LAT             LATBbits.LATB7
#define B_PORT            PORTBbits.RB7

#define KEY_A             0b00010000
#define KEY_B             0b00100000

// ****************************************************************************


// PPS Lock and Unlock in ASM as compiler messes it up in C
#define PPS_UNLOCK()   asm("BANKSEL PPSLOCK"); \
                       asm("MOVLW 0x55"); \
                       asm("MOVWF PPSLOCK");\
                       asm("MOVLW 0xAA"); \
                       asm("MOVWF PPSLOCK");\
                       asm("BCF PPSLOCK,0");



#define PPS_LOCK()     asm("BANKSEL PPSLOCK"); \
                       asm("MOVLW 0x55"); \
                       asm("MOVWF PPSLOCK");\
                       asm("MOVLW 0xAA"); \
                       asm("MOVWF PPSLOCK");\
                       asm("BSF PPSLOCK,0");



// PWM
#define PWM_PPS()       do{RA0PPS = 0b00000111;}while(0)   // Set PWM3 to RA0

void delay_ms(unsigned int tt);

#endif	/* HARDWARE_H */

