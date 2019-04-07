/*
	Editor: Earl R. Watkins II Title: ERW_PCA9685.h Date: 04/06/2019

	LED character generator

	Notes:

	Based on: experience

	This example code uses the "beerware" license. Use it, modify it, and/or reference it.
	If you find it useful, buy me an ice cold tasty beverage someday.
*/

#ifndef ERW_LED_Display_h
#define ERW_LED_Display_h

#include <Arduino.h>

#define ASCII_NULL    0x100000
#define ASCII_BS      0x200000
#define ASCII_TAB     0x300000
#define ASCII_LF      0x400000
#define ASCII_VT      0x500000
#define ASCII_CR      0x600000
#define ASCII_ESC     0x700000
#define ASCII_DEL     0x800000

//Include needed libraries with ifndef

class ERW_LED_Display
{
	public: //Can be called upon.

	//Public Functions

		ERW_LED_Display(uint8_t);
		void begin_alphanumeric(void);
		uint32_t ASCII2SEG18(uint8_t ASCII_input);

	//Public Variables

	private:
	//Private Functions



	//Private Variables
	uint8_t ERW_LED_Display_type;
	enum
	{
		Display_7		= 0x01,	/*  7 segment display, for displaying integers */
		Display_9		= 0x02,	/*  9 segment display, has cross lines for less boxy integers */
		Display_14	= 0x10,	/* 14 segment display, for displaying integers and simple characters */
		Display_16	= 0x20,	/* 16 segment display, for displaying integers and complex characters */
		Display_17	= 0x40,	/* 17 segment display, 16 segment display with a single dot */
		Display_18	= 0x80	/* 18 segment display, 16 segment display with a dot in 2 corners */
	};

		uint32_t AN_A1;
		uint32_t AN_A2;
		uint32_t AN_B;
		uint32_t AN_C;
		uint32_t AN_D1;
		uint32_t AN_D2;
		uint32_t AN_E;
		uint32_t AN_F;
		uint32_t AN_G1;
		uint32_t AN_G2;
		uint32_t AN_H;
		uint32_t AN_J;
		uint32_t AN_K;
		uint32_t AN_L;
		uint32_t AN_M;
		uint32_t AN_N;

	struct alphaNumeric16 Segment_mask16;

	/**
 * @brief AlphaNumeric_ASCII[128] is an array that takes in extended ASCII characters.
 * @param index_value takes in an ASCII character.
 * @return output are the bits used to light a 16 digit alphanumeric LED display.
 *                hex 0-3 are for the 16 alphanumeric display pins.
 *                hex 4 is for the 2 dip lights.
 *                hex 5-6 is for Display Control.
 *                hex 7 is reserved.
*/
uint32_t AlphaNumeric_ASCII[128];


};
#endif
