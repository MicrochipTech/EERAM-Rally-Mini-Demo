
// backlight.c
// Runs the PWM for the backlight
#include <xc.h>
#include <stdint.h>
#include "hardware.h"
#include "backlight.h"

#define PWM_MAX 1023
uint16_t pwm_max;
uint16_t pwm_level;

void backlightInit(void)
{
    pwm_max = PWM_MAX;
    pwm_level=0;
    
    // Set up PWM output Pin
    
//    PPSLOCK=0x55;
//    PPSLOCK=0xAA;
//    PPSLOCKbits.PPSLOCKED=0;
//    
//    RA0PPS = 0b00000111;  // Set PWM3 to RA0
//    
//    PPSLOCK=0x55;
//    PPSLOCK=0xAA;
//    PPSLOCKbits.PPSLOCKED=1;
    
    
    
    
    // Set up PWM 
    BACKLIGHT_TRIS = 1; // Output
    PWM3CON =0;
    T2CLKCON = 0b00000001; // Fosc /4
    CCPTMRS = 0b01010101;  // TMR2 is timebase
    PR2 = 0xFF;
    T2CON = 0b11110000; // TMR2 On 1:128 pre, 1:1 post    
    PWM3DCH = 0x00;
    PWM3DCL = 0x00;
    PWM3CON = 0b10000000;
    
    
    BACKLIGHT_TRIS = 0; // Output
}

void backlightSetMax(uint16_t max)
{
    pwm_max = max;
    if(pwm_max > PWM_MAX)
    {
        pwm_max = PWM_MAX;
    }
    
    if(pwm_level > pwm_max)
    {
        backlightOn();
    }
}

void backlightOn(void)
{
    PWM3DCH = pwm_max >>2;
    PWM3DCL = pwm_max <<6;
    pwm_level = pwm_max;
}

void backlightOff(void)
{
    PWM3DCH = 0;
    PWM3DCL = 0;
    pwm_level = 0;
}


void backlightFadeUp(void)
{
    uint16_t fade;
    for(fade=pwm_level; pwm_level <= pwm_max; pwm_level++)
    {
        PWM3DCH = pwm_level >>2;
        PWM3DCL = pwm_level <<6;
    
        delay_ms(1);
    }
    
}

void backlightFadeDown(void)
{
    uint16_t fade;
    for(fade=pwm_level; pwm_level >0; pwm_level--)
    {
        PWM3DCH = pwm_level >>2;
        PWM3DCL = pwm_level <<6;
    
        delay_ms(1);
    }
    PWM3DCH = 0;
    PWM3DCL = 0;
    pwm_level=0;
}

void backlightFadeTo(uint16_t target)
{
    if(target > pwm_max) target= pwm_max;
    
    if(target > pwm_level)
    {
        for(; pwm_level <= target; pwm_level++)
        {
            PWM3DCH = pwm_level >>2;
            PWM3DCL = pwm_level <<6;
            delay_ms(1);
        }
    }
    else if(target < pwm_level)
    {
        for(; pwm_level > target; pwm_level--)
        {
            PWM3DCH = pwm_level >>2;
            PWM3DCL = pwm_level <<6;
            delay_ms(1);
        }
        pwm_level=target;
        PWM3DCH = pwm_level >>2;
        PWM3DCL = pwm_level <<6;
    }
    
    
}
