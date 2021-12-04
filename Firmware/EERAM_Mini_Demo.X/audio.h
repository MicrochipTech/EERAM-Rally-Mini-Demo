#ifndef _AUDIO_H
#define _AUDIO_H

#include <stdint.h>

#define ONETIME     0       // One time play
#define CONTINUOUS  1       // Continuous loop until Stopped

#define STOP        0       
#define PLAY        1
#define PAUSE       2
#define RESUME      3

typedef union
{
    struct
    {
        uint8_t L;
        uint8_t H;
    };
    uint16_t W16;
    
}UINT16_8_CVT;


typedef struct
{
    uint16_t key;      // frequency load value / Key to play - pointer to the data in the key array
    uint16_t duration; // How long to hold the note for in ms 0 to 65536
}NOTE;


typedef struct
{
    uint8_t size;    // Number of notes in the tune
    uint8_t mode;    // Mode of operation ONETIME or CONTINUOUS
    NOTE *dat;       // Data array of notes to play 
}TUNE;


// Audio limited to 8bit @ 8Khz sample rate
typedef struct 
{
    uint8_t size;    // Size in bytes of sound data 
    uint8_t *dat;    // Pointer to internal data for the audio file
}SOUND;


// Notes C3 to B7 - using A4-440 tuning scales
// Index to the note timer reload array
enum
{
    NONOTE=0,  // Silence
    C3=61069,  // C3        130.81Hz
    Cs2=57554,  // C#3/Db3   138.59Hz
    D3=54422,  // D3        146.83Hz
    Ds3=51282,  // D#3/Eb3   155.56Hz
    E3=48485,  // E3        164.81Hz
    F3=45714,  // F3        174.61Hz
    Fs3=43243,  // F#3/Gb3   185.00Hz
    G3=40816,  // G3        196.00Hz
    Gs3=38462,  // G#3/Ab3   207.65Hz
    A3=36364,  // A3        220.00Hz
    As3=34335,  // A#3/Bb3   233.08Hz
    B3=32389,  // B3        246.94Hz
    C4=30534,  // C4        261.63Hz
    Cs4=28881,  // C#4/Db4   277.18Hz  - Middle C
    D4=27211,  // D4        293.66Hz
    Ds4=25723,  // D#4/Eb4   311.13Hz
    E4=24242,  // E4        329.63Hz
    F4=22923,  // F4        349.23Hz
    Fs4=25723,  // F#4/Eb4   311.13Hz
    G4=20408,  // G4        392.00Hz
    Gs4=19277,  // G#4/Ab4   415.30Hz
    A4=18183,  // A4        440.00Hz
    As4=17167,  // A#4/Bb4   466.16Hz
    B4=16194,  // B4        493.88Hz
    C5=15296,  // C5        523.25Hz
    Cs5=14440,  // C#5/Db5   554.37Hz
    D5=13629,  // D5        587.33Hz
    Ds5=12862,  // D#5/Eb5   622.25Hz
    E5=12140,  // E5        659.25Hz
    F5=11461,  // F5        698.46Hz
    Fs5=10811,  // F#5/Gb5   739.99Hz
    G5=10204,  // G5        783.99Hz
    Gs5=9627,  // G#5/Ab5    830.61Hz
    A5= 9091,  // A5         880.00Hz
    As5= 8584,  // A#5/Bb5    987.77Hz
    B5= 8097,  // B5        1046.50Hz
    C6= 7641,  // C6        1108.73Hz
    Cs6= 7214,  // C#6/Db6
    D6= 6809,  // D6       1174.66Hz
    Ds6= 6426,  // D6#/Eb6  1244.51Hz
    E6= 6065,  // E6       1318.51Hz
    F6= 5727,  // F6       1396.91Hz
    Fs6= 5405,  // F#6/Gb6  1479.98Hz
    G6= 5102,  // G6       1567.98Hz
    Gs6= 4290,  // G#6/Ab6  1864.66Hz
    A6= 4545,  // A6       1760.00Hz
    As6= 4290,  // A#6/Bb6  1864.66Hz
    B6= 4049,  // B6       1975.53Hz
    C7= 3822,  // C7       2093.00Hz
    Cs7= 3608,  // C#7/Db7  2217.46Hz
    D7= 3406,  // D7       2349.32Hz
    Ds7= 3214,  // D#7/Eb7  2489.02Hz
    E7= 3034,  // E7       2637.02Hz
    F7= 2863,  // F7       2793.83Hz
    Fs7= 2703,  // F#7/Gb7  2959.96Hz
    G7= 2551,  // G7       3135.96Hz
    Gs7= 2408,  // G#7/Ab7  3322.44Hz
    A7= 2273,  // A7       3520.00Hz
    B7= 2025   // B7       3951.07Hz
    
}KEY_INDEX;

// Adding the flats
#define Db3 Cs3
#define Eb3 Ds3
#define Gb3 Fs3
#define Ab3 Gs3
#define Bb3 As3

#define Db4 Cs4
#define Eb4 Ds4
#define Gb4 Fs4
#define Ab4 Gs4
#define Bb4 As4

#define Db5 Cs5
#define Eb5 Ds5
#define Gb5 Fs5
#define Ab5 Gs5
#define Bb5 As5

#define Db6 Cs6
#define Eb6 Ds6
#define Gb6 Fs6
#define Ab6 Gs6
#define Bb6 As6

#define Db7 Cs7
#define Eb7 Ds7
#define Gb7 Fs7
#define Ab7 Gs7
#define Bb7 As7


#define AUDIO_P_PPS()       do{RB4PPS = 0x01;}while(0)  // RB4->CWG1A
#define AUDIO_N_PPS()       do{RB5PPS = 0x02;}while(0)  // RB5->CWG1B 

#ifndef AUDIO_P_TRIS
#define AUDIO_P_TRIS        TRISBbits.TRISB4
#define AUDIO_N_TRIS        TRISBbits.TRISB5
#endif

#define AUDIO_OFF()         do{CWG1CON0 = 0x04;}while(0)
#define AUDIO_ON()          do{CWG1CON0 = 0x84;}while(0)


/**
 * Initialize the audio system 
 */
void audio_init(void);

/**
 * Sets the tune to play
 * @param t
 */
void audio_set_tune(TUNE *t);

/**
 * Plays the tune from the beginning
 */
void audio_play_tune(void);

/**
 * Pauses the tune
 * @param p  - 0=Pause 1=Resume  (PAUSE and RESUME are #defined)
 */
void audio_pause_tune(uint8_t p);

/**
 * Stops the tune and resets to the start
 */
void audio_stop_tune(void);

/**
 * Sets the sound to play - RAW 8 or 10 bit file 
 * Stops any current sound first
 * @param s
 */
void audio_set_sound(SOUND *s);

/**
 * Plays the selected sound from the beginning
 */
void audio_play_sound(void);

/**
 * Pauses the sound
 * @param p  - 0=Pause 1=Resume  (PAUSE and RESUME are #defined)
 */
void audio_pause_sound(uint8_t p);

/**
 * Stops the sound playing and resets to the start
 */
void audio_stop_sound(void);

/**
 * Interrupt that runs the audio in the background
 */
void audio_interrupt(void);

#endif

