/**
 * @file ERW_LED_Display.h
 * @author Earl R. Watkins II
 * @date 04/06/2019
 * @brief Library for turning turning strings into binary led drive as well as special display setups.
*/

#ifndef ERW_LED_Display_h
#define ERW_LED_Display_h

#include <Arduino.h>

#define ASCII_NULL    0x1000000
#define ASCII_BS      0x2000000
#define ASCII_TAB     0x3000000
#define ASCII_LF      0x4000000
#define ASCII_VT      0x5000000
#define ASCII_CR      0x6000000
#define ASCII_ESC     0x7000000
#define ASCII_DEL     0x8000000

#define	Display_7			0x01	/*  7 segment display, for displaying integers */
#define	Display_9			0x02	/*  9 segment display, has cross lines for less boxy integers */
#define	Display_14		0x10	/* 14 segment display, for displaying integers and simple characters */
#define	Display_16		0x20	/* 16 segment display, for displaying integers and complex characters */
#define	Display_17		0x40	/* 17 segment display, 16 segment display with a single dot */
#define	Display_18		0x80	/* 18 segment display, 16 segment display with a dot in 2 corners */

//Include needed libraries with ifndef

class ERW_LED_Display
{
	public: //Can be called upon.

	//Public Functions

		ERW_LED_Display(uint8_t display_type );
		int8_t begin_alphanumeric(void);

		uint32_t ASCII2AN(uint8_t ASCII_input );

		void lineRotation(uint16_t (&quarter_select)[4] );
		void xRotation(uint16_t (&half_select)[2] );
		void handRotation(uint16_t (&eighth_select)[8] );
		void halfRotation(uint16_t (&eighth_select)[8] );
		void quarterRotation(uint16_t (&eighth_select)[8] );
		void eighthRotation(uint16_t (&eighth_select)[8] );

		void fillPositive(uint16_t (&eighth_select)[8] );
		void fillNegative(uint16_t (&eighth_select)[8] );

		void verticalBars(uint16_t (&third_select)[3] );
		void verticalFill(uint16_t (&fifth_select)[5] );
		void horizontalBars(uint16_t (&third_select)[3] );
		void horizontalFill(uint16_t (&fifth_select)[5] );




	//Public Variables

	private:
	//Private Functions



	//Private Variables
	uint8_t LED_Display_type;

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

		uint32_t AN_DP1;
		uint32_t AN_DP2;


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
uint8_t ERW_LED_Display_type;


};
#endif
