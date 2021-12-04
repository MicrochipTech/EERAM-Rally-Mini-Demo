
#ifndef _LITEGUI_H
#define _LITEGUI_H

#include <stddef.h>
#include <stdint.h>

#include "ili9136c.h"

//==== DISPLAY LIMITS =====
#define XMAX 128
#define YMAX 160

//==== X,Y, W, H  size to use ======
// 128x160 display is 8 bit
// >256 x 256 would be 16 bit
//#define uint_lg   uint16_t    // For large displays use 16bit x,y,w,h
#define uint_lg    uint8_t      // For small displays use 8 bit x,y,w,h


//=====  Essential Includes ====
#include "color.h"         // Color predefines etc          


//===== OPTIONAL INCLUDES ========
// Select what objects you want, comment out the ones you do not want.

#include "fonts.h"     // Edit this file with prototype for your fonts
#include "images.h"    // Edit this file with prototypes for your images
#include "console.h"   // Simple scrolling text console
//#include "sprites.h"   // Moving animated sprites - semi autonomus movement
//#include "animation.h" // Simple non moving animation when NOT using sprites
//#include "gauge.h"     // Round gauge - a couple of different drawing modes
//#include "tinybar.h"   // Simple 3 or 5 pixel wide bar graphs



//===== GENERIC LITEGUI FUNCTIONS =======


// Init the TFT
void lgdrv_init(void);

// Clear the screen
void cls(uint16_t bColor);

// Set the current color to use
void setcolor(uint16_t c);

// Set the background color to use
void setbgcolor(uint16_t c);

// Plot a pixel
void plot(uint_lg x, uint_lg y);

// Draw a line
void line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);


// Output an 8bit color (indexed) image
void image8(uint_lg x, uint_lg y, uint_lg w, uint_lg h, uint8_t *img);

// Output a 16 bit color image
void image16(uint_lg x, uint_lg y, uint_lg w, uint_lg h, uint16_t *img);

// Select font for text
void setfont(FONT *font);

// Output text string
void text(uint_lg x, uint_lg y, char *str);


// Vertical Bar Graph
void vbar(uint_lg x, uint_lg y, uint_lg w, uint_lg h, uint16_t c1, uint16_t c2, uint_lg value);

// Horizontal Bar Graph
void hbar(uint_lg x, uint_lg y, uint_lg w, uint_lg h, uint16_t c, uint_lg value);

// Rectangle
void rectangle (uint_lg x, uint_lg y, uint_lg w, uint_lg h);

// Sprite
void image (uint8_t x, uint8_t y, IMAGE *imagedata);


extern void lg_init(void);


#endif

