#include <xc.h>
#include <stddef.h>
#include "hardware.h"
#include "audio.h"

// Internal only structures that run the Tune or sound
typedef struct
{
    uint16_t position;  // Current position in audio/music array
    uint16_t duration;  // Internal variable to count down until next note played
    uint8_t  state;     // PLAY / PAUSE / STOP
    uint8_t  size;
    uint8_t  mode;
    NOTE    *t;
    NOTE    *org;
}AUDIO_CONTROL_TUNE;

typedef struct
{
    uint16_t position;  // Current position in audio/music array
    uint8_t  state;     // PLAY / PAUSE / STOP
    SOUND    *s;
}AUDIO_CONTROL_SOUND;

// Internal structures used to run the sound
AUDIO_CONTROL_TUNE aTune;
AUDIO_CONTROL_SOUND aSound;

// Initialize audio hardware subsystem and data pointers
void audio_init(void)
{
    // Set up Internal Variables
    aTune.t=NULL;
    aTune.position=0;
    aTune.duration=0;    // Internal counter until next note played
    aTune.state=STOP;
    
    aSound.s=NULL;
    aSound.position=0;
    aSound.state=STOP;
    
    // ************************************************************************
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    
    LATBbits.LATB4 = 0;
    LATBbits.LATB5 = 0;
    // ************************************************************************
    
    // *** Set up I/O pins, CWG and Timers for Tune Playing *******************
    
    // ************************************************************************
    PPS_UNLOCK();  
    // Set up CWG PPS options here
    AUDIO_P_PPS();
    AUDIO_N_PPS();
    AUDIO_P_TRIS=0;
    AUDIO_N_TRIS=0;
    
    PPS_LOCK();
    // ************************************************************************

    
    // *** TMR1 Initialization - Tony *****************************************
    T1CON  = 0x02;          //CKPS 1:1; nT3SYNC synchronize; TMR3ON off; T3RD16 enabled;
    T1GCON = 0x00;          //T3GE disabled; T3GTM disabled; T3GPOL low; T3GGO done; T3GSPM disabled; 
    T1GATE = 0x00;          //GSS T3G;
    T1CLK  = 0x01;          //CS FOSC/4;
    
    TMR1H  = 0x00;          // preload for 2.048ms (488 Hz)
    TMR1L  = 0x00;          
    
    TMR1IF = 0;    // Clearing IF flag
    
    TMR1ON = 1;   // Start the Timer by writing to TMRxON bit
    // ************************************************************************
    
    // *** CCP1 Initialization - Tony *****************************************
    CCP1CON = 0x81;             // MODE Toggle_cleartmr; EN enabled; FMT right_aligned;
    
    CCPR1H = 0x00;              // RH 0;    
    CCPR1L = 0x00;              // RL 0;
    
    CCPTMRS = 0b00000001;       // Selecting Timer 1
    // ************************************************************************
    
    // *** CWG Initialization - Tony ******************************************
    CWG1CON1   = 0x00;          // CWG1POLA non inverted; CWG1POLC non inverted; CWG1POLB non inverted; CWG1POLD non inverted;
    
    CWG1DBR    = 0x00;          // CWG1DBR 0;
    CWG1DBF    = 0x00;          // CWG1DBF 0;
    
    CWG1AS0    = 0x00;          // CWG1SHUTDOWN No Auto-shutdown; CWG1REN disabled; CWG1LSBD inactive; CWG1LSAC inactive; 
    CWG1AS1    = 0x00;          // AS(1/2/3/4/5)E disabled; 
    
    CWG1STR    = 0x00;          // CWG1STR(A/B/C/D) disabled; CWG1OVR(A/B/C/D) low;
    CWG1CLKCON = 0x00;          // CWG1CS FOSC;
    CWG1ISM    = 0x01;          // IS CCP1_OUT;
    CWG1CON0   = 0x84;          // CWG1LD Buffer_not_loaded; CWG1EN enabled; CWG1MODE Half bridge mode;
    // ************************************************************************ 
}

void audio_set_tune(TUNE *t)
{
    aTune.state=STOP;
    aTune.position=0;
    aTune.size=t->size;
    aTune.mode=t->mode;
    aTune.t=t->dat;
    aTune.org=t->dat;
}

void audio_play_tune(void)
{
    aTune.position=0;
    aTune.state=PLAY;
    aTune.duration = 0;
    
}

void audio_pause_tune(uint8_t p)
{
    if(p==PAUSE)
    {
        aTune.state=PAUSE;
    }
    else if(p == PLAY || p == RESUME)
    {
        aTune.state=PLAY;   // PLAY or RESUME continue playing 
    }
}


void audio_stop_tune(void)
{
    aTune.state=STOP;
    aTune.position=0;
}

void audio_set_sound(SOUND *s)
{
    aSound.state=STOP;
    aSound.position=0;
    aSound.s=s;
}

void audio_play_sound(void)
{
    aSound.position=0;
    aSound.state=PLAY;
}

void audio_pause_sound(uint8_t p)
{
    if(p==PAUSE)
    {
        aSound.state=PAUSE;
    }
    else if(p == PLAY || p == RESUME)
    {
        aSound.state=PLAY;   // PLAY or RESUME continue playing 
    }
}

void audio_stop_sound(void)
{
    aSound.state=STOP;
    aSound.position=STOP;
}

// Interrupt handler that runs the audio system
// In Music mode it uses a tick to move to the next note when duration is complete
// and changes the frequency to match the note
// Use the aTune structure to operate.
void audio_interrupt(void)
{
    UINT16_8_CVT temp;
    
    if(aTune.state == PLAY)
    {
        if(aTune.duration == 0)
        {
            if(aTune.position < aTune.size)
            {
                aTune.duration = aTune.t->duration;
                temp.W16 = aTune.t->key;
                CCPR1L = temp.L;
                CCPR1H = temp.H;

                aTune.position++;
                aTune.t++;

            }
            else
            {
                if(aTune.mode == ONETIME)
                {
                    aTune.state = STOP;
                }
                else
                {
                    aTune.position = 0;
                    aTune.t=aTune.org;
                }
            }
        }
        else
        {
            aTune.duration--;
        }
    }
    else
    {
        CCPR1L = 0;
        CCPR1H = 0;
    }
}




