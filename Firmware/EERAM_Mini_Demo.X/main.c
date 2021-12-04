/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.25
        Device            :  PIC18F47K40
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.38
        MPLAB             :  MPLAB X 3.45
 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 * 
 * As of January 14, 2020, this version now applies only to the new Demo Board PCB
 * MCC generated files to support SPI1 and I2C2 master modes were added
 */
#include <xc.h>
#include <stdint.h>
#include "mcc.h"
#include "litegui.h"
#include "hardware.h"
#include "fonts.h"
#include "images.h"
#include "backlight.h"
#include "audio.h"
#include "controls.h"
#include "spi1.h"
//#include "i2c2_driver.h"
//#include "EERAM_driver.h"
#include <math.h>
#include "indiana.h"

// *** DEFINES ****************************************************************
//  Lane positions are along the X axis, left to right

#define LANE1  15
#define LANE2  35
#define LANE3  55
#define LANE4  75
#define LANE5  95
#define LANE6  115
// The car positions are shifted over a bit to center them in the lane lines
#define CAR_AX  17
#define CAR_BX  37
#define CAR_CX  57
#define CAR_DX  77
#define CAR_EX  97

// *** Function Prototypes ****************************************************
void runDisplay(uint8_t buttons);
void state_initial(uint8_t buttons);
void state_initial_hold(uint8_t buttons);
void state_track_draw(uint8_t buttons);
void state_track_run(uint8_t buttons);
void state_replay(uint8_t buttons);
void state_screensaver_start(uint8_t buttons);
void state_screensaver_hold(uint8_t buttons);
void state_screensaver_exit(uint8_t buttons);
void lane(uint8_t xl);
uint8_t collision(void);

void fix_borders(void);
void maneuvere(void);
void initialize_record(void);

void PIM_record(uint16_t address);
void PIM_playback(uint16_t address);
void PIM_Set_Status(void);
uint8_t PIM_error(void);
void PIM_store(void);
void MESSAGE_NewGame(void);
void MESSAGE_Removed(void);
void MESSAGE_Restored(void);
void MESSAGE_Rewind(void);
uint16_t EERAM_FindEnd(void);
void BEEP_low(void);
void BEEP_high(void);
void BEEP_crash(void);
void BEEP_scream(void);
void BEEP_rewind(void);
void BEEP_indiana(void);
void BEEP_note(uint16_t note, uint16_t duration);


// *** Enums ******************************************************************

enum {
    DS_INITIAL,
    DS_INITIAL_HOLD,
    DS_TRACK_DRAW,
    DS_TRACK_RUN,
    DS_CRASH,
    DS_REPLAY,
    DS_ERROR,
    DS_REMOVED,
    DS_REPLACED,
    DS_SCREENSAVER_START,
    DS_SCREENSAVER_HOLD,
    DS_SCREENSAVER_EXIT

} DISPLAY_STATES;

enum {
    COMP_NONE,
    COMP_INITIAL,
    COMP_MOVE
} COMPETITOR_STATES;

// *** Global Variables *******************************************************
uint8_t TickMs = 0;
CONSOLE MainConsole;
//SPIPACKET gestDataIn, gestDataOut;
uint8_t dState = DS_INITIAL, x, y, mx, my;
uint8_t ax, bx, cx, dx, ex;
uint16_t ay, by, cy, dy, ey;

uint8_t i2cbuff[] = {0, 1, 2, 3, 4, 5, 6, 7};
uint8_t overflow = 0xFF;

//extern const unsigned char gauntlet[];

/*const unsigned char gauntlet[64] = {
    0x0, 0xA, 0x14, 0x0, 0x0, 0x0, 0x10, 0x9, 0x0, 0x0, 0x10, 0x3, 0x8, 0x0, 0x0, 0x0, 0x8, 0x0, 0x16, 0x1, 0x0, 0x8, 0x0, 0x0,
    0x13, 0x8, 0x4, 0x0, 0x0, 0x9, 0x0, 0x14, 0x0, 0x2, 0x9, 0x0, 0x0, 0x0, 0x0, 0x0, 0xE, 0x0, 0x0, 0x0, 0xE, 0x10, 0x0, 0x0,
    0x0, 0x0, 0x14, 0x8, 0x0, 0x2, 0x11, 0x0, 0x0, 0x0, 0x2, 0x1C, 0x0, 0x0, 0x0, 0x00

};*/

const unsigned char gauntlet[64] = {
    0x0, 0x1D, 0x2, 0x0, 0x0, 0x0, 0x1D, 0x2, 0x0, 0xC, 0x13, 0x0, 0xC, 0x2, 0x0, 0x0, 0xE, 0x0, 0x0, 0x5, 0x0, 0x12, 0x1, 0x8,
    0x0, 0x14, 0x0, 0x0, 0x0, 0x1C, 0x0, 0x0, 0x8, 0x0, 0x2, 0x0, 0x1, 0x16, 0x8, 0x1, 0x0, 0x0, 0x1D, 0x0, 0x0, 0x13, 0x4, 0x0,
    0x3, 0x10, 0x4, 0xA, 0x0, 0x05, 0x2, 0x0, 0xC, 0x0, 0x3, 0x0, 0x0, 0x10, 0x9, 0x0

};

#define record_length  2046

//unsigned char capture[512][4];

uint16_t fineCount = 0, courseCount = 0;

uint16_t dTimer = 0, record_begin = 0;

uint8_t competitorStateA = COMP_NONE;
uint8_t competitorStateB = COMP_NONE;
uint8_t competitorStateC = COMP_NONE;
uint8_t competitorStateD = COMP_NONE;
uint8_t competitorStateE = COMP_NONE;
// ****************************************************************************


// *** Main *******************************************************************

void main(void) {
    uint8_t testButtons = 1;

    // Workaround for NVMREG bit bug in silicon    
#ifdef _PIC18_H
    NVMCON1bits.NVMREG = 0b10;
#endif

    SYSTEM_Initialize();
    //I2C2_Initialize();
    SPI1_Initialize();

    audio_init();
    //audio_set_tune(&MyIndiana);


    // Turn off boost regulator as not to cause audio noise in the speaker.
    // USB should be checked first(USBDETECT)to see if it is plugged in.
    // If USB is not plugged in, then set USBDETECT as output and set high
    TRISEbits.TRISE1 = 0;
    LATEbits.LATE1 = 1;

    backlightInit();
    lg_init();

    INTCON = 0b11000000; // Enable Global and Peripheral - no priority

    cls(BLACK);
    console_new(&MainConsole, 5, 95, 16, 6, WHITE, GRAY010, &font8x12);

    while (1) {
        if (TickMs > 13) {
            TickMs = 0;
            testButtons = checkButtons();
            runDisplay(testButtons);
        }
    }
}

void runDisplay(uint8_t buttons) {
    switch (dState) {
        default:
            dState = DS_INITIAL;
            break;

        case DS_INITIAL: // Initial start up screen
            state_initial(buttons);
            break;

        case DS_INITIAL_HOLD:
            //initialize_record();
            state_initial_hold(buttons);
            break;

        case DS_TRACK_DRAW: // Draw the current zone
            dTimer = 0;
            record_begin = 0x00;
            overflow = 0x00;
            MESSAGE_NewGame();
            delay_ms(200);
            state_track_draw(buttons);
            dState = DS_TRACK_RUN;
            break;

        case DS_TRACK_RUN: // Update the current zone
            if (buttons & KEY_B) {
                state_track_draw(buttons);
                dState = DS_REPLAY;
                EERAM_FindEnd();
                dTimer = record_begin;
            } else state_track_run(buttons);
            break;

        case DS_CRASH:

            if (buttons & KEY_B) {

                state_track_draw(buttons);
                if (overflow == 0xFF) record_begin = 0x00;
                else EERAM_FindEnd(); //this sets the record_begin
                dTimer = record_begin;
                MESSAGE_Rewind();
                BEEP_rewind();
                //delay_ms(100);
                state_track_draw(buttons);
                dState = DS_REPLAY;

            } else if (buttons & KEY_A) {
                //state_track_draw(buttons);
                dState = DS_INITIAL_HOLD;
            }
            break;

        case DS_ERROR:
            MESSAGE_Removed(); //show message 
            BEEP_low();
            dState = DS_REMOVED;
            break;

        case DS_REMOVED:
            if (PIM_error()) {
                dState = DS_REMOVED;
            } else {

                BEEP_high();
                MESSAGE_Restored(); //show message 
                dState = DS_REPLACED;

                EERAM_FindEnd();
                dTimer = record_begin;
            }
            break;
        case DS_REPLACED:
            if (PIM_error()) {
                MESSAGE_Removed(); //show message 
                BEEP_low();
                dState = DS_REMOVED;
            } else {
                if (buttons & KEY_B) {
                    MESSAGE_Rewind();
                BEEP_rewind();
                    state_track_draw(buttons);
                    EERAM_FindEnd();
                    dTimer = record_begin;

                    //dTimer = record_begin;

                    dState = DS_REPLAY;
                    //SPI1_Open();
                    //while(buttons & KEY_B);
                    delay_ms(100);

                } else if (buttons & KEY_A) {
                    //state_track_draw(buttons);
                    //BEEP_high();
                    dState = DS_INITIAL_HOLD;
                }
            }
            break;
        case DS_REPLAY: // Update the current zone

            if (buttons & KEY_A) {
                //state_track_draw(buttons);
                dState = DS_INITIAL_HOLD;
            } else state_replay(buttons);
            break;

        case DS_SCREENSAVER_START: // Transition to screen saver
            state_screensaver_start(buttons);
            break;

        case DS_SCREENSAVER_HOLD: // Screen Saver Mode
            state_screensaver_hold(buttons);
            break;

        case DS_SCREENSAVER_EXIT: // Exit screen saver
            state_screensaver_exit(buttons);
            break;
    }
}

void state_initial(uint8_t buttons) {
    image(29, 1, &mchp_meatball);
    image(15, 70, &microchip);
    console_show(&MainConsole);

    console_puts(&MainConsole, "     EERAM     ");
    console_puts(&MainConsole, "     RALLY     ");
    console_puts(&MainConsole, " ");
    backlightFadeUp();
    //delay_ms(100);

    console_puts(&MainConsole, "Hit A to RACE  ");
    //SPI1_Open();
    //initialize_record();
    //delay_ms(100);
    //delay_ms(100);
    //delay_ms(100);
    delay_ms(100);
    delay_ms(100);
    delay_ms(100);
    delay_ms(100);
    console_puts(&MainConsole, "Hit B to REVIEW");
    //BEEP_indiana();
    //audio_play_tune();

    dState = DS_INITIAL_HOLD;
}

void state_initial_hold(uint8_t buttons) {
    //if (PIM_error() == 0) {
        if ((buttons & KEY_A)||(buttons & KEY_UP)) {
            audio_stop_tune();
            MESSAGE_NewGame();
            delay_ms(200);
            backlightFadeDown();
            initialize_record();
            cls(BLACK);
            dState = DS_TRACK_DRAW;
            fineCount = 0;
            courseCount = 0;
            dTimer = 0;
            record_begin = 0;
        } else if ((buttons & KEY_B)||(buttons & KEY_DOWN)){
            audio_stop_tune();
            EERAM_FindEnd(); //this sets the record_begin
            MESSAGE_Rewind();
            BEEP_rewind();
            //fineCount = 0;
            //courseCount = 0;
            dTimer = record_begin;
            delay_ms(100);
            dState = DS_REPLAY;
            state_track_draw(buttons);

        }
    //}
}

void state_track_draw(uint8_t buttons) {
    cls(GRAY128);
    backlightFadeUp();
    //dState = DS_TRACK_RUN;
    x = CAR_AX;
    y = 102;

    ax = CAR_AX;
    bx = CAR_BX;
    cx = CAR_CX;
    dx = CAR_DX;
    ex = CAR_EX;

    ay = 0;
    by = 0;
    cy = 0;
    dy = 0;
    ey = 0;

    competitorStateA = COMP_NONE;
    competitorStateB = COMP_NONE;
    competitorStateC = COMP_NONE;
    competitorStateD = COMP_NONE;
    competitorStateE = COMP_NONE;

    dTimer = record_begin;

    //Set the track lanes and sides
    setcolor(GREEN);
    rectangle(0, 130, LANE1, 29);
    rectangle(0, 0, LANE1, 140); //Drawing a solid green box always seems to be incomplete, so splitting it up to two operations
    //rectangle(0, 135, LANE1, 25);

    setcolor(GRAY204);
    rectangle(LANE6, 0, 119, 159);

    lane(LANE1);
    lane(LANE2);
    lane(LANE3);
    lane(LANE4);
    lane(LANE5);
    lane(LANE6);

}

void lane(uint8_t xl) {
    uint8_t y1;
    setcolor(WHITE);

    for (y1 = 0; y1 < 160; y1++) {
        plot(xl, y1);
    }
}

uint8_t collisionA() {
    uint8_t ty;

    ty = ay;

    if (dState != DS_TRACK_RUN) return 0;
    if (competitorStateA != COMP_MOVE) return 0;
    if ((x > (CAR_AX + 10)) || ((x + 10) < CAR_AX)) return 0;

    if (y >= ty) {
        if ((y - ty) < 24) return 1;
    } else if ((ty - y) < 24)return 1;

    return 0;
}

uint8_t collisionB() {
    uint8_t ty;

    ty = by;

    if (dState != DS_TRACK_RUN) return 0;
    if (competitorStateB != COMP_MOVE) return 0;
    if ((x > (CAR_BX + 10)) || ((x + 10) < CAR_BX)) return 0;

    if (y >= ty) {
        if ((y - ty) < 24) return 1;
    } else if ((ty - y) < 24)return 1;

    return 0;
}

uint8_t collisionC() {
    uint8_t ty;

    ty = cy;

    if (dState != DS_TRACK_RUN) return 0;
    if (competitorStateC != COMP_MOVE) return 0;
    if ((x > (CAR_CX + 10)) || ((x + 10) < CAR_CX)) return 0;

    if (y >= ty) {
        if ((y - ty) < 24) return 1;
    } else if ((ty - y) < 24)return 1;

    return 0;
}

uint8_t collisionD() {
    uint8_t ty;

    ty = dy;

    if (dState != DS_TRACK_RUN) return 0;
    if (competitorStateD != COMP_MOVE) return 0;
    if ((x > (CAR_DX + 10)) || ((x + 10) < CAR_DX)) return 0;

    if (y >= ty) {
        if ((y - ty) < 24) return 1;
    } else if ((ty - y) < 24)return 1;

    return 0;
}

uint8_t collisionE() {
    uint8_t ty;

    ty = ey;

    if (dState != DS_TRACK_RUN) return 0;
    if (competitorStateE != COMP_MOVE) return 0;
    if ((x > (CAR_EX + 10)) || ((x + 10) < CAR_EX)) return 0;

    if (y >= ty) {
        if ((y - ty) < 24) return 1;
    } else if ((ty - y) < 24)return 1;

    return 0;
}

void state_track_run(uint8_t buttons) {

    // Move the player as directed
    if (buttons & KEY_LEFT) {
        x--;
        if (x < 12) {
            x = 12;
        }
    }
    if (buttons & KEY_RIGHT) {
        x++;
        if (x > 102) {
            x = 102;
        }
    }

    if (buttons & KEY_UP) {
        y--;
        if (y < 2) y = 2;
    }

    if (buttons & KEY_DOWN) {
        y++;
        if (y > 132) y = 132;
    }
    fix_borders();
    maneuvere();

    PIM_record(dTimer * 4);
    //if(PIM_error) dState = DS_CRASH;

    if (collisionA() || collisionB() || collisionC() || collisionD() || collisionE()) {
        image(x, y, &car16); //redraw the car in case it is being covered
        delay_ms(100); //don't kill the game, just slow for a moment and move on
        dState = DS_CRASH;
        PIM_store();
        //BEEP_crash();
        BEEP_scream();

        //SPI1_Close();
    }
    fineCount++;
    if (fineCount > 48) {
        fineCount = 0;
        courseCount++;
        if (courseCount > 63) courseCount = 0;
    }

    dTimer++;

    if (dTimer > record_length) {
        dTimer = 0;
        overflow = 0xFE;
    }
}

void state_replay(uint8_t buttons) {

    PIM_playback(dTimer * 4); //read the record from the previously set address
    if (PIM_error()) dState = DS_ERROR;

    if ((x > 0xF0) || (x == 0x00)) //indicating end of record
    {
        //console_clear(&MainConsole);
        //console_puts(&MainConsole, "End of Playback");
        delay_ms(100);
        delay_ms(100);
        delay_ms(100);
        delay_ms(100);
        delay_ms(100);
        delay_ms(100);
        delay_ms(100);
        delay_ms(100);
        delay_ms(100);
        delay_ms(100);
        delay_ms(100);
        delay_ms(100);

        if (x == 0xFF)//specifically, if the record was less than full
        {
            record_begin = 0;

        } else {
            EERAM_FindEnd();
        }
        state_track_draw(buttons); //redraw the track
        dTimer = record_begin; //then reset pointer to beginning of record
        dState = DS_REPLAY;
        if (PIM_error()) dState = DS_ERROR;
        return;
    }

    fix_borders();
    maneuvere();
    dTimer++;
    if (dTimer > record_length) {
        dTimer = 0;
        // overflow = 0xFE;
    }
}

void initialize_record() {
    overflow = 0xFF;
    SPI1_Open();
    PIM_Set_Status(); //enable continuous writes and enable auto-store
    //if(PIM_error) dState = DS_CRASH;
    x = 0;
    y = 0;
    fineCount = 0;
    courseCount = 0;
    dTimer = 0;
    record_begin = 0;
    while (dTimer++ < record_length) PIM_record(dTimer * 4);
    if (PIM_error()) dState = DS_ERROR;
    dTimer = 0;
    //x = CAR_AX;
}

void maneuvere() {
    switch (competitorStateA) {
        default:
            break;

        case COMP_NONE:
            competitorStateA = COMP_NONE;
            break;

        case COMP_INITIAL:
            ax = CAR_AX;
            ay = 0;

            competitorStateA = COMP_MOVE;
            break;

        case COMP_MOVE:
            if (ay > 132) {
                setcolor(GRAY128);
                rectangle(ax, ay, 16, 27);
                competitorStateA = COMP_NONE;
            } else {
                ay++;
                image(ax, ay, &blu16);
                competitorStateA = COMP_MOVE;
            }

            break;
    }

    switch (competitorStateB) {
        default:
            break;

        case COMP_NONE:
            competitorStateB = COMP_NONE;
            break;

        case COMP_INITIAL:
            bx = CAR_BX;
            by = 0;

            competitorStateB = COMP_MOVE;
            break;

        case COMP_MOVE:
            if (by > 132) {
                setcolor(GRAY128);
                rectangle(bx, by, 16, 27);
                competitorStateB = COMP_NONE;
            } else {
                by++;
                image(bx, by, &yel16);
                competitorStateB = COMP_MOVE;
            }

            break;
    }

    switch (competitorStateC) {
        default:
            break;

        case COMP_NONE:
            competitorStateC = COMP_NONE;
            break;

        case COMP_INITIAL:
            cx = CAR_CX;
            cy = 0;
            competitorStateC = COMP_MOVE;
            break;

        case COMP_MOVE:
            if (cy > 132) {
                setcolor(GRAY128);
                rectangle(cx, cy, 16, 27);
                competitorStateC = COMP_NONE;
            } else {
                cy++;
                image(cx, cy, &org16);
                competitorStateC = COMP_MOVE;
            }

            break;
    }

    switch (competitorStateD) {
        default:
            break;

        case COMP_NONE:
            competitorStateD = COMP_NONE;
            break;

        case COMP_INITIAL:
            dx = CAR_DX;
            dy = 0;
            competitorStateD = COMP_MOVE;
            break;

        case COMP_MOVE:
            if (dy > 132) {
                setcolor(GRAY128);
                rectangle(dx, dy, 16, 27);
                competitorStateD = COMP_NONE;
            } else {
                dy++;
                image(dx, dy, &vio16);
                competitorStateD = COMP_MOVE;
            }

            break;
    }

    switch (competitorStateE) {
        default:
            break;

        case COMP_NONE:
            competitorStateE = COMP_NONE;
            break;

        case COMP_INITIAL:
            ex = CAR_EX;
            ey = 0;
            competitorStateE = COMP_MOVE;
            break;

        case COMP_MOVE:
            if (ey > 132) {
                setcolor(GRAY128);
                rectangle(ex, ey, 16, 27);
                competitorStateE = COMP_NONE;
            } else {
                ey++;
                image(ex, ey, &grn16);
                competitorStateE = COMP_MOVE;
            }

            break;
    }



    if (PIM_error()) dState = DS_ERROR;


    if (fineCount == 30) {
        if (gauntlet[courseCount] & 0x10) competitorStateA = COMP_INITIAL;
    }
    if (fineCount == 20) {
        if (gauntlet[courseCount] & 0x08) competitorStateB = COMP_INITIAL;
    }
    if (fineCount == 12) {
        if (gauntlet[courseCount] & 0x04) competitorStateC = COMP_INITIAL;
    }
    if (fineCount == 40) {
        if (gauntlet[courseCount] & 0x02) competitorStateD = COMP_INITIAL;
    }
    if (fineCount == 47) {
        if (gauntlet[courseCount] & 0x01) competitorStateE = COMP_INITIAL;
    }
}

void fix_borders() {
    if (x < (LANE1 + 2)) {
        setcolor(GREEN);
        rectangle(0, 0, LANE1, 159);
        lane(LANE1);
    }
    if ((x > (LANE2 - 17))&&(x < (LANE2 + 2))) lane(LANE2);
    if ((x > (LANE3 - 17))&&(x < (LANE3 + 2))) lane(LANE3);
    if ((x > (LANE4 - 17))&&(x < (LANE4 + 2))) lane(LANE4);
    if ((x > (LANE5 - 17))&&(x < (LANE5 + 2))) lane(LANE5);
    if ((x > (LANE6 - 17))&&(x < (LANE6 + 2))) {
        setcolor(GRAY204);
        rectangle(LANE6, 0, 119, 159);
        lane(LANE6);
    }
    image(x, y, &car16);
}

void state_screensaver_start(uint8_t buttons) {
    backlightFadeDown();
    cls(BLACK);
    image(29, 1, &mchp_meatball);
    image(15, 70, &microchip);
    backlightFadeTo(32);
    dState = DS_SCREENSAVER_HOLD;
}

void state_screensaver_hold(uint8_t buttons) {
    dState = DS_SCREENSAVER_EXIT;
}

void PIM_record(uint16_t address) {
    SPI1_Open();
    PIM_CS_LOW;
    SPI1_ExchangeByte(WRTEN);
    PIM_CS_HI;

    PIM_CS_LOW;
    SPI1_ExchangeByte(WRITE);
    SPI1_ExchangeByte(address >> 8);
    SPI1_ExchangeByte(address);

    SPI1_ExchangeByte(x); //capture[dTimer][0] = x;
    SPI1_ExchangeByte(y); //capture[dTimer][1] = y;
    SPI1_ExchangeByte(fineCount); //capture[dTimer][2] = fineCount;
    SPI1_ExchangeByte(courseCount); //capture[dTimer][3] = courseCount;
    SPI1_ExchangeByte(overflow); //mark the end of record
    PIM_CS_HI;

}

void PIM_playback(uint16_t address) {
    SPI1_Open();
    PIM_CS_LOW;
    SPI1_ExchangeByte(READ);
    SPI1_ExchangeByte(address >> 8);
    SPI1_ExchangeByte(address);

    x = SPI1_ExchangeByte(0x00); //capture[dTimer][0] = x;
    y = SPI1_ExchangeByte(0x00); //capture[dTimer][1] = y;
    fineCount = SPI1_ExchangeByte(0x00); //capture[dTimer][2] = fineCount;
    courseCount = SPI1_ExchangeByte(0x00); //capture[dTimer][3] = courseCount;
    PIM_CS_HI;
}

uint16_t EERAM_FindEnd(void) {
    x = 0x00;
    uint16_t counter = 0;
    SPI1_Open();

    PIM_CS_LOW;
    SPI1_ExchangeByte(READ);
    SPI1_ExchangeByte(0x00);
    SPI1_ExchangeByte(0x00);
    while ((x < 0xF0) && (counter < record_length)) {
        x = SPI1_ExchangeByte(0x00); //capture[dTimer][0] = x;
        y = SPI1_ExchangeByte(0x00); //capture[dTimer][1] = y;
        fineCount = SPI1_ExchangeByte(0x00); //capture[dTimer][2] = fineCount;
        courseCount = SPI1_ExchangeByte(0x00); //capture[dTimer][3] = courseCount;
        counter++;
    }
    PIM_CS_HI;

    //if( counter == record_length) initialize_record(); 
    if (x == 0xFF)record_begin = 0x0000;

    else if (counter < record_length - 2) record_begin = counter + 1;
    else record_begin = 0x0000;
    PIM_playback(record_begin); //set the other variables according to beginning
    return counter;

}

void PIM_Set_Status(void) {
    SPI1_Open();
    PIM_CS_LOW;
    SPI1_ExchangeByte(WRTEN);
    PIM_CS_HI;

    PIM_CS_LOW;
    SPI1_ExchangeByte(WRSR);
    SPI1_ExchangeByte(0x20); //set the PRO/ bit to enable continuous writes 
    PIM_CS_HI;
    PIM_CS_HI;

    PIM_store();
}

uint8_t PIM_error(void) {
    uint8_t status_byte;
    SPI1_Open();
    PIM_CS_LOW;
    SPI1_ExchangeByte(RDSR); //read status register
    status_byte = SPI1_ExchangeByte(0x00);
    PIM_CS_HI;
    if (status_byte != 0x20) return 1;
    else return 0;
}

void PIM_store(void) {
    SPI1_Open();
    PIM_CS_LOW;
    SPI1_ExchangeByte(0x08); //software store
    PIM_CS_HI;
    delay_ms(10); //the BUSY bit in the status register will be set for a moment, so set delay and it will clear before proceeding
}

void state_screensaver_exit(uint8_t buttons) {
    backlightFadeDown();
    cls(GRAY128);
    dState = DS_TRACK_DRAW;
}

void MESSAGE_NewGame(void) {
    console_clear(&MainConsole);
    console_puts(&MainConsole, "               ");
    console_puts(&MainConsole, "     NEW       ");
    console_puts(&MainConsole, "     GAME      ");
    console_puts(&MainConsole, "     BEGIN!    ");
    console_puts(&MainConsole, "               ");
    console_puts(&MainConsole, "               ");

    //console_show(&MainConsole);
}
void MESSAGE_Removed(void) {
    console_clear(&MainConsole);
    console_puts(&MainConsole, "               ");
    console_puts(&MainConsole, "    REPLACE    ");
    console_puts(&MainConsole, "     EERAM     ");
    console_puts(&MainConsole, "               ");
    console_puts(&MainConsole, "               ");
    console_puts(&MainConsole, "               ");

    //console_show(&MainConsole);
}

void MESSAGE_Rewind(void) {
    console_clear(&MainConsole);
    console_puts(&MainConsole, "               ");
    console_puts(&MainConsole, "   REWIND<<<   ");
    console_puts(&MainConsole, "   >>>REVIEW   ");
    console_puts(&MainConsole, "               ");
    console_puts(&MainConsole, "               ");
    console_puts(&MainConsole, "               ");

    //console_show(&MainConsole);
}

void MESSAGE_Restored(void) {
    console_clear(&MainConsole);

    console_puts(&MainConsole, "               ");
    console_puts(&MainConsole, "     PRESS     ");
    console_puts(&MainConsole, "     A OR B    ");
    console_puts(&MainConsole, "               ");
    console_puts(&MainConsole, "               ");
    console_puts(&MainConsole, "               ");
    //console_show(&MainConsole);
}

void BEEP_low(void) {
    uint8_t noteL = C3 & 0x00FF;
    uint8_t noteH = C3 >> 8;
    CCPR1L = noteL;
    CCPR1H = noteH;
    delay_ms(100);
    delay_ms(100);
    CCPR1L = 0x00;
    CCPR1H = 0x00;
}

void BEEP_high(void) {
    uint8_t noteL = C5 & 0x00FF;
    uint8_t noteH = C5 >> 8;
    CCPR1L = noteL;
    CCPR1H = noteH;
    delay_ms(100);
    delay_ms(100);
    CCPR1L = 0x00;
    CCPR1H = 0x00;
}

void BEEP_crash(void) {
    uint8_t noteL, noteH, i, j;
    i = j = 0;
    while (i < 64) {
        j = 0;
        while (j < 8) {
            CCPR1H = gauntlet[i] << j;
            delay_ms(1);
            j++;
        }
        i++;
    }

    CCPR1L = 0x00;
    CCPR1H = 0x00;
}

void BEEP_scream(void) {
    uint8_t noteL, noteH, j;
    j = 0;

    j = 50;
    while (j--) {
        CCPR1H = 0x50 - j;
        delay_ms(20);

    }



    CCPR1L = 0x00;
    CCPR1H = 0x00;
}

void BEEP_rewind(void) {
    uint8_t j;

    j = 30;
    while (j-- > 20) {
        CCPR1H = 0xf0 + j;
        delay_ms(j);
        CCPR1H = 0xa0 + j;
        delay_ms(j);
        CCPR1H = 0xc0 + j;
        delay_ms(j);
        CCPR1H = 0xb0 + j;
        delay_ms(j);
    }
    CCPR1L = 0x00;
    CCPR1H = 0x00;
}

void BEEP_note(uint16_t note, uint16_t duration) {
    CCPR1L = note;
    CCPR1H = note >> 8;
    delay_ms(duration);
    CCPR1L = 0x00;
    CCPR1H = 0x00;

}

void BEEP_indiana(void) {
    BEEP_note(C3, 300);
    
    BEEP_note(F3, 300);
    
    BEEP_note(A4, 300);
    
    BEEP_note(C4, 900);
    
    delay_ms(600);
    
    BEEP_note(D4, 300);
    
    BEEP_note(C4, 300);
    
    BEEP_note(A4, 300);
    
    BEEP_note(G3, 600);
    
    BEEP_note(D3, 600);
}

interrupt void MyISR(void) {
    if (TMR3IF) {
        TMR3IF = 0;
        TMR3ON = 0;
        TMR3H = TMR1RELOADH;
        TMR3L = TMR1RELOADL;
        TMR3ON = 1;

        TickMs++;

        //audio_interrupt();
        debounceButtons();
        //buttons = readButtons();
    }
}

