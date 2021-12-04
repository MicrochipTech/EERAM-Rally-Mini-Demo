
#include "litegui.h"
#include <string.h>

#ifndef _CONSOLE_H
#warning "console.c has been included BUT console.h has not been selected in litegui.h"
#else


// Only ONE console array avaliable for the system
// You can have multiple consoles, but they share the same buffer so only fill and display one at a time
char consoleStr[CONSOLE_ROW_MAX][CONSOLE_COLUMN_MAX + 1]; 



uint8_t console_draw(CONSOLE *console);   // PRIVATE: Draws / Updates the console


//======== PUBLIC FUNCTIONS ============

CONSOLE *console_new(CONSOLE *console, uint_lg x, uint_lg y, uint8_t col,
                     uint8_t row, color_t fg, color_t bg, FONT *font)
{
    console->x=x;
    console->y=y;
    
    if(col <= CONSOLE_COLUMN_MAX)
    {
        console->col=col;
    }
    else
    {
        console->col = CONSOLE_COLUMN_MAX;
    }
    if(row <= CONSOLE_ROW_MAX)
    {
        console->row=row;
    }
    else
    {
        console->row=CONSOLE_ROW_MAX;
    }
    
    console->fg=fg;
    console->bg=bg;
    
    console->show=0;
       
    console->line=0;
    
    console->font = font;
            
    console_clear(console);
    
    return console; 
}


uint8_t console_clear(CONSOLE *console)
{
    uint16_t count,a;
   
       
    for(count=0; count < CONSOLE_ROW_MAX ; count++)
    {
        for(a=0;a< CONSOLE_COLUMN_MAX;a++)
        {
            consoleStr[count][a]=' ';  // clear first byte on each row in the buffer
        }
        consoleStr[count][CONSOLE_COLUMN_MAX]=0; // terminate the line
    }
    
    console_draw(console);
    
    return 1;
}


uint8_t console_puts(CONSOLE *console, char *str)
{
    uint8_t a,b, len;
        
    len = strlen(str);
    if(len > console->col) len= console->col; // Shorten string to one line 
    
   
    if( console->line >= console->row)
    {
        // Need to scroll the text in the buffer first
        for(a=0; a < console->row-1; a++)
        {
            for(b=0;b <= console->col;b++)
            {
                consoleStr[a][b] = consoleStr[a+1][b];
            }
        }
        console->line=console->row-1;
    }
    
    // Add new data to buffer
        
    for(a=0;a < console->col;a++)
    {
        if(*str !=0)
        {
            consoleStr[console->line][a]=*str;
            str++;
        }
        else
        {
            consoleStr[console->line][a]=' '; // Pad with spaces
        }
       
    }
    consoleStr[console->line][console->col]=0;  // Terminate the line
    
    console->line++; // Point to next line in buffer (or overflow it))
    
    // Update the console
    console_draw(console);
    
    return 0;
}


uint8_t console_show(CONSOLE *console)
{
    console->show=1;
    
    console_draw(console);
    
    return 0;
}

uint8_t console_hide(CONSOLE *console)
{
    console->show=0;
    
    return 0;
}



//========== PRIVATE FUNCTIONS FOLLOW =============

uint8_t console_draw(CONSOLE *console)
{
    uint8_t a,lines,h;
    uint_lg x,y;
    
    x=console->x;
    y=console->y;
    lines=console->line;
    
    h=console->font->h;
    
    if(console->show==0) return 0;   // Exit if not allowed to draw
    
    
    // Select the font and color
    setfont(console->font);
    setbgcolor(console->bg);
    setcolor(console->fg);
    
    
    // Draw frame in color of the text
    // First version does not have a frame
        
    // Write text - buffer it with spaces to pad the lines
    for(a=0; a < lines;a++)
    {
        text(x,y,consoleStr[a]);
        y+=console->font->h;
        
    }
    
    // Write spaces to the end to clear any old data
    for(;a <console->row;a++)
    {
        text(x,y,consoleStr[a]);
        y+=console->font->h;
    }
            
    return 1;
}







#endif


