#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#define UNIT 1000 /* T=1second in specification */
#define PERIOD 20 /* Total units of a full cycle */

#define S_RED 4    /* Pin for red led in south direction */
#define S_YEL 3    /* Pin for yellow led in south direction */
#define S_GRE 2    /* Pin for green led in south direction */
#define S_BUTTON 9 /* Pin for button (car counter) in south direction */

#define W_RED 7    /* Pin for red led in north direction */
#define W_YEL 6    /* Pin for yellow led in north direction */
#define W_GRE 5    /* Pin for green led in north direction */
#define W_BUTTON 8 /* Pin for button (car counter) in north direction */

/* Bits for the Y coordinate */
#define b0 12
#define b1 11
#define b2 10

/* Bits for the X coordinate */
#define a0 A0

#define DETECT_PIN_S A1
#define DETECT_PIN_W A2

/* Bits for the cardinal points */
#define DS 13
#define DW A3

#endif
