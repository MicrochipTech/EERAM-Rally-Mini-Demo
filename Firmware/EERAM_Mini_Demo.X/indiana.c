// indiana.c
// Simple tune to play for the demo

#include "audio.h"

// Simple Demo on how to create a monophonic tune
// Data is: Note, Duration

const NOTE MyIndianaNotes[10]=
{
    {C3, 300},
    {F3, 300},
    {A4, 300},
    {C4, 900},
    {0,600},
    {D4, 300},
    {C4, 300},
    {A4, 300},
    {G3, 600},
    {D3, 600}
};


const TUNE MyIndiana = 
{
    //34, CONTINUOUS, demoTuneNotes
    10, ONETIME, MyIndianaNotes
};




