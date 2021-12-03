#ifndef _FONTS_H
#define _FONTS_H



// FONT - THis is the bit mapped single color font

#define FONT_INTERNAL  0   // Internal FLASH Used - Currently only option supported
#define FONT_EXTERNAL  1   // External FLASH (SPI or I2C bus FLASH)
#define FONT_FILE      2   // SD CARD used

typedef struct
{
    uint8_t w;           // Character width in pixels (Steps of 8 for this library!).
    uint8_t h;           // Character Height in pixels (Steps of 1).
    uint8_t ASCII_Start; // First ASCII code in the font
    uint8_t ASCII_End;   // Last ASCII code in the font
    uint8_t DType;       // INTERNAL / EXTERNAL / FILE  - Currently Internal only
    uint8_t *data;       // pointer to internal data or external or file
}FONT;

// Example Font:

// const uint8_t GiggleData[8*128]=
// {
//    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // NULL Character
//    ......  
//    0x00,0x18,0x08,0x08,0x08,0x08,0x0C,0x00,    // 'l' Character
//    ......
// };
// const FONT Giggles = { 8, 8, 0, 127, FONT_INTERNAL, GiggleData}; // 8x8 font, ASCI characters 0 to 127



//========  Prototypes to fonts used in the system =========
// Please add any additional fonts here.

// Simple 8 x 12 Font - Default font in the library
extern const FONT font8x12;



#endif

