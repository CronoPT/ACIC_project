/* FILENAME - configs.h */

#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#define UNIT 1000 /* T=1second in specification */
#define PERIOD 20 /* Total units of a full cycle */

#define S_RED 9    /* Pin for red led in south direction */
#define S_YEL 8    /* Pin for yellow led in south direction */
#define S_GRE 7    /* Pin for green led in south direction */
#define S_BUTTON 6 /* Pin for button (car counter) in south direction */

#define W_RED 11   /* Pin for red led in north direction */
#define W_YEL 12   /* Pin for yellow led in north direction */
#define W_GRE 13   /* Pin for green led in north direction */
#define W_BUTTON 10 /* Pin for button (car counter) in north direction */

/* Bits for the Y coordinate */
#define b0 5
#define b1 4
#define b2 3

/* Bits for the X coordinate */
#define a0 A0

#define DETECT_PIN_S A1
#define DETECT_PIN_W A2

/* Bits for the cardinal points */
#define DS 2
#define DW A3

#endif
