#ifndef _COLOR_H
#define _COLOR_H

// Header file for pre-defined colors, structures and macros

typedef union
{
    uint16_t color;         // 16 bit Color
    struct                  // Breakdown of the RGB565
    {
        unsigned  R : 5;
        unsigned  G : 6;
        unsigned  B : 5;
    };
    

    
}COLOR16;


typedef union 
{
    uint8_t color;
    struct
    {
        unsigned int R : 3;
        unsigned int G : 3;
        unsigned int B : 2;
    };
    
}COLOR8;


#define color_t uint16_t        // Default color that matches the display



// RGB565 Format converter
#define RGB565(r,g,b) (((uint16_t)r & 0x00F8) << 8) | (((uint16_t)g & 0x00FC) << 3) | (((uint16_t)b & 0x00F8) >> 3)  

//==== STANDARD COLORS BELOW =====



// Black White and Gray
#define BLACK           RGB565(0,     0,   0)
#define WHITE           RGB565(255, 255, 255)
#define GRAY242      	RGB565(242, 242, 242)    
#define GRAY229      	RGB565(229, 229, 229)    
#define GRAY224         RGB565(224, 224, 224)
#define GRAY204      	RGB565(204, 204, 204)    
#define GRAY192         RGB565(192, 192, 192)
#define GRAY160         RGB565(160, 160, 160)
#define GRAY128         RGB565(128, 128, 128)
#define GRAY096         RGB565( 96,  96,  96)
#define GRAY032         RGB565( 32,  32,  32)
#define GRAY010         RGB565( 10,  10,  10)


// REGULAR colors
#define RED             RGB565(128,   0,   0)
#define GREEN           RGB565(  0, 128,   0)
#define BLUE            RGB565(  0,   0, 128)
#define CYAN            RGB565(  0, 128, 128)
#define MAGENTA         RGB565(128,   0, 128)
#define YELLOW          RGB565(255, 255, 128)
#define ORANGE         	RGB565(255, 187,  76)

// BRIGHT colors
#define BRIGHTRED       RGB565(255,   0,   0)
#define BRIGHTGREEN     RGB565(  0, 255,   0)
#define BRIGHTBLUE      RGB565(  0,   0, 255)
#define BRIGHTCYAN      RGB565(  0, 255, 255)
#define BRIGHTMAGENTA   RGB565(255,   0, 255)
#define BRIGHTYELLOW    RGB565(255, 255,   0)

// LIGHT colors
#define LIGHTGRAY       RGB565(128, 128, 128)
#define LIGHTRED        RGB565(255, 128, 128)
#define LIGHTGREEN      RGB565(128, 255, 128)
#define LIGHTBLUE       RGB565(128, 128, 255)
#define LIGHTCYAN       RGB565(128, 255, 255)
#define LIGHTMAGENTA    RGB565(255, 128, 255)
#define LIGHTYELLOW     RGB565(255, 255, 150)
#define LIGHTORANGE     RGB565(255, 200,   0)

// Dark Colors
#define DARKGRAY        RGB565( 64,  64,  64)
#define DARKORANGE      RGB565(255, 140,   0)

// Misc Colors (Browns?)
#define GOLD            RGB565(255, 215,   0)
#define BROWN           RGB565(166, 74,   43) 
#define SADDLEBROWN 	RGB565(139,  69,  19) 
#define SIENNA      	RGB565(160,  82,  45)
#define PERU        	RGB565(205, 133,  63)
#define BURLYWOOD  	 	RGB565(222, 184, 135)
#define WHEAT       	RGB565(245, 245, 220)
#define TAN         	RGB565(210, 180, 140)
#define SEA_BLUE        RGB565(0,    67, 171)






#endif
