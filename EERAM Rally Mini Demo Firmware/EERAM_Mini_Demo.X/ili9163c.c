
#include <xc.h>
#include <stdint.h>
#include "liteguidrv.h"
#include "hardware.h"
#include "mcc.h"
#include "ili9136c.h"


uint16_t scolor =0;  // selected color
 

void delay_ms(unsigned int tt)
{
    while(tt--)
    { 
        __delay_ms(1);
    }
}
    


//====================================================//

//===============================================================

static  uint16_t pic[10]={0,1,2,3,4,5,6,7,8,9};

//Clear Screen
void cls(uint16_t bColor)
{
    uint16_t i,j;
    LCD_SetPos(0,127,0,159);//128 x 160
    for (i=0;i<160;i++)
	{
	
	   for (j=0;j<128;j++)
	       Write_Data_U16(bColor);
	}
}


//===============================================================
//WRITE COMMAND DATA

void  Write_Cmd_Data (unsigned char x)
{
 
#if (INTERFACE == 8080)
    
    
    RS_LAT=1;	    // DC latch = 1 = Data
 //   CS_LAT=0;
    DATABUS_LAT=x;	
    WR_LAT=0;
    WR_LAT=1;
  //  CS_LAT=1;
    
#elif (INTERFACE == 6800)
    
	RS_LAT=1;	
	CS_LAT=0;
	WR_LAT=0;
	RD_LAT=1;
	DATABUS_LAT=x;	
	RD_LAT=0;
	CS_LAT=1;
#else
    #error INTERFACE TYPE IS NOT DEFINED
#endif

   
}

//==============================================================
//WRITE TWO BYTE
void  Write_Data_U16(uint16_t y)
{
	uint8_t m,n;
	m=(uint8_t)(y>>8);
	n=(uint8_t)y;
	Write_Data(m,n);

}
//=============================================================
//WRITE COMMAND

void Write_Cmd(unsigned char CMD)
{
#if (INTERFACE == 8080)
    
	RS_LAT=0;  // DC latch = 0 = Command
//    CS_LAT=0;
 
	DATABUS_LAT=CMD;	
    WR_LAT=0;
 	WR_LAT=1;
 //   NOP();
//	CS_LAT=1;
 

#elif(INTERFACE==6800)
    
	RS_LAT=0;	
	CS_LAT=0;
	WR_LAT=0;
	RD_LAT=1;
	DATABUS_LAT=CMD;	
	RD_LAT=0;
	CS_LAT=1;
#endif
    
      
}

//===================================================================
//WRITE DATA

void Write_Data(unsigned char DH,unsigned char DL)
{
 #if(INTERFACE==8080)
 	
 
	RS_LAT=1;       // DC = 1 = Data
//	CS_LAT=0;

    
    DATABUS_LAT=DH;
    WR_LAT=0;
    WR_LAT=1;
    
    DATABUS_LAT=DL;
    WR_LAT=0;
    WR_LAT=1;
    
  
//	CS_LAT=1;
    
	
#elif(INTERFACE==6800)
 	{
	RS_LAT=1;	
	CS_LAT=0;
	WR_LAT=0;
	RD_LAT=1;
	DATABUS_LAT=DH;	
	RD_LAT=0;

 	RD_LAT=1;
	DATABUS_LAT=DL;	
	RD_LAT=0;

	CS=1;
#endif
}


void LCD_FULL(unsigned int i)
{//show Box
    uint16_t w,u;
    
    LCD_SetPos(0,127,0,159);//160x128 

    for(w=0;w<128;w++)
    {    
        Write_Data_U16(~i);

    }

  	for(w=0;w<158;w++)		    
    { 
        Write_Data_U16(~i);

        for(u=0;u<126;u++)
        Write_Data_U16(i);

        Write_Data_U16(~i);		
    }

    for(w=0;w<128;w++)
    {    
        Write_Data_U16(~i);

    }	
	
}



//============================================================
//show gray

void DispRGBGray(void)
{  

	uint16_t  A,B,C;
    uint16_t  i,j,k,DH;

     LCD_SetPos(0,127,0,159);//160x128 



	for(k=0;k<40;k++)
	{   
    	A=0;
    	B=0;
    	C=0;
		for(i=0;i<32;i++)
		{    
    		for(j=0;j<4;j++)
    		{
     			DH=(A<<11)+(B<<5)+C;
     			Write_Data_U16(DH);
    		}
    		A=A+1;
   			B=B+2;
    		C=C+1;
  		}

	}


	for(k=0;k<40;k++)
	{   
    	A=0;
    	B=0;
    	C=0;
		for(i=0;i<32;i++)
		{    
    		for(j=0;j<4;j++)
    		{
     			DH=(A<<11)+B+C;
     			Write_Data_U16(DH);
    		}
    		A=A+1;

  		}

	}

	for(k=0;k<40;k++)
	{   
    	A=0;
    	B=0;
    	C=0;
		for(i=0;i<32;i++)
		{    
    		for(j=0;j<4;j++)
    		{
     			DH=A+(B<<5)+C;
     			Write_Data_U16(DH);
    		}
    		B=B+2;

  		}

	}

	for(k=0;k<40;k++)
	{   
    	A=0;
    	B=0;
    	C=0;
		for(i=0;i<32;i++)
		{    
    		for(j=0;j<4;j++)
    		{
     			DH=A+B+C;
     			Write_Data_U16(DH);
    		}
    		C=C+1;

  		}

	}




}

//============================================================
//show picture
void show_picture(void)
{
	uint8_t i,j;
	uint16_t m=0,n=0;
   LCD_SetPos(0,119,0,159);//160x128 
	for(j=0;j<160;j++)
	{
        for(i=0;i<120;i++)
		{
            Write_Data_U16(pic[j*120+i]);
	    }
	}

    return;
}




//=============================================================
//Initial

void lgdrv_init(void)
{	 
    
    // Initialise the I/O to initial states
    CS_LAT=1;
    RS_LAT=1;
    WR_LAT=1; 
    RD_LAT=1; 
    RES_LAT=1;
    DATABUS_LAT=0;

        
    CS_TRIS=0;
    RS_TRIS=0;
    WR_TRIS=0; 
    RD_TRIS=0; 
    RES_TRIS=0;

    DATABUS_TRIS=0;
    
 	delay_ms(5);
    RES_LAT=0;
	delay_ms(50);
	RES_LAT=1;
	delay_ms(150);

  //************* Start Initial Sequence **********//
    
    CS_LAT=0;        // Select teh device (Do not need to release)
    
	Write_Cmd(0x11); //Exit Sleep
	delay_ms(50);

	Write_Cmd(0x26);        //Set Default Gamma
    Write_Cmd_Data(0x04);
    
    Write_Cmd(0xB1);        // Frame Rate Control
    Write_Cmd_Data(0x08);   //10 
    Write_Cmd_Data(0x10);   //08 
    
    Write_Cmd(0xC0);        //Set VRH1[4:0] & VC[2:0] for VCI1 & GVDD
    Write_Cmd_Data(0x0C);
    Write_Cmd_Data(0x05);
    
    Write_Cmd(0xC1);        //Set BT[2:0] for AVDD & VCL & VGH & VGL
    Write_Cmd_Data(0x02);
    
    Write_Cmd(0xC5);        //Set VMH[6:0] & VML[6:0] for VOMH & VCOML
    Write_Cmd_Data(0x4E);
    Write_Cmd_Data(0x30);
    
    Write_Cmd(0xC7);         // VCOM Offset
    Write_Cmd_Data(0xc0);   //offset=0//C0
    
    Write_Cmd(0x3A);  //Set Color Format
    Write_Cmd_Data(0x05);
    
    Write_Cmd(0x2A);  //Set Column Address
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(0x7F);
    
    Write_Cmd(0x2B);  //Set Page Address
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(0x00);
    Write_Cmd_Data(0x9F);
    
 //   Write_Cmd(0xB4);  //frame inversion
//	Write_Cmd_Data(0x07);
    
    Write_Cmd(0x36);  //Set Scanning Direction
    Write_Cmd_Data(0xC0);
    
 //Write_Cmd(0xEC);  //Set pumping clock frequency
 //Write_Cmd_Data(0x0B);
    
    Write_Cmd(0xF2);  //Enable Gamma bit
    Write_Cmd_Data(0x01);

	Write_Cmd(0xE0);      // Positive Gamma correction
    Write_Cmd_Data(0x3F);//p1          // xx VP63[5:0]             //       //
    Write_Cmd_Data(0x31);//p2          // xx VP62[5:0]             //       //
    Write_Cmd_Data(0x2D);//p3         // xx VP61[5:0]             //       //
    Write_Cmd_Data(0x2F);//p4          // xx VP59[5:0]             //       //
    Write_Cmd_Data(0x28);//p5          // xx VP57[5:0]             //       //
    Write_Cmd_Data(0x0D);//p6         // xxx VP50[4:0]  //       //
    Write_Cmd_Data(0x59);//p7          // x VP43[6:0]              //       //
    Write_Cmd_Data(0xA8);//p8          // VP36[3:0] VP27[3:0]        //       //
    Write_Cmd_Data(0x44);//p9          // x VP20[6:0]              //       //
    Write_Cmd_Data(0x18);//p10       // xxx VP13[4:0]  //       //
    Write_Cmd_Data(0x1F);//p11       // xx VP6[5:0]               //       //
    Write_Cmd_Data(0x10);//p12       // xx VP4[5:0]               //       //
    Write_Cmd_Data(0x07);//p13       // xx VP2[5:0]               //       //
    Write_Cmd_Data(0x02);//p14       // xx VP1[5:0]               //       //
    Write_Cmd_Data(0x00);//p15       // xx VP0[5:0]               //       //
    
    Write_Cmd(0xE1);        // Negative Gamma correction
    Write_Cmd_Data(0x00);//p1          // xx VN0[5:0]               //       //
    Write_Cmd_Data(0x0E);//p2         // xx VN1[5:0]               //       //
    Write_Cmd_Data(0x12);//p3          // xx VN2[5:0]               //       //
    Write_Cmd_Data(0x10);//p4          // xx VN4[5:0]              //       //
    Write_Cmd_Data(0x17);//p5          // xx VN6[5:0]               //       //
    Write_Cmd_Data(0x12);//p6          // xxx VN13[4:0] //       //
    Write_Cmd_Data(0x26);//p7          // x VN20[6:0]              //       //
    Write_Cmd_Data(0x57);//p8          // VN36[3:0] VN27[3:0]       //       //  
    Write_Cmd_Data(0x3B);//p9         // x VN43[6:0]              //       //
    Write_Cmd_Data(0x07);//p10       // xxx VN50[4:0] //       //
    Write_Cmd_Data(0x20);//p11       // xx VN57[5:0]            //       //
    Write_Cmd_Data(0x2F);//p12       // xx VN59[5:0]            //       //
    Write_Cmd_Data(0x38);//p13       // xx VN61[5:0]            //       //
    Write_Cmd_Data(0x3D);//p14       // xx VN62[5:0]            //       //       
    Write_Cmd_Data(0x3f);//p15         // xx VN63[5:0]            //       /

	
/*	Write_Cmd(0xE0);
	Write_Cmd_Data(0x36);//p1
	Write_Cmd_Data(0x29);//p2
	Write_Cmd_Data(0x12);//p3
	Write_Cmd_Data(0x22);//p4
	Write_Cmd_Data(0x1C);//p5
	Write_Cmd_Data(0x15);//p6
	Write_Cmd_Data(0x42);//p7
	Write_Cmd_Data(0xB7);//p8
	Write_Cmd_Data(0x2F);//p9
	Write_Cmd_Data(0x13);//p10
	Write_Cmd_Data(0x12);//p11
	Write_Cmd_Data(0x0A);//p12
	Write_Cmd_Data(0x11);//p13
	Write_Cmd_Data(0x0B);//p14
	Write_Cmd_Data(0x06);//p15
	Write_Cmd(0xE1);
	Write_Cmd_Data(0x09);//p1
	Write_Cmd_Data(0x16);//p2
	Write_Cmd_Data(0x2D);//p3
	Write_Cmd_Data(0x0D);//p4
	Write_Cmd_Data(0x13);//p5
	Write_Cmd_Data(0x15);//p6
	Write_Cmd_Data(0x40);//p7
	Write_Cmd_Data(0x48);//p8
	Write_Cmd_Data(0x53);//p9
	Write_Cmd_Data(0x0C);//p10
	Write_Cmd_Data(0x1D);//p11
	Write_Cmd_Data(0x25);//p12
	Write_Cmd_Data(0x2E);//p13
	Write_Cmd_Data(0x34);//p14
	Write_Cmd_Data(0x39);//p15	   */

	Write_Cmd(0x29); // Display On
	Write_Cmd(0x2C); // Memory Write ????

    
    //show_picture();
}
	    


//===============================================================
//????????
void LCD_SetPos(unsigned char x0,unsigned char x1,unsigned int y0,unsigned int y1)
{
    uint8_t YSH,YSL,YEH,YEL;

	YSH=y0>>8;
	YSL=y0;

	YEH=y1>>8;
	YEL=y1;

 	Write_Cmd(0x2A);        //Column Address set
	Write_Cmd_Data (0x00);
	Write_Cmd_Data (x0);
	Write_Cmd_Data (0x00);
	Write_Cmd_Data (x1);
	Write_Cmd(0x2B);        // Page Address Set
	Write_Cmd_Data (YSH);
	Write_Cmd_Data (YSL);
	Write_Cmd_Data (YEH);
	Write_Cmd_Data (YEL);
	Write_Cmd(0x2C);        // Memory Write
    
    //LCD_WriteCMD(GRAMWR);
}
