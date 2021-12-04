#ifndef _BACKLIGHT_H
#define _BACKLIGHT_H

/**
 * Initialise the backlight PWM module
 */
void backlightInit(void);

/**
 * Sets the maximum brightness
 * @param max = new max level
 */
void backlightSetMax(uint16_t max);

/**
 * Turn back light ON instantly
 */
void backlightOn(void);

/**
 * Turn backlight OFF instantly
 */
void backlightOff(void);

/**
 * Fade to Max level  - blocking
 */
void backlightFadeUp(void);

/**
 * Fade to OFF - blocking
 */
void backlightFadeDown(void);

/**
 *  Fade to a level
 * @param target = level to fade to
 */
void backlightFadeTo(uint16_t target);

#endif