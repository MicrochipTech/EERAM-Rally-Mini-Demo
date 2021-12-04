/* 
 * File:   controls.h
 * Author: C16490
 *
 * Created on November 2, 2016, 11:19 AM
 */

#ifndef CONTROLS_H
#define	CONTROLS_H

#include <xc.h>
#include <stdint.h>
#include "hardware.h"

#ifdef	__cplusplus
extern "C" {
#endif

void debounceButtons(void);

uint8_t checkButtons(void);

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLS_H */

