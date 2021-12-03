#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include "litegui.h"



uint16_t lgColor=WHITE;
uint16_t lgBGColor=BLACK;

FONT     *lgFont;     // Pointer to currently Selected font



void lg_init(void)
{
    // Init the Hardware
    lgdrv_init();
    
    // Clear the screen
    cls(BLACK);
    
    // Init the GUI system
    
    lgColor=WHITE;
    

    
}

// rangecheckxywh 
// Internal Function only
// Clips values to the limited range
// return 0 if in range, or bit pattern of which axis clipped
uint8_t rangecheckxywh (uint_lg *x,uint_lg *y,uint_lg *w,uint_lg *h )
{
    uint8_t ret=0;
    
    if(*x > XMAX)
    {
        *x=XMAX;
        ret |=1;
    }
    
    if(*y > YMAX)
    {
        *y=YMAX;
        ret |=2;
    }
    
    if((*x + *w) > XMAX)
    {
        *w=XMAX - *x;
        ret |= 4;
    }
    if((*y + *h) > YMAX)
    {
        *y=YMAX - *x;
        ret |=8;
    }
    
    return ret;
    
}

// rangecheckxy 
// Internal Function only
// Clips values to the limited range
// return 0 if in range, or bit pattern of which axis clipped
uint8_t rangecheckxy(uint_lg *x,uint_lg *y)
{
    uint8_t ret=0;
    if(*x > XMAX) 
    {
        *x=XMAX;
        ret |=1;
    }
    if(*y > YMAX)
    {
        *y=YMAX;
        ret |=2;
    }
    
    return ret;  
}

// Clear the screen
//void cls(uint16_t bColor);

// Set the current color to use
void setcolor(uint16_t c)
{
    lgColor=c;    
}

// Set the current color to use
void setbgcolor(uint16_t c)
{
    lgBGColor=c;    
}


// Plot a pixel
void plot(uint_lg x, uint_lg y)
{
    LCD_SetPos(x,x,y,y);     //160x128 
    Write_Data_U16(lgColor);
}

void swap(uint_lg* a, uint_lg* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapb(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Draw a line
void line(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      plot(y0, x0);
    } else {
      plot(x0, y0);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  } 
}

// Output an 8bit color (indexed) image
void image8(uint_lg x, uint_lg y, uint_lg w, uint_lg h, uint8_t *img)
{
    
}

// Output a 16 bit color image
void image16(uint_lg x, uint_lg y, uint_lg w, uint_lg h, uint16_t *img)
{
    
}

// Select font for text
void setfont(FONT *font)
{
    if(font != NULL)
    {
        lgFont = font;
    }
    
}

// Output text string
void text(uint_lg x, uint_lg y, char *str)
{
    uint8_t w,h,count,bitcount, *ch,d, step;
        
    if(lgFont==NULL) return;    // Exit if we do not have a font selected
    
    w=lgFont->w;
    h=lgFont->h;
    step = (w/8) * h;
    
    while(*str)
    {
        if(*str >= lgFont->ASCII_Start && *str <= lgFont->ASCII_End)
        {
            // Point to the start of the Character
            ch = &lgFont->data[ (*str - lgFont->ASCII_Start) * step ];
        }
        else
        {
            // Make it a space
            ch = &lgFont->data[ ( ' ' - lgFont->ASCII_Start) * step ];
        }
        str++;    
        
      // Write each character
      if(rangecheckxywh(&x,&y,&w,&h)==0)
      {
          // Set the box to draw in
           LCD_SetPos(x,x+w-1,y,y+h-1); 
          
          // Draw the character
           for(count=0;count < step; count++)
           {
               d=*ch;
               for(bitcount=0;bitcount<8;bitcount++)
               {
                   if(d & 0x80) Write_Data_U16(lgColor);
                   // Should skip pixel if possible, or get current background 
                   // color to write
                   else Write_Data_U16(lgBGColor);     
                   d <<=1; 
               }
               ch++;
           }
           
           // Move to next character position
           x+=w;
      }
      else
      {
          // Out of range so do not display any more characters
          break;
      }
    }
}



// Vertical Bar Graph
void vbar(uint_lg x, uint_lg y, uint_lg w, uint_lg h, uint16_t c1, 
          uint16_t c2, uint_lg value)
{
    uint_lg l;
    
    if(rangecheckxywh(&x,&y,&w,&h)) return; // Do not draw if out of range
    
    // Calculate BAR Level
    if(value > h) value=h;
        
    // Draw Level from bottom to top
    
    setcolor(c1);
    for (l=0; l<=value; l++)
    {
      rectangle(x,y+h-l, w,1);
    }
    
    setcolor(c2);
    
    for(; l <=h; l++)
    {
      rectangle(x,y+h-l, w,1);
    }
    
}

// Horizontal Bar Graph
void hbar(uint_lg x, uint_lg y, uint_lg w, uint_lg h, uint16_t c, uint_lg value)
{
    if(rangecheckxywh(&x,&y,&w,&h)) return; // Do not draw if out of range
    if(value > w) value=w;
    LCD_SetPos(x,x+w,y,y+w); 
}

// Rectangle
void rectangle (uint_lg x, uint_lg y, uint_lg w, uint_lg h)
{
    uint16_t count;
    rangecheckxywh(&x,&y,&w,&h);
    
    LCD_SetPos(x,x+w,y,y+h); 
    for(count=w*h; count>0; count --)
    {
       Write_Data_U16(lgColor); 
    }
    
}

// sprite - TEst using Gimp Image Data
void image (uint8_t x, uint8_t y, IMAGE *imagedata)
{
    uint16_t count,rgb, count2=0;
    uint8_t w,h,m,n;
    uint8_t *dat;
       
    w = imagedata->width;
    h = imagedata->height;
    dat = imagedata->pixel_data;    
  
   
  
    rangecheckxywh(&x,&y,&w,&h);
    
    LCD_SetPos(x,x+w-1,y,y+h-1); 

    for(count=w*h; count!=0; count --)
    {
      
       m=*dat;
       dat++;
       n=*dat;
       dat++;
      
       rgb=(uint16_t)n<<8;
       rgb |= m;
        
       if(rgb == BLACK)
       {
           rgb = lgBGColor;
       }
       
       Write_Data_U16(rgb); 
     
    }
}


