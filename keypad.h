#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "std_types.h"
#include "Common_macros.h"
#include "Microcontroller.h"

#define N_col 3
#define N_row 4
#define Keypad_port_out_in GPIO_PORTA_DATA_R
#define Keypad_pull_up     GPIO_PORTA_PUR_R 
#define KeyPad_DIR         GPIO_PORTA_DIR_R
#define keypad_Digital_en  GPIO_PORTA_DEN_R
/***  functions proto types *///
uint8 Keypad_getpressed(void);

#endif