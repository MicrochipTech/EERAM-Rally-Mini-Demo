#ifndef _CONSOLE_H
#define _CONSOLE_H


// ONLY ONE CONSOLE DATA BLOCK PER SYSTEM

#define CONSOLE_ROW_MAX     20
#define CONSOLE_COLUMN_MAX  16


typedef struct
{
    uint_lg x,y;        // Top left corner
    uint8_t col,row;    // Number of text columns and rows
    color_t fg,bg;      // color of the text and background
    uint8_t show;       // Shown or hidden
    FONT *font;         // Font to use 
    uint16_t line;      // Current line in the string 
    //char *str[CONSOLE_ROW_MAX][CONSOLE_COLUMN_MAX];
    // Pointer to the string array
}CONSOLE;

/**
 * Create a new console object
 * @param console
 * @param x   - Top left corner of the console
 * @param y   
 * @param col - Number of columns
 * @param row - Number of rows 
 * @param fg  - Foreground / test color
 * @param bg  - Background color
 * @return 
 */
CONSOLE *console_new(CONSOLE *console, uint_lg x, uint_lg y, uint8_t col,
                     uint8_t row, color_t fg, color_t bg, FONT *font);

/**
 * Clear the consol buffer and display
 * @param console
 * @return 
 */
uint8_t console_clear(CONSOLE *console);

/**
 * Put string to the console \n will move to next line, null terminated strings
 * @param console
 * @param str
 * @return 
 */
uint8_t console_puts(CONSOLE *console, char *str);

/**
 * 
 * @param console
 * @return 
 */
uint8_t console_show(CONSOLE *console);


/**
 * 
 * @param console
 * @return 
 */
uint8_t console_hide(CONSOLE *console);


#endif


