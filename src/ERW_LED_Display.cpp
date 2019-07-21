/**
 * @file ERW_LED_Display.cpp
 * @author Earl R. Watkins II
 * @date 04/06/2019
 * @brief Library for turning turning strings into binary led drive as well as special display setups.
*/

#include "ERW_LED_Display.h"

/**
 * @brief ERW_LED_Display Contructor
 */
ERW_LED_Display::ERW_LED_Display(uint8_t display_type)
{
  ERW_LED_Display_type = display_type;
  if ( ERW_LED_Display_type & Display_18 )
  {
    AN_G1  = 0x0080;
    AN_E   = 0x0040;
    AN_D1  = 0x0020;
    AN_N   = 0x0010;
    AN_M   = 0x0008;
    AN_D2  = 0x0004;
    AN_L   = 0x0002;
    AN_C   = 0x0001;

    AN_G2  = 0x8000;
    AN_B   = 0x4000;
    AN_A2  = 0x2000;
    AN_K   = 0x1000;
    AN_J   = 0x0800;
    AN_A1  = 0x0400;
    AN_H   = 0x0200;
    AN_F   = 0x0100;

    AN_DP1 = 0x10000;
    AN_DP2 = 0x20000;
  }
}

/**
 * ERW_LED_Display constructor
 */
int8_t ERW_LED_Display::begin_alphanumeric(void)
{
  uint8_t returnVar = 0;
  if( ERW_LED_Display_type & 0x0F )
  {
    returnVar = -1;
  }
  AlphaNumeric_ASCII[32] = 0x00000000; /* space */
  AlphaNumeric_ASCII[33] = AN_B | AN_C | AN_DP1; /* ! */
  AlphaNumeric_ASCII[34] = AN_B | AN_F; /* " */
  AlphaNumeric_ASCII[35] = AN_D1 | AN_D2 | AN_E | AN_F | AN_G1 | AN_G2 | AN_J | AN_M; /* # */
  AlphaNumeric_ASCII[36] = AN_A1 | AN_A2 | AN_C | AN_D1 | AN_D2 | AN_F | AN_G1 | AN_G2 | AN_J | AN_M; /* $ */
  AlphaNumeric_ASCII[37] = AN_A1 | AN_C | AN_D2 | AN_F | AN_G1 | AN_G2 | AN_J | AN_K | AN_M | AN_N; /* % */
  AlphaNumeric_ASCII[38] = AN_A1 | AN_D1 | AN_D2 | AN_E | AN_F | AN_G1 | AN_H | AN_K | AN_L; /* & */
  AlphaNumeric_ASCII[39] = AN_B ; /* ' */
  AlphaNumeric_ASCII[40] = AN_K | AN_L; /* ( */
  AlphaNumeric_ASCII[41] = AN_H | AN_N; /* ) */
  AlphaNumeric_ASCII[42] = AN_G1 | AN_G2 | AN_H | AN_J | AN_K | AN_N | AN_M | AN_L; /* * */
  AlphaNumeric_ASCII[43] = AN_G1 | AN_G2 | AN_J | AN_M; /* + */
  AlphaNumeric_ASCII[44] = AN_D2 | AN_DP1; /* , */
  AlphaNumeric_ASCII[45] = AN_G1 | AN_G2; /* - */
  AlphaNumeric_ASCII[46] = AN_DP1; /* . */
  AlphaNumeric_ASCII[47] = AN_K | AN_N; /* / */
  AlphaNumeric_ASCII[48] = AN_A1 | AN_A2 | AN_B | AN_C | AN_D1 | AN_D2 | AN_E | AN_F | AN_K | AN_N; /* 0 */
  AlphaNumeric_ASCII[49] = AN_B | AN_C; /* 1 */
  AlphaNumeric_ASCII[50] = AN_A1 | AN_A2 | AN_B | AN_D1 | AN_D2 | AN_E | AN_G1 | AN_G2; /* 2 */
  AlphaNumeric_ASCII[51] = AN_A1 | AN_A2 | AN_B | AN_C | AN_D1 | AN_D2 | AN_G1 | AN_G2; /* 3 */
  AlphaNumeric_ASCII[52] = AN_B | AN_C | AN_F | AN_G1 | AN_G2; /* 4 */
  AlphaNumeric_ASCII[53] = AN_A1 | AN_A2 | AN_C | AN_D1 | AN_D2 | AN_F | AN_G1 | AN_G2; /* 5 */
  AlphaNumeric_ASCII[54] = AN_A1 | AN_A2 | AN_C | AN_D1 | AN_D2 | AN_E | AN_F | AN_G1 | AN_G2; /* 6 */
  AlphaNumeric_ASCII[55] = AN_A1 | AN_A2 | AN_B | AN_C; /* 7 */
  AlphaNumeric_ASCII[56] = AN_A1 | AN_A2 | AN_B | AN_C | AN_D1 | AN_D2 | AN_E | AN_F | AN_G1 | AN_G2; /* 8 */
  AlphaNumeric_ASCII[57] = AN_A1 | AN_A2 | AN_B | AN_C | AN_F | AN_G1 | AN_G2; /* 9 */
  AlphaNumeric_ASCII[58] = AN_D1 | AN_G1; /* : */
  AlphaNumeric_ASCII[59] = AN_A1 | AN_N; /* ; */
  AlphaNumeric_ASCII[60] = AN_K | AN_L; /* < */
  AlphaNumeric_ASCII[61] = AN_D1 | AN_D2 | AN_G1 | AN_G2; /* = */
  AlphaNumeric_ASCII[62] = AN_H | AN_N; /* > */
  AlphaNumeric_ASCII[63] = AN_A2 | AN_B | AN_G2 | AN_M | AN_DP1; /* ? */
  AlphaNumeric_ASCII[64] = AN_A1 | AN_A2 | AN_B | AN_C | AN_D1 | AN_D2 | AN_E | AN_M; /* @ */
  AlphaNumeric_ASCII[65] = AN_A1 | AN_A2 | AN_B | AN_C | AN_E | AN_F | AN_G1 | AN_G2; /* A */
  AlphaNumeric_ASCII[66] = AN_A1 | AN_A2 | AN_B | AN_C | AN_D1 | AN_D2 | AN_G2 | AN_J | AN_M; /* B */
  AlphaNumeric_ASCII[67] = AN_A1 | AN_A2 | AN_D1 | AN_D2 | AN_E | AN_F; /* C */
  AlphaNumeric_ASCII[68] = AN_A1 | AN_A2 | AN_B | AN_C | AN_D1 | AN_D2 | AN_J | AN_M; /* D */
  AlphaNumeric_ASCII[69] = AN_A1 | AN_A2 | AN_D1 | AN_D2 | AN_E | AN_F | AN_G1; /* E */
  AlphaNumeric_ASCII[70] = AN_A1 | AN_A2 | AN_E | AN_F | AN_G1; /* F */
  AlphaNumeric_ASCII[71] = AN_A1 | AN_A2 | AN_C | AN_D1 | AN_D2 | AN_E | AN_F | AN_G2; /* G */
  AlphaNumeric_ASCII[72] = AN_B | AN_C | AN_E | AN_F | AN_G1 | AN_G2; /* H */
  AlphaNumeric_ASCII[73] = AN_A1 | AN_A2 | AN_D1 | AN_D2 | AN_J | AN_M; /* I */
  AlphaNumeric_ASCII[74] = AN_B | AN_C | AN_D1 | AN_D2 | AN_E; /* J */
  AlphaNumeric_ASCII[75] = AN_E | AN_F | AN_G1 | AN_K | AN_L; /* K */
  AlphaNumeric_ASCII[76] = AN_D1 | AN_D2 | AN_E | AN_F; /* L */
  AlphaNumeric_ASCII[77] = AN_B | AN_C | AN_E | AN_F | AN_H | AN_K; /* M */
  AlphaNumeric_ASCII[78] = AN_B | AN_C | AN_E | AN_F | AN_H | AN_L; /* N */
  AlphaNumeric_ASCII[79] = AN_A1 | AN_A2 | AN_B | AN_C | AN_D1 | AN_D2 | AN_E | AN_F; /* O*/
  AlphaNumeric_ASCII[80] = AN_A1 | AN_A2 | AN_B | AN_E | AN_F | AN_G1 | AN_G2; /* P */
  AlphaNumeric_ASCII[81] = AN_A1 | AN_A2 | AN_B | AN_C | AN_D1 | AN_D2 | AN_E | AN_F | AN_L; /* Q */
  AlphaNumeric_ASCII[82] = AN_A1 | AN_A2 | AN_B | AN_E | AN_F | AN_G1 | AN_G2 | AN_L; /* R */
  AlphaNumeric_ASCII[83] = AN_A1 | AN_A2 | AN_C | AN_D1 | AN_D2 | AN_F | AN_G1 | AN_G2; /* S */
  AlphaNumeric_ASCII[84] = AN_A1 | AN_A2 | AN_J | AN_M; /* T */
  AlphaNumeric_ASCII[85] = AN_B | AN_C | AN_D1 | AN_D2 | AN_E | AN_F; /* U */
  AlphaNumeric_ASCII[86] = AN_E | AN_F | AN_K | AN_N; /* V */
  AlphaNumeric_ASCII[87] = AN_B | AN_C | AN_E | AN_F | AN_N | AN_L; /* W */
  AlphaNumeric_ASCII[88] = AN_H | AN_K | AN_N | AN_L; /* X */
  AlphaNumeric_ASCII[89] = AN_H | AN_K | AN_M; /* Y */
  AlphaNumeric_ASCII[90] = AN_A1 | AN_A2 | AN_D1 | AN_D2 | AN_K | AN_N; /* Z */
  AlphaNumeric_ASCII[91] = AN_A2 | AN_D2 | AN_J | AN_M ; /* [ */
  AlphaNumeric_ASCII[92] = AN_H | AN_L; /* \ */
  AlphaNumeric_ASCII[93] = AN_A1 | AN_D1 | AN_J | AN_M; /* ] */
  AlphaNumeric_ASCII[94] = AN_N | AN_L; /* ^ */
  AlphaNumeric_ASCII[95] = AN_D1 | AN_D2; /* _ */
  AlphaNumeric_ASCII[96] = AN_H; /* ` */
  AlphaNumeric_ASCII[97] = AN_D1 | AN_D2 | AN_E | AN_G1 | AN_M; /* a */
  AlphaNumeric_ASCII[98] = AN_D1| AN_E | AN_F | AN_G1 | AN_M; /* b */
  AlphaNumeric_ASCII[99] = AN_D1 | AN_E | AN_G1; /* c */
  AlphaNumeric_ASCII[100] = AN_D1 | AN_E | AN_G1 | AN_J | AN_M; /* d */
  AlphaNumeric_ASCII[101] = AN_D1 | /* AN_D2 | */AN_E | AN_G1 | AN_N; /* e */
  AlphaNumeric_ASCII[102] = AN_A2 | AN_G1 | AN_G2 | AN_J | AN_M; /* f */
  AlphaNumeric_ASCII[103] = AN_A1 | AN_D1 | AN_F | AN_G1 | AN_J | AN_M; /* g */
  AlphaNumeric_ASCII[104] = AN_E | AN_F | AN_G1 | AN_M; /* h */
  AlphaNumeric_ASCII[105] = AN_A1 | AN_D1 | AN_D2 | AN_G1 | AN_M; /* i */
  AlphaNumeric_ASCII[106] = AN_D1 | AN_E | AN_J | AN_M; /* j */
  AlphaNumeric_ASCII[107] = AN_G2 | AN_J | AN_L | AN_M; /* k */
  AlphaNumeric_ASCII[108] = AN_A1 | AN_D2 | AN_J | AN_M; /* l */
  AlphaNumeric_ASCII[109] = AN_C | AN_E | AN_G1 | AN_G2 | AN_M; /* m */
  AlphaNumeric_ASCII[110] = AN_E | AN_G1 | AN_M; /* n */
  AlphaNumeric_ASCII[111] = AN_D1 | AN_E | AN_G1 | AN_M; /* o */
  AlphaNumeric_ASCII[112] = AN_A1 | AN_E | AN_F | AN_G1 | AN_J; /* p */
  AlphaNumeric_ASCII[113] = AN_A1 | AN_D2 | AN_F | AN_G1 | AN_J | AN_M; /* q */
  AlphaNumeric_ASCII[114] = AN_E | AN_G1; /* r */
  AlphaNumeric_ASCII[115] = AN_D2 | AN_G2 | AN_L; /* s */
  AlphaNumeric_ASCII[116] = AN_D2 | AN_G1 | AN_G2 | AN_J | AN_M; /* t */
  AlphaNumeric_ASCII[117] = AN_D1 | AN_E | AN_M; /* u */
  AlphaNumeric_ASCII[118] = AN_E | AN_N; /* v */
  AlphaNumeric_ASCII[119] = AN_C | AN_E | AN_N | AN_L; /* w */
  AlphaNumeric_ASCII[120] = AN_H | AN_K | AN_N | AN_L; /* x */
  AlphaNumeric_ASCII[121] = AN_C | AN_D1 | AN_D2 | AN_L; /* y */
  AlphaNumeric_ASCII[122] = AN_D1 | AN_G1 | AN_N; /* z */
  AlphaNumeric_ASCII[123] = AN_A2 | AN_D2 | AN_G1 | AN_J | AN_M; /* { */
  AlphaNumeric_ASCII[124] = AN_J | AN_M; /* | */
  AlphaNumeric_ASCII[125] = AN_A1 | AN_D1 | AN_G2 | AN_J | AN_M; /* } */
  AlphaNumeric_ASCII[126] = AN_F | AN_H | AN_K; /* ~ */

  return returnVar;
}

/**
 * [ERW_LED_Display::ASCII2SEG18 description]
 * @param  ASCII_input input a printable ansii character
 * @return             uint32_t for 16bit LED, four bits for DPs,
*                      four used for control characters, and 8 are reserved
 */
uint32_t ERW_LED_Display::ASCII2AN(uint8_t ASCII_input)
{
  uint32_t returnValue = 0;
  returnValue = AlphaNumeric_ASCII[ASCII_input];
  return returnValue;
}

void ERW_LED_Display::lineRotation(uint16_t (&quarter_select)[4] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    quarter_select[0] = AN_J | AN_M;
    quarter_select[1] = AN_K | AN_N;
    quarter_select[2] = AN_G1 | AN_G2;
    quarter_select[3] = AN_H | AN_L;
  }
}

void ERW_LED_Display::xRotation(uint16_t (&half_select)[2] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    half_select[0] = AN_J | AN_M | AN_G1 | AN_G2;
    half_select[1] = AN_H | AN_K | AN_N | AN_L;
  }
}

void ERW_LED_Display::handRotation(uint16_t (&eighth_select)[8] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    eighth_select[0] = AN_J;
    eighth_select[1] = AN_K;
    eighth_select[2] = AN_G2;
    eighth_select[3] = AN_L;
    eighth_select[4] = AN_M;
    eighth_select[5] = AN_N;
    eighth_select[6] = AN_G1;
    eighth_select[7] = AN_H;
  }
}

void ERW_LED_Display::halfRotation(uint16_t (&eighth_select)[8] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    eighth_select[0] = AN_J | AN_K | AN_G2 | AN_L | AN_M;
    eighth_select[1] = AN_K | AN_G2 | AN_L | AN_M | AN_N;
    eighth_select[2] = AN_G2 | AN_L | AN_M | AN_N | AN_G1;
    eighth_select[3] = AN_L | AN_M | AN_N | AN_G1 | AN_H;
    eighth_select[4] = AN_M | AN_N | AN_G1 | AN_H | AN_J;
    eighth_select[5] = AN_N | AN_G1 | AN_H | AN_J | AN_K;
    eighth_select[6] = AN_G1 | AN_H |AN_J | AN_K | AN_G2;
    eighth_select[7] = AN_H |AN_J | AN_K | AN_G2 | AN_L;
  }
}

void ERW_LED_Display::quarterRotation(uint16_t (&eighth_select)[8] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    eighth_select[0] = AN_J | AN_K | AN_G2;
    eighth_select[1] = AN_K | AN_G2 | AN_L;
    eighth_select[2] = AN_G2 | AN_L | AN_M;
    eighth_select[3] = AN_L | AN_M | AN_N;
    eighth_select[4] = AN_M | AN_N | AN_G1;
    eighth_select[5] = AN_N | AN_G1 | AN_H;
    eighth_select[6] = AN_G1 | AN_H |AN_J;
    eighth_select[7] = AN_H |AN_J | AN_K;
  }
}

void ERW_LED_Display::eighthRotation(uint16_t (&eighth_select)[8] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    eighth_select[0] = AN_J | AN_K;
    eighth_select[1] = AN_K | AN_G2;
    eighth_select[2] = AN_G2 | AN_L;
    eighth_select[3] = AN_L | AN_M;
    eighth_select[4] = AN_M | AN_N;
    eighth_select[5] = AN_N | AN_G1;
    eighth_select[6] = AN_G1 | AN_H;
    eighth_select[7] = AN_H |AN_J;
  }
}

void ERW_LED_Display::fillPositive(uint16_t (&eighth_select)[8] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    eighth_select[0] = AN_J;
    eighth_select[1] = AN_J | AN_K;
    eighth_select[2] = AN_J | AN_K | AN_G2;
    eighth_select[3] = AN_J | AN_K | AN_G2 | AN_L;
    eighth_select[4] = AN_J | AN_K | AN_G2 | AN_L | AN_M;
    eighth_select[5] = AN_J | AN_K | AN_G2 | AN_L | AN_M | AN_N;
    eighth_select[6] = AN_J | AN_K | AN_G2 | AN_L | AN_M | AN_N | AN_G1;
    eighth_select[7] = AN_J | AN_K | AN_G2 | AN_L | AN_M | AN_N | AN_G1 | AN_H;
  }
}

void ERW_LED_Display::fillNegative(uint16_t (&eighth_select)[8] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    eighth_select[0] = AN_H;
    eighth_select[1] = AN_H | AN_G1;
    eighth_select[2] = AN_H | AN_G1 | AN_N;
    eighth_select[3] = AN_H | AN_G1 | AN_N | AN_M;
    eighth_select[4] = AN_H | AN_G1 | AN_N | AN_M | AN_L;
    eighth_select[5] = AN_H | AN_G1 | AN_N | AN_M | AN_L | AN_G2;
    eighth_select[6] = AN_H | AN_G1 | AN_N | AN_M | AN_L | AN_G2 | AN_K;
    eighth_select[7] = AN_H | AN_G1 | AN_N | AN_M | AN_L | AN_G2 | AN_K | AN_J;
  }
}

void ERW_LED_Display::verticalBars(uint16_t (&third_select)[3] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    third_select[0] = AN_D1 | AN_D2;
    third_select[1] = AN_G1 | AN_G2;
    third_select[2] = AN_A1 | AN_A2;
  }
}

void ERW_LED_Display::verticalFill(uint16_t (&fifth_select)[5] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    fifth_select[0] = AN_D1 | AN_D2;
    fifth_select[1] = AN_D1 | AN_D2 | AN_E | AN_N | AN_M | AN_L | AN_C;
    fifth_select[2] = AN_D1 | AN_D2 | AN_E | AN_N | AN_M | AN_L | AN_C | AN_G1 | AN_G2;
    fifth_select[3] = AN_D1 | AN_D2 | AN_E | AN_N | AN_M | AN_L | AN_C | AN_G1 | AN_G2 | AN_F | AN_H | AN_J | AN_K | AN_B;
    fifth_select[4] = AN_D1 | AN_D2 | AN_E | AN_N | AN_M | AN_L | AN_C | AN_G1 | AN_G2 | AN_F | AN_H | AN_J | AN_K | AN_B | AN_A1 | AN_A2;
  }
}

void ERW_LED_Display::horizontalBars(uint16_t (&third_select)[3] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    third_select[0] = AN_E | AN_F;
    third_select[1] = AN_J | AN_M;
    third_select[2] = AN_B | AN_C;
  }
}

void ERW_LED_Display::horizontalFill(uint16_t (&fifth_select)[5] )
{
  if( ERW_LED_Display_type & 0xF0 )
  {
    fifth_select[0] = AN_E | AN_F;
    fifth_select[1] = AN_E | AN_F | AN_A1 | AN_H | AN_G1 | AN_N | AN_D1;
    fifth_select[2] = AN_E | AN_F | AN_A1 | AN_H | AN_G1 | AN_N | AN_D1 | AN_J | AN_M;
    fifth_select[3] = AN_E | AN_F | AN_A1 | AN_H | AN_G1 | AN_N | AN_D1 | AN_J | AN_M | AN_A2 | AN_K | AN_G2 | AN_L | AN_D2;
    fifth_select[4] = AN_E | AN_F | AN_A1 | AN_H | AN_G1 | AN_N | AN_D1 | AN_J | AN_M | AN_A2 | AN_K | AN_G2 | AN_L | AN_D2 | AN_B | AN_C;
  }
}
