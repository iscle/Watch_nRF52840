#include "lvgl/lvgl.h"

/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef SAN_FRANCISCO_BOLD_20
#define SAN_FRANCISCO_BOLD_20 1
#endif

#if SAN_FRANCISCO_BOLD_20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0xff, 0xff, 0xff, 0xfc, 0xf, 0xc0,

    /* U+22 "\"" */
    0xef, 0xdf, 0xbf, 0x7e, 0xfd, 0xc0,

    /* U+23 "#" */
    0x8, 0xc3, 0x10, 0x66, 0x3f, 0xf7, 0xfe, 0x23,
    0x4, 0x61, 0x88, 0x31, 0x1f, 0xfb, 0xff, 0x19,
    0x82, 0x30, 0xc4, 0x0,

    /* U+24 "$" */
    0x8, 0x2, 0x0, 0x80, 0xfc, 0x7f, 0xba, 0x7e,
    0x9f, 0xa0, 0xf8, 0x1f, 0x83, 0xf8, 0x3f, 0x9,
    0xfa, 0x7e, 0x9d, 0xfe, 0x7f, 0x2, 0x0, 0x80,
    0x20,

    /* U+25 "%" */
    0x78, 0x3f, 0xc6, 0xcc, 0xcc, 0xcc, 0xfd, 0x87,
    0xb0, 0x6, 0x0, 0x7e, 0xf, 0xf1, 0xb3, 0x33,
    0x33, 0x33, 0x63, 0xfc, 0x1e,

    /* U+26 "&" */
    0x1e, 0xf, 0xe1, 0x8e, 0x30, 0x6, 0x0, 0x60,
    0x1e, 0x7, 0xe6, 0xed, 0xdc, 0xf3, 0x9e, 0x73,
    0xcf, 0xfc, 0x79, 0x80,

    /* U+27 "'" */
    0xff, 0xff, 0xc0,

    /* U+28 "(" */
    0x2, 0x1c, 0x79, 0xc7, 0x1e, 0x38, 0x70, 0xe1,
    0xc3, 0x87, 0xe, 0x1c, 0x3c, 0x38, 0x3c, 0x3c,
    0x38,

    /* U+29 ")" */
    0x1, 0xc3, 0xc3, 0xc1, 0xc3, 0xc3, 0x87, 0xe,
    0x1c, 0x38, 0x70, 0xe1, 0xc7, 0xe, 0x79, 0xe3,
    0x0,

    /* U+2A "*" */
    0xc, 0x3, 0x8, 0xc7, 0xb7, 0x7f, 0x83, 0x1,
    0xe0, 0xcc, 0x73, 0x80, 0x0,

    /* U+2B "+" */
    0x1c, 0x7, 0x1, 0xc3, 0xff, 0xff, 0xc7, 0x1,
    0xc0, 0x70, 0x1c, 0x0,

    /* U+2C "," */
    0x7b, 0x9c, 0xce, 0x60,

    /* U+2D "-" */
    0xff, 0xf0,

    /* U+2E "." */
    0xff, 0xf0,

    /* U+2F "/" */
    0x1, 0xc0, 0x60, 0x38, 0xe, 0x3, 0x1, 0xc0,
    0x70, 0x18, 0xe, 0x3, 0x1, 0xc0, 0x70, 0x18,
    0xe, 0x3, 0x80, 0xc0, 0x70, 0x18, 0xe, 0x0,

    /* U+30 "0" */
    0x3f, 0x1f, 0xef, 0x3f, 0x87, 0xe1, 0xf8, 0x7f,
    0xdf, 0xf7, 0xe1, 0xf8, 0x7e, 0x1f, 0xcf, 0x7f,
    0x8f, 0xc0,

    /* U+31 "1" */
    0x1e, 0x3f, 0x3b, 0x99, 0xc8, 0xe0, 0x70, 0x38,
    0x1c, 0xe, 0x7, 0x3, 0x81, 0xcf, 0xff, 0xfc,

    /* U+32 "2" */
    0x3e, 0x3f, 0xbc, 0xfc, 0x70, 0x38, 0x1c, 0x1c,
    0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0xf, 0xff, 0xfc,

    /* U+33 "3" */
    0x7f, 0x9f, 0xe0, 0x30, 0x18, 0xc, 0x7, 0xc1,
    0xf8, 0xf, 0x1, 0xc0, 0x7e, 0x1f, 0xcf, 0x7f,
    0x8f, 0xc0,

    /* U+34 "4" */
    0x7, 0x7, 0x3, 0x83, 0x83, 0x83, 0xc1, 0xcf,
    0xe7, 0xe3, 0xff, 0xff, 0xe0, 0x70, 0x38, 0x1c,

    /* U+35 "5" */
    0x7f, 0x9f, 0xe7, 0x1, 0xc0, 0x77, 0x1f, 0xe7,
    0x3c, 0x7, 0x1, 0xc0, 0x77, 0x1d, 0xcf, 0x7f,
    0x87, 0xc0,

    /* U+36 "6" */
    0xe, 0x3, 0x1, 0xc0, 0x60, 0x38, 0x1d, 0xc7,
    0xfb, 0xcf, 0xe1, 0xf8, 0x7e, 0x1f, 0xcf, 0x7f,
    0x87, 0x80,

    /* U+37 "7" */
    0xff, 0xff, 0xfe, 0x1f, 0x86, 0x3, 0x80, 0xe0,
    0x30, 0x1c, 0x6, 0x3, 0x80, 0xc0, 0x70, 0x1c,
    0x6, 0x0,

    /* U+38 "8" */
    0x3f, 0x1f, 0xef, 0x3f, 0x87, 0xe1, 0xdc, 0xe3,
    0xf0, 0xfc, 0x73, 0xb8, 0x7e, 0x1f, 0xcf, 0x7f,
    0x8f, 0xc0,

    /* U+39 "9" */
    0x1e, 0x1f, 0xef, 0x3f, 0x87, 0xe1, 0xf8, 0x7f,
    0x3d, 0xfe, 0x3b, 0x81, 0xc0, 0x60, 0x38, 0xc,
    0x7, 0x0,

    /* U+3A ":" */
    0xff, 0x80, 0x0, 0xff, 0x80,

    /* U+3B ";" */
    0x7b, 0xde, 0x0, 0x0, 0x0, 0x3, 0xdc, 0xe6,
    0x73, 0x0,

    /* U+3C "<" */
    0x0, 0x81, 0xc3, 0xe7, 0xcf, 0x6, 0x3, 0xc0,
    0x7c, 0xf, 0x81, 0xc0, 0x20,

    /* U+3D "=" */
    0xff, 0xff, 0xc0, 0x0, 0x0, 0x7, 0xff, 0xfe,

    /* U+3E ">" */
    0x80, 0x70, 0x3e, 0x7, 0xc0, 0xf8, 0xc, 0x1e,
    0x3c, 0xf8, 0x70, 0x20, 0x0,

    /* U+3F "?" */
    0xfc, 0xfe, 0xf, 0x7, 0x7, 0xf, 0x3e, 0x3c,
    0x30, 0x30, 0x0, 0x0, 0x70, 0x70,

    /* U+40 "@" */
    0x1f, 0x7, 0xf9, 0xc3, 0x70, 0x3c, 0x7, 0x8f,
    0xf3, 0xfe, 0x63, 0xcc, 0x79, 0x8f, 0x31, 0xe6,
    0x3c, 0xff, 0x8e, 0xf8, 0x3, 0x80, 0x3e, 0x3,
    0xc0,

    /* U+41 "A" */
    0x1e, 0x7, 0x81, 0xe0, 0xfc, 0x3f, 0xc, 0xc3,
    0x31, 0xce, 0x73, 0x9f, 0xe7, 0xfb, 0x87, 0xe1,
    0xf0, 0x30,

    /* U+42 "B" */
    0xfe, 0x3f, 0xce, 0x3b, 0x8e, 0xe3, 0xb8, 0xcf,
    0xe3, 0xfc, 0xe3, 0xb8, 0x7e, 0x1f, 0x8f, 0xff,
    0xbf, 0xc0,

    /* U+43 "C" */
    0x3f, 0x1f, 0xef, 0x3f, 0x87, 0xe0, 0x38, 0xe,
    0x3, 0x80, 0xe0, 0x38, 0xe, 0x1f, 0xcf, 0x7f,
    0x8f, 0xc0,

    /* U+44 "D" */
    0xfe, 0x7f, 0xb9, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0xff, 0xf7, 0xf0,

    /* U+45 "E" */
    0xff, 0xff, 0xf8, 0x1c, 0xe, 0x7, 0x3, 0xfd,
    0xfe, 0xe0, 0x70, 0x38, 0x1c, 0xf, 0xff, 0xfc,

    /* U+46 "F" */
    0xff, 0xff, 0xf8, 0x1c, 0xe, 0x7, 0x3, 0xff,
    0xff, 0xe0, 0x70, 0x38, 0x1c, 0xe, 0x7, 0x0,

    /* U+47 "G" */
    0x3f, 0x1f, 0xef, 0x1f, 0x87, 0xe0, 0x38, 0xe,
    0x7f, 0x9f, 0xe1, 0xf8, 0x7e, 0x1f, 0xcf, 0x7f,
    0x8f, 0xc0,

    /* U+48 "H" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0xff,
    0xff, 0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1c,

    /* U+49 "I" */
    0xff, 0xff, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,
    0x1c, 0x1c, 0x1c, 0x1c, 0xff, 0xff,

    /* U+4A "J" */
    0x1f, 0xc7, 0xf0, 0x1c, 0x7, 0x1, 0xc0, 0x70,
    0x1c, 0x7, 0x1, 0xc0, 0x7e, 0x1f, 0xcf, 0x7f,
    0x8f, 0xc0,

    /* U+4B "K" */
    0xe1, 0xf8, 0x7e, 0x3b, 0x8e, 0xe7, 0x39, 0xcf,
    0xe3, 0xf8, 0xe7, 0x39, 0xce, 0x3b, 0x8e, 0xe1,
    0xf8, 0x70,

    /* U+4C "L" */
    0xe0, 0x70, 0x38, 0x1c, 0xe, 0x7, 0x3, 0x81,
    0xc0, 0xe0, 0x70, 0x38, 0x1c, 0xf, 0xff, 0xfc,

    /* U+4D "M" */
    0xe1, 0xf8, 0x7f, 0x3f, 0xcf, 0xd2, 0xf7, 0xbd,
    0xef, 0x33, 0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0,
    0xf0, 0x30,

    /* U+4E "N" */
    0xe1, 0xf0, 0xfc, 0x7e, 0x3d, 0x9e, 0xcf, 0x67,
    0x9b, 0xcd, 0xe6, 0xf1, 0xf8, 0xfc, 0x3e, 0x1c,

    /* U+4F "O" */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0x77, 0xf1, 0xf0,

    /* U+50 "P" */
    0xff, 0x3f, 0xee, 0x3f, 0x87, 0xe1, 0xf8, 0xff,
    0xfb, 0xfc, 0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0,
    0x38, 0x0,

    /* U+51 "Q" */
    0x3f, 0x1f, 0xef, 0x3f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0xcf, 0x7f,
    0x8f, 0x80, 0x70, 0xe, 0x3, 0x80, 0x70,

    /* U+52 "R" */
    0xff, 0x3f, 0xee, 0x3f, 0x87, 0xe1, 0xf8, 0xff,
    0xfb, 0xf8, 0xe6, 0x39, 0xce, 0x33, 0x8e, 0xe3,
    0xb8, 0x70,

    /* U+53 "S" */
    0x3f, 0x1f, 0xee, 0x3f, 0x87, 0xe0, 0x3c, 0x7,
    0xf0, 0xfe, 0x3, 0xc0, 0x7e, 0x1f, 0xcf, 0x7f,
    0x8f, 0xc0,

    /* U+54 "T" */
    0xff, 0xff, 0xf0, 0xe0, 0x38, 0xe, 0x3, 0x80,
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0, 0x38, 0xe,
    0x3, 0x80,

    /* U+55 "U" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0x77, 0xf1, 0xf0,

    /* U+56 "V" */
    0xc0, 0xf8, 0x7e, 0x1d, 0x86, 0x61, 0x9c, 0xe7,
    0x38, 0xcc, 0x33, 0xf, 0xc3, 0xf0, 0x78, 0x1e,
    0x7, 0x80,

    /* U+57 "W" */
    0xce, 0x79, 0xcf, 0x29, 0xe5, 0x3c, 0xa7, 0xd5,
    0xda, 0xb3, 0x56, 0x7b, 0xcf, 0x79, 0xef, 0x38,
    0xe7, 0x1c, 0xe3, 0x80,

    /* U+58 "X" */
    0xe1, 0xd8, 0x67, 0x38, 0xcc, 0x3f, 0x7, 0x81,
    0xe0, 0x78, 0x1e, 0xf, 0xc3, 0x31, 0xce, 0xe1,
    0xf8, 0x70,

    /* U+59 "Y" */
    0xe0, 0xfc, 0x1d, 0xc7, 0x38, 0xe3, 0xb8, 0x77,
    0x6, 0xc0, 0xf8, 0xe, 0x1, 0xc0, 0x38, 0x7,
    0x0, 0xe0, 0x1c, 0x0,

    /* U+5A "Z" */
    0xff, 0xff, 0xc0, 0xe0, 0xe0, 0x70, 0x70, 0x70,
    0x38, 0x38, 0x38, 0x1c, 0x1c, 0xf, 0xff, 0xfc,

    /* U+5B "[" */
    0xff, 0xfe, 0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x8e,
    0x38, 0xe3, 0x8e, 0x38, 0xff, 0xf0,

    /* U+5C "\\" */
    0xe0, 0x18, 0x7, 0x1, 0xc0, 0x30, 0xe, 0x3,
    0x80, 0x60, 0x1c, 0x3, 0x0, 0xe0, 0x38, 0x6,
    0x1, 0xc0, 0x70, 0xc, 0x3, 0x80, 0x60, 0x1c,

    /* U+5D "]" */
    0xff, 0xf1, 0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c, 0x71, 0xc7, 0xff, 0xf0,

    /* U+5E "^" */
    0xc, 0x7, 0x81, 0xe0, 0xfc, 0x33, 0x1c, 0xe6,
    0x19, 0x86,

    /* U+5F "_" */
    0xff, 0xff, 0xf0,

    /* U+60 "`" */
    0xe3, 0x8c,

    /* U+61 "a" */
    0x1f, 0x1f, 0xe7, 0x1c, 0x7, 0x3f, 0xdf, 0xfe,
    0x1f, 0x87, 0xe3, 0xff, 0xf3, 0xdc,

    /* U+62 "b" */
    0xe0, 0x70, 0x38, 0x1d, 0xcf, 0xf7, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0x7f, 0xf7, 0x70,

    /* U+63 "c" */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7e, 0x7, 0x3, 0x81,
    0xc7, 0xe3, 0xbf, 0x8f, 0x80,

    /* U+64 "d" */
    0x3, 0x81, 0xc0, 0xe7, 0x77, 0xff, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0x77, 0xf9, 0xdc,

    /* U+65 "e" */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7f, 0xff, 0xff, 0x81,
    0xc0, 0xe3, 0xbf, 0x8f, 0x80,

    /* U+66 "f" */
    0xf, 0xc7, 0xf1, 0xc0, 0x70, 0xff, 0xff, 0xf1,
    0xc0, 0x70, 0x1c, 0x7, 0x1, 0xc0, 0x70, 0x1c,
    0x7, 0x0,

    /* U+67 "g" */
    0x3b, 0xbf, 0xfd, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xf7, 0xbf, 0xce, 0xe0, 0x70, 0x39, 0xf8,
    0xf8,

    /* U+68 "h" */
    0xe0, 0x70, 0x38, 0x1d, 0xcf, 0xf7, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1c,

    /* U+69 "i" */
    0x1c, 0x7, 0x1, 0xc0, 0x0, 0x0, 0x3f, 0xf,
    0xc0, 0x70, 0x1c, 0x7, 0x1, 0xc0, 0x70, 0x1c,
    0x7, 0xf, 0xff, 0xff,

    /* U+6A "j" */
    0x7, 0x7, 0x7, 0x0, 0xff, 0xff, 0x7, 0x7,
    0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
    0xf, 0xfe, 0xfc,

    /* U+6B "k" */
    0xe0, 0x38, 0xe, 0x3, 0x87, 0xe3, 0xb8, 0xee,
    0x73, 0xf8, 0xfe, 0x39, 0xce, 0x33, 0x8e, 0xe1,
    0xb8, 0x70,

    /* U+6C "l" */
    0xfe, 0x1f, 0xc0, 0x38, 0x7, 0x0, 0xe0, 0x1c,
    0x3, 0x80, 0x70, 0xe, 0x1, 0xc0, 0x38, 0x7,
    0x0, 0x7e, 0x7, 0xc0,

    /* U+6D "m" */
    0xd9, 0xbf, 0xfc, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33, 0xcc, 0xf3, 0x3c, 0xcc,

    /* U+6E "n" */
    0xee, 0x7f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xe0,

    /* U+6F "o" */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xbf, 0x8f, 0x80,

    /* U+70 "p" */
    0xee, 0x7f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xff, 0xbb, 0x9c, 0xe, 0x7, 0x3,
    0x80,

    /* U+71 "q" */
    0x3b, 0xbf, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xbf, 0xce, 0xe0, 0x70, 0x38, 0x1c,
    0xe,

    /* U+72 "r" */
    0xee, 0x7f, 0xb8, 0xfc, 0x7e, 0x3f, 0x3, 0x81,
    0xc0, 0xe0, 0x70, 0x38, 0x0,

    /* U+73 "s" */
    0x1f, 0x1f, 0xf7, 0x1d, 0xc0, 0x7c, 0xf, 0xe0,
    0x3c, 0x7, 0x71, 0xdf, 0xe3, 0xf0,

    /* U+74 "t" */
    0x1c, 0x7, 0x1, 0xc3, 0xff, 0xff, 0xc7, 0x1,
    0xc0, 0x70, 0x1c, 0x7, 0x1, 0xc0, 0x70, 0x1f,
    0xc3, 0xf0,

    /* U+75 "u" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xbf, 0x8f, 0x80,

    /* U+76 "v" */
    0xe0, 0xf8, 0x76, 0x19, 0x86, 0x73, 0x8c, 0xc3,
    0x30, 0xfc, 0x1e, 0x7, 0x81, 0xe0,

    /* U+77 "w" */
    0xe6, 0x36, 0x66, 0x66, 0x66, 0xf6, 0x6f, 0x66,
    0x96, 0x69, 0x62, 0x94, 0x39, 0xc3, 0x9c, 0x39,
    0xc0,

    /* U+78 "x" */
    0xe1, 0xdc, 0xe3, 0x30, 0xfc, 0x1e, 0x7, 0x81,
    0xe0, 0xfc, 0x73, 0x9c, 0x6e, 0x1c,

    /* U+79 "y" */
    0xe1, 0xf8, 0x76, 0x19, 0xce, 0x73, 0x8c, 0xc3,
    0xf0, 0x7c, 0x1e, 0x7, 0x80, 0xe0, 0x30, 0x1c,
    0x6, 0x3, 0x80,

    /* U+7A "z" */
    0xff, 0xff, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    0xe0, 0xe0, 0x7f, 0xff, 0xe0,

    /* U+7B "{" */
    0x3, 0x87, 0xc3, 0x81, 0xc0, 0xe0, 0x70, 0x38,
    0x1c, 0xfc, 0x7e, 0x3, 0x81, 0xc0, 0xe0, 0x70,
    0x38, 0x1c, 0xf, 0x81, 0xc0,

    /* U+7C "|" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,

    /* U+7D "}" */
    0xf0, 0x3e, 0x1, 0xc0, 0x70, 0x1c, 0x7, 0x1,
    0xc0, 0x70, 0xf, 0xc3, 0xf1, 0xc0, 0x70, 0x1c,
    0x7, 0x1, 0xc0, 0x70, 0xf8, 0x3c, 0x0,

    /* U+7E "~" */
    0x78, 0xff, 0x3c, 0xcf, 0x3f, 0xc7, 0x80,

    /* U+410 "А" */
    0x1e, 0x7, 0x81, 0xe0, 0xfc, 0x3f, 0xc, 0xc3,
    0x31, 0xce, 0x73, 0x9f, 0xe7, 0xfb, 0x87, 0xe1,
    0xf0, 0x30,

    /* U+411 "Б" */
    0xff, 0xbf, 0xee, 0x3, 0x80, 0xe0, 0x3f, 0xcf,
    0xfb, 0x8f, 0xe1, 0xf8, 0x7e, 0x1f, 0x8f, 0xff,
    0xbf, 0x80,

    /* U+412 "В" */
    0xfe, 0x3f, 0xce, 0x3b, 0x8e, 0xe3, 0xb8, 0xcf,
    0xe3, 0xfc, 0xe3, 0xb8, 0x7e, 0x1f, 0x8f, 0xff,
    0xbf, 0xc0,

    /* U+413 "Г" */
    0xff, 0xff, 0xf8, 0x1c, 0xe, 0x7, 0x3, 0x81,
    0xc0, 0xe0, 0x70, 0x38, 0x1c, 0xe, 0x7, 0x0,

    /* U+414 "Д" */
    0x3f, 0xc7, 0xf8, 0xe7, 0x1c, 0xe3, 0x9c, 0x73,
    0x8e, 0x71, 0xce, 0x39, 0xc7, 0x38, 0xe7, 0x38,
    0xef, 0xff, 0xff, 0xf8, 0x3f, 0x7, 0xe0, 0xe0,

    /* U+415 "Е" */
    0xff, 0xff, 0xf8, 0x1c, 0xe, 0x7, 0x3, 0xfd,
    0xfe, 0xe0, 0x70, 0x38, 0x1c, 0xf, 0xff, 0xfc,

    /* U+416 "Ж" */
    0xe6, 0x76, 0x66, 0x66, 0x67, 0x66, 0x36, 0xc3,
    0x6c, 0x3f, 0xc3, 0x6c, 0x36, 0xc7, 0x6e, 0x66,
    0x66, 0x66, 0x66, 0x6c, 0x63,

    /* U+417 "З" */
    0x1f, 0x8f, 0xfd, 0xc7, 0x80, 0x70, 0x1c, 0x3e,
    0x7, 0xf0, 0xf, 0x0, 0xe0, 0x1d, 0x83, 0xb8,
    0xf7, 0xfc, 0x3e, 0x0,

    /* U+418 "И" */
    0xc3, 0xe3, 0xf1, 0xf8, 0xfc, 0xde, 0x6f, 0x37,
    0xb3, 0xd9, 0xfc, 0xfc, 0x7e, 0x3e, 0x1f, 0xc,

    /* U+419 "Й" */
    0x63, 0x31, 0x8f, 0x83, 0x80, 0x6, 0x1f, 0x1f,
    0x8f, 0xc7, 0xe7, 0xf3, 0x79, 0xbd, 0x9e, 0xcf,
    0xe7, 0xe3, 0xf1, 0xf8, 0xf8, 0x60,

    /* U+41A "К" */
    0xe1, 0xf8, 0x7e, 0x3b, 0x8e, 0xe7, 0x39, 0xcf,
    0xe3, 0xf8, 0xe7, 0x39, 0xce, 0x3b, 0x8e, 0xe1,
    0xf8, 0x70,

    /* U+41B "Л" */
    0x3f, 0xcf, 0xf3, 0x9c, 0xe7, 0x39, 0xce, 0x73,
    0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9d, 0xe7, 0xf1,
    0xf8, 0x70,

    /* U+41C "М" */
    0xe1, 0xf8, 0x7f, 0x3f, 0xcf, 0xd2, 0xf7, 0xbd,
    0xef, 0x33, 0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0,
    0xf0, 0x30,

    /* U+41D "Н" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0xff,
    0xff, 0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1c,

    /* U+41E "О" */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0x77, 0xf1, 0xf0,

    /* U+41F "П" */
    0xff, 0xff, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1c,

    /* U+420 "Р" */
    0xff, 0x3f, 0xee, 0x3f, 0x87, 0xe1, 0xf8, 0xff,
    0xfb, 0xfc, 0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0,
    0x38, 0x0,

    /* U+421 "С" */
    0x3f, 0x1f, 0xef, 0x3f, 0x87, 0xe0, 0x38, 0xe,
    0x3, 0x80, 0xe0, 0x38, 0xe, 0x1f, 0xcf, 0x7f,
    0x8f, 0xc0,

    /* U+422 "Т" */
    0xff, 0xff, 0xf0, 0xe0, 0x38, 0xe, 0x3, 0x80,
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0, 0x38, 0xe,
    0x3, 0x80,

    /* U+423 "У" */
    0xe1, 0xf8, 0x76, 0x19, 0xce, 0x33, 0x8c, 0xc3,
    0xb0, 0x7c, 0x1e, 0x3, 0x80, 0xc0, 0x70, 0x1c,
    0x6, 0x0,

    /* U+424 "Ф" */
    0xc, 0xf, 0xc7, 0xfb, 0xb7, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33, 0xcc, 0xf3, 0x3c, 0xcf, 0xb7, 0x7f,
    0x8f, 0xc0, 0xc0, 0x30,

    /* U+425 "Х" */
    0xe1, 0xd8, 0x67, 0x38, 0xcc, 0x3f, 0x7, 0x81,
    0xe0, 0x78, 0x1e, 0xf, 0xc3, 0x31, 0xce, 0xe1,
    0xf8, 0x70,

    /* U+426 "Ц" */
    0xe3, 0xb8, 0xee, 0x3b, 0x8e, 0xe3, 0xb8, 0xee,
    0x3b, 0x8e, 0xe3, 0xb8, 0xee, 0x3b, 0x8e, 0xff,
    0xff, 0xf0, 0x1c, 0x7, 0x1, 0xc0,

    /* U+427 "Ч" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0xce,
    0xff, 0x3f, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1c,

    /* U+428 "Ш" */
    0xcc, 0xf3, 0x3c, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33, 0xcc, 0xf3, 0x3c, 0xcf, 0x33, 0xff,
    0xff, 0xf0,

    /* U+429 "Щ" */
    0xcc, 0xd9, 0x9b, 0x33, 0x66, 0x6c, 0xcd, 0x99,
    0xb3, 0x36, 0x66, 0xcc, 0xd9, 0x9b, 0x33, 0x66,
    0x6f, 0xff, 0xff, 0xc0, 0x18, 0x3,

    /* U+42A "Ъ" */
    0xfc, 0xf, 0xc0, 0x1c, 0x1, 0xc0, 0x1c, 0x1,
    0xfc, 0x1f, 0xe1, 0xcf, 0x1c, 0x71, 0xc7, 0x1c,
    0x71, 0xcf, 0x1f, 0xe1, 0xf8,

    /* U+42B "Ы" */
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0, 0xfe, 0x3f,
    0xcf, 0x3b, 0xc6, 0xf1, 0xbc, 0x6f, 0x3b, 0xfc,
    0xfe, 0x30,

    /* U+42C "Ь" */
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0, 0x3f, 0xcf,
    0xfb, 0x8f, 0xe1, 0xf8, 0x7e, 0x1f, 0x8f, 0xff,
    0xbf, 0x80,

    /* U+42D "Э" */
    0x3e, 0x3f, 0xb8, 0xfc, 0x70, 0x38, 0x1c, 0x7e,
    0x3f, 0x3, 0x81, 0xf8, 0xfc, 0x77, 0xf1, 0xf0,

    /* U+42E "Ю" */
    0xc7, 0xb3, 0xfc, 0xcf, 0x33, 0xcc, 0xff, 0x3f,
    0xcf, 0x33, 0xcc, 0xf3, 0x3c, 0xcf, 0x33, 0xcf,
    0xf1, 0xe0,

    /* U+42F "Я" */
    0x3f, 0xdf, 0xff, 0x1f, 0x87, 0xe1, 0xfc, 0x77,
    0xfc, 0x7f, 0x19, 0xce, 0x73, 0x1d, 0xc7, 0x71,
    0xf8, 0x70,

    /* U+430 "а" */
    0x1f, 0x1f, 0xe7, 0x1c, 0x7, 0x3f, 0xdf, 0xfe,
    0x1f, 0x87, 0xe3, 0xff, 0xf3, 0xdc,

    /* U+431 "б" */
    0x1f, 0x3f, 0x9c, 0x1c, 0xe, 0xe7, 0xfb, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0x77, 0xf1, 0xf0,

    /* U+432 "в" */
    0xff, 0x3f, 0xee, 0x3b, 0x8e, 0xfe, 0x3f, 0xee,
    0x1f, 0x87, 0xe1, 0xff, 0xef, 0xf0,

    /* U+433 "г" */
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    0xe0, 0xe0, 0xe0,

    /* U+434 "д" */
    0x3f, 0xc7, 0xf8, 0xe7, 0x1c, 0xe3, 0x9c, 0x73,
    0x8e, 0x71, 0xce, 0x71, 0xdf, 0xff, 0xff, 0xf0,
    0x7e, 0xf, 0xc1, 0xc0,

    /* U+435 "е" */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7f, 0xff, 0xff, 0x81,
    0xc0, 0xe3, 0xbf, 0x8f, 0x80,

    /* U+436 "ж" */
    0xe6, 0x76, 0x66, 0x66, 0x63, 0x6c, 0x36, 0xc3,
    0xfc, 0x36, 0xc3, 0x6c, 0x66, 0x66, 0x66, 0xe6,
    0x70,

    /* U+437 "з" */
    0x3f, 0x1f, 0xfe, 0x1c, 0x7, 0x1f, 0x7, 0xe0,
    0x1c, 0x7, 0xe1, 0xdf, 0xe3, 0xf0,

    /* U+438 "и" */
    0xc3, 0xe3, 0xf1, 0xf9, 0xfc, 0xde, 0xef, 0x67,
    0xb3, 0xf1, 0xf8, 0xf8, 0x60,

    /* U+439 "й" */
    0x63, 0x31, 0x8f, 0x83, 0x80, 0x6, 0x1f, 0x1f,
    0x8f, 0xcf, 0xe6, 0xf7, 0x7b, 0x3f, 0x9f, 0x8f,
    0xc7, 0xc3,

    /* U+43A "к" */
    0xe1, 0xf8, 0xee, 0x33, 0x9c, 0xfe, 0x3f, 0x8e,
    0x73, 0x9c, 0xe3, 0xb8, 0x6e, 0x1c,

    /* U+43B "л" */
    0x3f, 0xcf, 0xf3, 0x9c, 0xe7, 0x39, 0xce, 0x73,
    0x9c, 0xe7, 0x39, 0xfc, 0x7e, 0x1c,

    /* U+43C "м" */
    0xe1, 0xf8, 0x7f, 0x3f, 0xcf, 0xda, 0xf7, 0xbd,
    0xef, 0x33, 0xc0, 0xf0, 0x3c, 0xc,

    /* U+43D "н" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0xff, 0xff,
    0xc7, 0xe3, 0xf1, 0xf8, 0xe0,

    /* U+43E "о" */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xbf, 0x8f, 0x80,

    /* U+43F "п" */
    0xff, 0xff, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xe0,

    /* U+440 "р" */
    0xee, 0x7f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xff, 0xbb, 0x9c, 0xe, 0x7, 0x3,
    0x80,

    /* U+441 "с" */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7e, 0x7, 0x3, 0x81,
    0xc7, 0xe3, 0xbf, 0x8f, 0x80,

    /* U+442 "т" */
    0xff, 0xff, 0xf0, 0xe0, 0x38, 0xe, 0x3, 0x80,
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0,

    /* U+443 "у" */
    0xe1, 0xf8, 0x76, 0x19, 0xce, 0x73, 0x8c, 0xc3,
    0xf0, 0x7c, 0x1e, 0x7, 0x80, 0xe0, 0x30, 0x1c,
    0x6, 0x3, 0x80,

    /* U+444 "ф" */
    0xc, 0x3, 0x0, 0xc0, 0xfc, 0x7f, 0xbb, 0x7c,
    0xcf, 0x33, 0xcc, 0xf3, 0x3c, 0xcf, 0xb7, 0x7f,
    0x8f, 0xc0, 0xc0, 0x30, 0xc, 0x3, 0x0,

    /* U+445 "х" */
    0xe1, 0xdc, 0xe3, 0x30, 0xfc, 0x1e, 0x7, 0x81,
    0xe0, 0xfc, 0x73, 0x9c, 0x6e, 0x1c,

    /* U+446 "ц" */
    0xe3, 0xb8, 0xee, 0x3b, 0x8e, 0xe3, 0xb8, 0xee,
    0x3b, 0x8e, 0xe3, 0xbf, 0xff, 0xfc, 0x7, 0x1,
    0xc0, 0x70,

    /* U+447 "ч" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3b, 0xfc, 0xfe,
    0x7, 0x3, 0x81, 0xc0, 0xe0,

    /* U+448 "ш" */
    0xcc, 0xf3, 0x3c, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33, 0xcc, 0xff, 0xff, 0xfc,

    /* U+449 "щ" */
    0xcc, 0xd9, 0x9b, 0x33, 0x66, 0x6c, 0xcd, 0x99,
    0xb3, 0x36, 0x66, 0xcc, 0xdf, 0xff, 0xff, 0x80,
    0x30, 0x6,

    /* U+44A "ъ" */
    0xfc, 0xf, 0xc0, 0x1c, 0x1, 0xc0, 0x1f, 0xc1,
    0xfe, 0x1c, 0x71, 0xc7, 0x1c, 0x71, 0xfe, 0x1f,
    0xc0,

    /* U+44B "ы" */
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xf8, 0xff, 0x3c,
    0x6f, 0x1b, 0xc6, 0xff, 0x3f, 0x8c,

    /* U+44C "ь" */
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xff, 0x3f, 0xee,
    0x1f, 0x87, 0xe1, 0xff, 0xef, 0xf0,

    /* U+44D "э" */
    0x3e, 0x3f, 0xb8, 0xe0, 0x70, 0xf8, 0x7c, 0xf,
    0xc7, 0xe7, 0xbf, 0x8f, 0x80,

    /* U+44E "ю" */
    0xc7, 0xb3, 0xfc, 0xcf, 0x33, 0xfc, 0xff, 0x3c,
    0xcf, 0x33, 0xcc, 0xf3, 0xfc, 0x78,

    /* U+44F "я" */
    0x3f, 0xbf, 0xf8, 0xfc, 0x7e, 0x3b, 0xfc, 0xfe,
    0x77, 0x33, 0xb9, 0xf8, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 192, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 192, .box_w = 3, .box_h = 14, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 192, .box_w = 7, .box_h = 6, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 13, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 192, .box_w = 10, .box_h = 20, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 58, .adv_w = 192, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 192, .box_w = 3, .box_h = 6, .ofs_x = 5, .ofs_y = 8},
    {.bitmap_index = 102, .adv_w = 192, .box_w = 7, .box_h = 19, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 119, .adv_w = 192, .box_w = 7, .box_h = 19, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 136, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 149, .adv_w = 192, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 161, .adv_w = 192, .box_w = 5, .box_h = 6, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 165, .adv_w = 192, .box_w = 6, .box_h = 2, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 167, .adv_w = 192, .box_w = 4, .box_h = 3, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 192, .box_w = 10, .box_h = 19, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 193, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 192, .box_w = 3, .box_h = 11, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 192, .box_w = 5, .box_h = 15, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 382, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 395, .adv_w = 192, .box_w = 9, .box_h = 7, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 403, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 416, .adv_w = 192, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 192, .box_w = 11, .box_h = 18, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 455, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 591, .adv_w = 192, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 691, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 192, .box_w = 10, .box_h = 18, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 748, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 766, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 784, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 802, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 818, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 856, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 874, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 894, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 910, .adv_w = 192, .box_w = 6, .box_h = 18, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 924, .adv_w = 192, .box_w = 10, .box_h = 19, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 948, .adv_w = 192, .box_w = 6, .box_h = 18, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 962, .adv_w = 192, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 972, .adv_w = 192, .box_w = 10, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 975, .adv_w = 192, .box_w = 5, .box_h = 3, .ofs_x = 3, .ofs_y = 13},
    {.bitmap_index = 977, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 991, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1007, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1020, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1036, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1049, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1067, .adv_w = 192, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1084, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1100, .adv_w = 192, .box_w = 10, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1120, .adv_w = 192, .box_w = 8, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1139, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1157, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1177, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1191, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1204, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1217, .adv_w = 192, .box_w = 9, .box_h = 15, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 1234, .adv_w = 192, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1251, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1264, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1278, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1296, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1309, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1323, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1340, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1354, .adv_w = 192, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1373, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1386, .adv_w = 192, .box_w = 9, .box_h = 18, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1407, .adv_w = 192, .box_w = 3, .box_h = 18, .ofs_x = 5, .ofs_y = -2},
    {.bitmap_index = 1414, .adv_w = 192, .box_w = 10, .box_h = 18, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1437, .adv_w = 192, .box_w = 10, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1444, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1462, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1480, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1498, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1514, .adv_w = 192, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1538, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1554, .adv_w = 192, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1575, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1595, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1611, .adv_w = 192, .box_w = 9, .box_h = 19, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1633, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1651, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1669, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1687, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1703, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1719, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1735, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1753, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1771, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1789, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1807, .adv_w = 192, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1827, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1845, .adv_w = 192, .box_w = 10, .box_h = 17, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 1867, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1883, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1901, .adv_w = 192, .box_w = 11, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1923, .adv_w = 192, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1944, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1962, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1980, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1996, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2014, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2032, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2046, .adv_w = 192, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2062, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2076, .adv_w = 192, .box_w = 8, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2087, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2107, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2120, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2137, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2151, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2164, .adv_w = 192, .box_w = 9, .box_h = 16, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2182, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2196, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2210, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2224, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2237, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2250, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2263, .adv_w = 192, .box_w = 9, .box_h = 15, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 2280, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2293, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2307, .adv_w = 192, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2326, .adv_w = 192, .box_w = 10, .box_h = 18, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 2349, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2363, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 2381, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2394, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2408, .adv_w = 192, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2426, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2443, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2457, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2471, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2484, .adv_w = 192, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2498, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 1040, .range_length = 64, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t San_Francisco_Bold_20 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 23,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -3,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if SAN_FRANCISCO_BOLD_20*/

