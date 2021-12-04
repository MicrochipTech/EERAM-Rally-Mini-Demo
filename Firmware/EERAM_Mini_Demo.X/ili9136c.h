
#ifndef _ILI9136c_H
#define _ILI9136c_H

// Hardware settings for the ili9136c driver
// Parallel Port Mode - bit banged parallel port
//=============================================================

#ifndef _XTAL_FREQ
//#define _XTAL_FREQ 32000000
#endif

//Chip select pin (Low enable).
#define CS_PORT PORTAbits.RA4
#define CS_LAT  LATAbits.LATA4  
#define CS_TRIS TRISAbits.TRISA4

//(DC) RS=A0    RS=1  data   RS=0  command             
#define RS_PORT  PORTAbits.RA3 	
#define RS_LAT   LATAbits.LATA3
#define RS_TRIS  TRISAbits.TRISA3

//8080:write  6800: H read  L write
#define WR_PORT  PORTAbits.RA2
#define WR_LAT   LATAbits.LATA2
#define WR_TRIS  TRISAbits.TRISA2

//8080:read  6800: enable 
#define RD_PORT  PORTAbits.RA1  
#define RD_LAT   LATAbits.LATA1
#define RD_TRIS  TRISAbits.TRISA1

//Chip reset pin (Low Active).
#define RES_PORT PORTAbits.RA6 
#define RES_LAT  LATAbits.LATA6
#define RES_TRIS TRISAbits.TRISA6

// DATA Byte Port (Low 8 bits)
#define DATABUS_PORT PORTD    
#define DATABUS_TRIS TRISD
#define DATABUS_LAT  LATD

//8080  OR  6800 
 #define INTERFACE	8080   



void ILI9163_Initial(void);
void Write_Cmd_Data(unsigned char x);
void Write_Cmd(unsigned char CMD);
void Write_Data(unsigned char DH,unsigned char DL);
//void delay_ms(unsigned int tt);
void Write_Data_U16(unsigned int y);
void LCD_SetPos(unsigned char x0,unsigned char x1,unsigned  int y0,unsigned int y1);
void ClearScreen(unsigned int bColor);
void DispRGBGray(void);


#endif