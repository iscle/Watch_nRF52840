#include "lvgl/lvgl.h"

/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef SAN_FRANCISCO_BOLD_18
#define SAN_FRANCISCO_BOLD_18 1
#endif

#if SAN_FRANCISCO_BOLD_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0x6d, 0xb6, 0xdb, 0x60, 0x7e,

    /* U+22 "\"" */
    0xcf, 0x3c, 0xf3, 0xcc,

    /* U+23 "#" */
    0x19, 0x86, 0x41, 0x11, 0xff, 0x7f, 0xc4, 0xc3,
    0x30, 0xc8, 0xff, 0xbf, 0xe2, 0x20, 0x98, 0x66,
    0x0,

    /* U+24 "$" */
    0x8, 0x8, 0x1c, 0x7e, 0xef, 0xcb, 0xc8, 0xf8,
    0x7c, 0x1e, 0xf, 0xb, 0xcb, 0xef, 0x7e, 0x1c,
    0x8, 0x8,

    /* U+25 "%" */
    0x70, 0x7f, 0x1b, 0x66, 0x6c, 0xcf, 0xb0, 0xec,
    0x1, 0x0, 0x7e, 0x1f, 0xe6, 0xcc, 0xd9, 0xb3,
    0xfc, 0x3c,

    /* U+26 "&" */
    0x3c, 0x1f, 0x86, 0x31, 0x80, 0x60, 0xc, 0x7,
    0x83, 0x76, 0xcf, 0xb1, 0xcc, 0x73, 0xfe, 0x79,
    0x80,

    /* U+27 "'" */
    0xff, 0xc0,

    /* U+28 "(" */
    0xc, 0xf7, 0x98, 0xe3, 0xc, 0x30, 0xc3, 0xc,
    0x30, 0xc1, 0x87, 0xf, 0xc,

    /* U+29 ")" */
    0xc3, 0x87, 0x6, 0x1c, 0x30, 0xc3, 0xc, 0x30,
    0xc3, 0x1c, 0x63, 0xbc, 0xc0,

    /* U+2A "*" */
    0xc, 0x3, 0x0, 0xc3, 0xff, 0x7f, 0x83, 0x1,
    0xe0, 0xcc, 0x33, 0x0,

    /* U+2B "+" */
    0x18, 0xc, 0x6, 0x1f, 0xff, 0xf8, 0xc0, 0x60,
    0x30,

    /* U+2C "," */
    0x76, 0xec, 0xc0,

    /* U+2D "-" */
    0xff, 0xf0,

    /* U+2E "." */
    0xff, 0x80,

    /* U+2F "/" */
    0x3, 0x81, 0x81, 0xc0, 0xc0, 0x60, 0x70, 0x30,
    0x18, 0x1c, 0xc, 0xe, 0x6, 0x3, 0x3, 0x81,
    0x80, 0xc0, 0xe0, 0x0,

    /* U+30 "0" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xdb, 0xdb, 0xc3,
    0xc3, 0xc3, 0xe7, 0x7e, 0x3c,

    /* U+31 "1" */
    0x1c, 0x7c, 0xec, 0xcc, 0xc, 0xc, 0xc, 0xc,
    0xc, 0xc, 0xc, 0xff, 0xff,

    /* U+32 "2" */
    0x3c, 0x7e, 0xe7, 0xc3, 0x3, 0x7, 0x6, 0xc,
    0x18, 0x30, 0xe0, 0xff, 0xff,

    /* U+33 "3" */
    0x7f, 0x7f, 0x6, 0xc, 0x18, 0x3e, 0x3f, 0x3,
    0x3, 0xc3, 0xe7, 0x7e, 0x3c,

    /* U+34 "4" */
    0x6, 0xc, 0x1c, 0x18, 0x30, 0x60, 0xe3, 0xc3,
    0xff, 0xff, 0x3, 0x3, 0x3,

    /* U+35 "5" */
    0x7f, 0xbf, 0xd8, 0xc, 0x6, 0xe3, 0xf9, 0x8e,
    0x3, 0x1, 0x80, 0xd8, 0xef, 0xe3, 0xe0,

    /* U+36 "6" */
    0xe, 0xe, 0x6, 0x7, 0x3, 0x3, 0x73, 0xfd,
    0xc7, 0xc1, 0xe0, 0xf8, 0xef, 0xe3, 0xe0,

    /* U+37 "7" */
    0xff, 0xff, 0xf0, 0xf8, 0x60, 0x70, 0x30, 0x38,
    0x1c, 0xc, 0xe, 0x6, 0x7, 0x3, 0x0,

    /* U+38 "8" */
    0x3c, 0x3f, 0x39, 0xd8, 0x6c, 0x33, 0x30, 0xf8,
    0xce, 0xc1, 0xe0, 0xf8, 0xef, 0xe3, 0xe0,

    /* U+39 "9" */
    0x3e, 0x3f, 0xb8, 0xf8, 0x3c, 0x1f, 0x1d, 0xfc,
    0x76, 0x6, 0x7, 0x3, 0x3, 0x83, 0x80,

    /* U+3A ":" */
    0xff, 0x80, 0x7, 0xfc,

    /* U+3B ";" */
    0x77, 0x70, 0x0, 0x0, 0x76, 0x6e, 0xc0,

    /* U+3C "<" */
    0x1, 0x7, 0x1f, 0x78, 0xe0, 0xe0, 0x78, 0x1e,
    0x7, 0x1,

    /* U+3D "=" */
    0xff, 0xff, 0x0, 0x0, 0xff, 0xff,

    /* U+3E ">" */
    0x80, 0xe0, 0xf8, 0x1e, 0x7, 0x7, 0x1e, 0x78,
    0xe0, 0x80,

    /* U+3F "?" */
    0xf9, 0xf8, 0x18, 0x30, 0xef, 0x9e, 0x30, 0x60,
    0x0, 0x3, 0x87, 0x0,

    /* U+40 "@" */
    0x1f, 0x1f, 0xe6, 0x1f, 0x3, 0xcf, 0xf7, 0xfd,
    0x8f, 0x63, 0xd8, 0xf6, 0x3d, 0x8f, 0x3f, 0xc0,
    0x18, 0x7, 0xc0, 0x70,

    /* U+41 "A" */
    0x1c, 0xe, 0xf, 0x6, 0xc3, 0x61, 0xb1, 0x9c,
    0xc6, 0x7f, 0x7f, 0xb8, 0xf8, 0x7c, 0x18,

    /* U+42 "B" */
    0xfc, 0xff, 0xc3, 0xc3, 0xc3, 0xfe, 0xfe, 0xc7,
    0xc3, 0xc3, 0xc7, 0xfe, 0xfc,

    /* U+43 "C" */
    0x3c, 0x7e, 0xc3, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc3, 0xc7, 0x7e, 0x3c,

    /* U+44 "D" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc7, 0xfe, 0xfc,

    /* U+45 "E" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xc0,
    0xc0, 0xc0, 0xc0, 0xff, 0xff,

    /* U+46 "F" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0xff,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0,

    /* U+47 "G" */
    0x3c, 0x7e, 0xc3, 0xc3, 0xc0, 0xc0, 0xcf, 0xcf,
    0xc3, 0xc3, 0xc3, 0x7e, 0x3c,

    /* U+48 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+49 "I" */
    0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0xff, 0xff,

    /* U+4A "J" */
    0x1f, 0x8f, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6,
    0x3, 0x1, 0xe0, 0xf8, 0xef, 0xe3, 0xe0,

    /* U+4B "K" */
    0xc3, 0x63, 0xb1, 0x99, 0xcc, 0xc7, 0xe3, 0xf1,
    0x98, 0xce, 0x63, 0x31, 0xd8, 0xec, 0x30,

    /* U+4C "L" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xff, 0xff,

    /* U+4D "M" */
    0xe3, 0xf1, 0xfc, 0xfe, 0xfd, 0x5e, 0xaf, 0x77,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x18,

    /* U+4E "N" */
    0xe3, 0xe3, 0xf3, 0xf3, 0xf3, 0xdb, 0xdb, 0xdb,
    0xcf, 0xcf, 0xcf, 0xc7, 0xc7,

    /* U+4F "O" */
    0x3c, 0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc7, 0x7e, 0x3c,

    /* U+50 "P" */
    0xfe, 0x7f, 0xb0, 0xf8, 0x3c, 0x1e, 0x1f, 0xfd,
    0xfc, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x0,

    /* U+51 "Q" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xe7, 0x7e, 0x3c, 0xe, 0x6, 0x3,

    /* U+52 "R" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xfc,
    0xcc, 0xce, 0xc6, 0xc7, 0xc3,

    /* U+53 "S" */
    0x3e, 0x3f, 0xb8, 0xf8, 0x3c, 0x3, 0xc0, 0xf8,
    0xe, 0x1, 0xe0, 0xf8, 0xef, 0xe3, 0xe0,

    /* U+54 "T" */
    0xff, 0xff, 0xc3, 0x1, 0x80, 0xc0, 0x60, 0x30,
    0x18, 0xc, 0x6, 0x3, 0x1, 0x80, 0xc0,

    /* U+55 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xe7, 0x7e, 0x3c,

    /* U+56 "V" */
    0xc1, 0xe0, 0xf8, 0xec, 0x66, 0x33, 0x19, 0x9c,
    0x6c, 0x36, 0x1b, 0xd, 0x83, 0x81, 0xc0,

    /* U+57 "W" */
    0xcc, 0xf3, 0x3c, 0xcd, 0x3b, 0x6a, 0xda, 0xb6,
    0xad, 0xea, 0x7a, 0x9c, 0xe7, 0x39, 0xce, 0x73,
    0x80,

    /* U+58 "X" */
    0x61, 0xcc, 0x63, 0x38, 0x6c, 0x1f, 0x3, 0x80,
    0xe0, 0x38, 0x1f, 0xe, 0xc3, 0x39, 0xc6, 0x60,
    0xc0,

    /* U+59 "Y" */
    0xe1, 0xd8, 0x67, 0x38, 0xcc, 0x33, 0x7, 0x81,
    0xe0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30, 0xc,
    0x0,

    /* U+5A "Z" */
    0xff, 0xff, 0x7, 0x6, 0xe, 0x1c, 0x18, 0x38,
    0x70, 0x60, 0xe0, 0xff, 0xff,

    /* U+5B "[" */
    0xff, 0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c,
    0x63, 0x1f, 0xf8,

    /* U+5C "\\" */
    0xe0, 0x30, 0x18, 0xe, 0x3, 0x1, 0x80, 0xe0,
    0x30, 0x1c, 0x6, 0x3, 0x1, 0xc0, 0x60, 0x30,
    0x1c, 0x6, 0x3, 0x80,

    /* U+5D "]" */
    0xff, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0x7f, 0xf8,

    /* U+5E "^" */
    0x1c, 0xe, 0xd, 0x86, 0xc6, 0x63, 0x1b, 0x8c,

    /* U+5F "_" */
    0xff, 0xff, 0xc0,

    /* U+60 "`" */
    0xe7,

    /* U+61 "a" */
    0x3c, 0x7f, 0xe3, 0x3, 0x7f, 0xff, 0xc3, 0xc3,
    0xff, 0x7b,

    /* U+62 "b" */
    0xc0, 0xc0, 0xc0, 0xdc, 0xfe, 0xe7, 0xc3, 0xc3,
    0xc3, 0xc3, 0xe7, 0xfe, 0xdc,

    /* U+63 "c" */
    0x3c, 0x7e, 0xe3, 0xc3, 0xc0, 0xc0, 0xc3, 0xe3,
    0x7e, 0x3c,

    /* U+64 "d" */
    0x3, 0x3, 0x3, 0x7b, 0x7f, 0xe7, 0xc3, 0xc3,
    0xc3, 0xc3, 0xe7, 0x7f, 0x7b,

    /* U+65 "e" */
    0x3c, 0x7e, 0xc3, 0xc3, 0xff, 0xff, 0xc0, 0xc3,
    0x7e, 0x3c,

    /* U+66 "f" */
    0xf, 0x8f, 0xc6, 0x3, 0xf, 0xff, 0xfc, 0x60,
    0x30, 0x18, 0xc, 0x6, 0x3, 0x1, 0x80,

    /* U+67 "g" */
    0x7b, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xff,
    0x7b, 0x3, 0x3, 0x7f, 0x7c,

    /* U+68 "h" */
    0xc0, 0xc0, 0xc0, 0xde, 0xff, 0xe7, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+69 "i" */
    0x18, 0xc, 0x0, 0x0, 0xf, 0x87, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x6, 0x3, 0xf, 0xff, 0xfc,

    /* U+6A "j" */
    0x7, 0x7, 0x0, 0x0, 0x7f, 0x7f, 0x3, 0x3,
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0xfe,
    0xfc,

    /* U+6B "k" */
    0xc0, 0x60, 0x30, 0x18, 0x6c, 0x76, 0x73, 0x31,
    0xf8, 0xfc, 0x66, 0x33, 0x98, 0xec, 0x30,

    /* U+6C "l" */
    0xfc, 0x1f, 0x80, 0x30, 0x6, 0x0, 0xc0, 0x18,
    0x3, 0x0, 0x60, 0xc, 0x1, 0x80, 0x30, 0x7,
    0xf0, 0x7e,

    /* U+6D "m" */
    0xf3, 0x7f, 0xf6, 0x7b, 0x3d, 0x9e, 0xcf, 0x67,
    0xb3, 0xd9, 0xec, 0xc0,

    /* U+6E "n" */
    0xde, 0xff, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3,

    /* U+6F "o" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7,
    0x7e, 0x3c,

    /* U+70 "p" */
    0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7,
    0xfe, 0xdc, 0xc0, 0xc0, 0xc0,

    /* U+71 "q" */
    0x7b, 0x7f, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7,
    0x7f, 0x7b, 0x3, 0x3, 0x3,

    /* U+72 "r" */
    0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0,

    /* U+73 "s" */
    0x7e, 0xff, 0xc3, 0xc0, 0x7c, 0x1f, 0x3, 0xc3,
    0xff, 0x7e,

    /* U+74 "t" */
    0x18, 0xc, 0x6, 0x1f, 0xff, 0xf8, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x6, 0x3, 0xf0, 0xf8,

    /* U+75 "u" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7,
    0x7e, 0x3c,

    /* U+76 "v" */
    0xc1, 0xe1, 0xd8, 0xcc, 0x66, 0x73, 0xb0, 0xd8,
    0x6c, 0x3c, 0xe, 0x0,

    /* U+77 "w" */
    0xcc, 0x53, 0xb6, 0xad, 0xab, 0x6a, 0xda, 0xb6,
    0xa9, 0xea, 0x33, 0x8c, 0xe0,

    /* U+78 "x" */
    0xe3, 0xb3, 0x8d, 0x87, 0xc1, 0xc0, 0xe0, 0xf8,
    0xec, 0x63, 0x71, 0xc0,

    /* U+79 "y" */
    0xc1, 0xf1, 0xd8, 0xcc, 0x67, 0x61, 0xb0, 0xd8,
    0x38, 0x1c, 0xe, 0x6, 0x3, 0x3, 0x80,

    /* U+7A "z" */
    0xff, 0xff, 0x7, 0xe, 0x1c, 0x38, 0x70, 0xe0,
    0xff, 0xff,

    /* U+7B "{" */
    0x7, 0x87, 0xc3, 0x1, 0x80, 0xc0, 0x60, 0x30,
    0x18, 0xf8, 0x7c, 0x3, 0x1, 0x80, 0xc0, 0x60,
    0x30, 0x1f, 0x7, 0x80,

    /* U+7C "|" */
    0xff, 0xff, 0xff, 0xff, 0xc0,

    /* U+7D "}" */
    0xe0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x1f, 0x1f, 0x30, 0x30, 0x30, 0x30, 0x30, 0xf0,
    0xe0,

    /* U+7E "~" */
    0x71, 0xfc, 0xf3, 0xf8, 0xe0,

    /* U+410 "А" */
    0x1c, 0xe, 0xf, 0x6, 0xc3, 0x61, 0xb1, 0x9c,
    0xc6, 0x7f, 0x7f, 0xb8, 0xf8, 0x7c, 0x18,

    /* U+411 "Б" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xfc, 0xfe, 0xc7,
    0xc3, 0xc3, 0xc7, 0xfe, 0xfc,

    /* U+412 "В" */
    0xfc, 0xff, 0xc3, 0xc3, 0xc3, 0xfe, 0xfe, 0xc7,
    0xc3, 0xc3, 0xc7, 0xfe, 0xfc,

    /* U+413 "Г" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0,

    /* U+414 "Д" */
    0x3f, 0x8f, 0xe3, 0x18, 0xc6, 0x31, 0x8c, 0x63,
    0x18, 0xc6, 0x31, 0x8c, 0x66, 0x1b, 0xff, 0xff,
    0xf0, 0x3c, 0xc,

    /* U+415 "Е" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xff, 0xff, 0xc0,
    0xc0, 0xc0, 0xc0, 0xff, 0xff,

    /* U+416 "Ж" */
    0xcc, 0xf3, 0x3c, 0xcd, 0xb6, 0x6d, 0x9b, 0x63,
    0xf1, 0xb6, 0x6d, 0x9b, 0x6c, 0xcf, 0x33, 0xcc,
    0xc0,

    /* U+417 "З" */
    0x3e, 0x3f, 0xd8, 0x60, 0x30, 0x38, 0xf0, 0x7c,
    0x7, 0x1, 0xb0, 0xd8, 0xef, 0xe3, 0xe0,

    /* U+418 "И" */
    0xc7, 0xc7, 0xcf, 0xcf, 0xcf, 0xdb, 0xdb, 0xdb,
    0xf3, 0xf3, 0xf3, 0xe3, 0xe3,

    /* U+419 "Й" */
    0x66, 0x7e, 0x3c, 0x0, 0xc7, 0xc7, 0xcf, 0xcf,
    0xcf, 0xdb, 0xdb, 0xdb, 0xf3, 0xf3, 0xf3, 0xe3,
    0xe3,

    /* U+41A "К" */
    0xc3, 0x63, 0xb1, 0x99, 0xcc, 0xc7, 0xe3, 0xf1,
    0x98, 0xce, 0x63, 0x31, 0xd8, 0xec, 0x30,

    /* U+41B "Л" */
    0x3f, 0x9f, 0xcc, 0x66, 0x33, 0x19, 0x8c, 0xc6,
    0x63, 0x31, 0x98, 0xcc, 0x7c, 0x3c, 0x18,

    /* U+41C "М" */
    0xe3, 0xf1, 0xfc, 0xfe, 0xfd, 0x5e, 0xaf, 0x77,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x18,

    /* U+41D "Н" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+41E "О" */
    0x3c, 0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc7, 0x7e, 0x3c,

    /* U+41F "П" */
    0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+420 "Р" */
    0xfe, 0x7f, 0xb0, 0xf8, 0x3c, 0x1e, 0x1f, 0xfd,
    0xfc, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x0,

    /* U+421 "С" */
    0x3c, 0x7e, 0xc3, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc3, 0xc7, 0x7e, 0x3c,

    /* U+422 "Т" */
    0xff, 0xff, 0xc3, 0x1, 0x80, 0xc0, 0x60, 0x30,
    0x18, 0xc, 0x6, 0x3, 0x1, 0x80, 0xc0,

    /* U+423 "У" */
    0xc1, 0xf1, 0xd8, 0xcc, 0x67, 0x71, 0xb0, 0xd8,
    0x38, 0x1c, 0xe, 0x6, 0x3, 0x3, 0x80,

    /* U+424 "Ф" */
    0xc, 0xf, 0xc7, 0xfb, 0xb7, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33, 0xcc, 0xf3, 0x3e, 0xdd, 0xfe, 0x3f,
    0x3, 0x0,

    /* U+425 "Х" */
    0x61, 0xcc, 0x63, 0x38, 0x6c, 0x1f, 0x3, 0x80,
    0xe0, 0x38, 0x1f, 0xe, 0xc3, 0x39, 0xc6, 0x60,
    0xc0,

    /* U+426 "Ц" */
    0xc6, 0x63, 0x31, 0x98, 0xcc, 0x66, 0x33, 0x19,
    0x8c, 0xc6, 0x63, 0x31, 0x9f, 0xff, 0xf8, 0xc,
    0x6,

    /* U+427 "Ч" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe3, 0x7f, 0x3f,
    0x3, 0x3, 0x3, 0x3, 0x3,

    /* U+428 "Ш" */
    0xd9, 0xec, 0xf6, 0x7b, 0x3d, 0x9e, 0xcf, 0x67,
    0xb3, 0xd9, 0xec, 0xf6, 0x7f, 0xff, 0xf8,

    /* U+429 "Щ" */
    0xd9, 0xb6, 0x6d, 0x9b, 0x66, 0xd9, 0xb6, 0x6d,
    0x9b, 0x66, 0xd9, 0xb6, 0x6d, 0x9b, 0xff, 0xff,
    0xc0, 0x30, 0xc,

    /* U+42A "Ъ" */
    0xf0, 0x3c, 0x3, 0x0, 0xc0, 0x30, 0xf, 0xc3,
    0xf8, 0xc7, 0x30, 0xcc, 0x33, 0x1c, 0xfe, 0x3f,
    0x0,

    /* U+42B "Ы" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xcf, 0xf7,
    0x9b, 0xcd, 0xe6, 0xf3, 0x7f, 0xbf, 0x98,

    /* U+42C "Ь" */
    0xc0, 0x60, 0x30, 0x18, 0xc, 0x7, 0xf3, 0xfd,
    0x87, 0xc1, 0xe0, 0xf0, 0xff, 0xef, 0xe0,

    /* U+42D "Э" */
    0x3c, 0x7e, 0xe3, 0xc3, 0x3, 0x3f, 0x3f, 0x3,
    0x3, 0xc3, 0xe7, 0x7e, 0x3c,

    /* U+42E "Ю" */
    0xcf, 0x6f, 0xf6, 0x7b, 0x3d, 0x9f, 0xcf, 0xe7,
    0xb3, 0xd9, 0xec, 0xf6, 0x7b, 0xfc, 0xf0,

    /* U+42F "Я" */
    0x3f, 0x7f, 0xe3, 0xc3, 0xc3, 0xe3, 0x7f, 0x3f,
    0x33, 0x73, 0x63, 0xe3, 0xc3,

    /* U+430 "а" */
    0x3c, 0x7f, 0xe3, 0x3, 0x7f, 0xff, 0xc3, 0xc3,
    0xff, 0x7b,

    /* U+431 "б" */
    0x3f, 0x7f, 0xe0, 0xc0, 0xde, 0xfe, 0xe7, 0xc3,
    0xc3, 0xc3, 0xe7, 0x7e, 0x3c,

    /* U+432 "в" */
    0xfe, 0xff, 0xc3, 0xc3, 0xfe, 0xfe, 0xc3, 0xc3,
    0xff, 0xfe,

    /* U+433 "г" */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0,

    /* U+434 "д" */
    0x3f, 0x8f, 0xe3, 0x18, 0xc6, 0x31, 0x8c, 0x63,
    0x19, 0x86, 0xff, 0xff, 0xfc, 0xf, 0x3,

    /* U+435 "е" */
    0x3c, 0x7e, 0xc3, 0xc3, 0xff, 0xff, 0xc0, 0xc3,
    0x7e, 0x3c,

    /* U+436 "ж" */
    0xcc, 0xf3, 0x36, 0xd9, 0xb6, 0x3f, 0x1b, 0x66,
    0xdb, 0x33, 0xcc, 0xf3, 0x30,

    /* U+437 "з" */
    0x3f, 0x3f, 0xd8, 0x60, 0x31, 0xf0, 0xf8, 0x7,
    0xc3, 0x7f, 0x9f, 0x80,

    /* U+438 "и" */
    0xc7, 0xc7, 0xcf, 0xcf, 0xdb, 0xdb, 0xf3, 0xf3,
    0xe3, 0xe3,

    /* U+439 "й" */
    0x66, 0x7e, 0x3c, 0x0, 0xc7, 0xc7, 0xcf, 0xcf,
    0xdb, 0xdb, 0xf3, 0xf3, 0xe3, 0xe3,

    /* U+43A "к" */
    0xc3, 0xc7, 0xce, 0xcc, 0xfc, 0xfc, 0xcc, 0xce,
    0xc7, 0xc3,

    /* U+43B "л" */
    0x3f, 0x9f, 0xcc, 0x66, 0x33, 0x19, 0x8c, 0xc6,
    0x63, 0xf1, 0xf0, 0xc0,

    /* U+43C "м" */
    0xe3, 0xf1, 0xfd, 0xfe, 0xfd, 0x5e, 0xaf, 0x77,
    0x83, 0xc1, 0xe0, 0xc0,

    /* U+43D "н" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3,

    /* U+43E "о" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7,
    0x7e, 0x3c,

    /* U+43F "п" */
    0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3,

    /* U+440 "р" */
    0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7,
    0xfe, 0xdc, 0xc0, 0xc0, 0xc0,

    /* U+441 "с" */
    0x3c, 0x7e, 0xe3, 0xc3, 0xc0, 0xc0, 0xc3, 0xe3,
    0x7e, 0x3c,

    /* U+442 "т" */
    0xff, 0xff, 0xc3, 0x1, 0x80, 0xc0, 0x60, 0x30,
    0x18, 0xc, 0x6, 0x0,

    /* U+443 "у" */
    0xc1, 0xf1, 0xd8, 0xcc, 0x67, 0x61, 0xb0, 0xd8,
    0x38, 0x1c, 0xe, 0x6, 0x3, 0x3, 0x80,

    /* U+444 "ф" */
    0xc, 0x3, 0x0, 0xc0, 0xfc, 0x7f, 0xbb, 0x7c,
    0xcf, 0x33, 0xcc, 0xf3, 0x3e, 0xdd, 0xfe, 0x3f,
    0x3, 0x0, 0xc0, 0x30,

    /* U+445 "х" */
    0xe3, 0xb3, 0x8d, 0x87, 0xc1, 0xc0, 0xe0, 0xf8,
    0xec, 0x63, 0x71, 0xc0,

    /* U+446 "ц" */
    0xc6, 0x63, 0x31, 0x98, 0xcc, 0x66, 0x33, 0x19,
    0x8c, 0xff, 0xff, 0xc0, 0x60, 0x30,

    /* U+447 "ч" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xe3, 0x7f, 0x3f, 0x3,
    0x3, 0x3,

    /* U+448 "ш" */
    0xd9, 0xec, 0xf6, 0x7b, 0x3d, 0x9e, 0xcf, 0x67,
    0xb3, 0xff, 0xff, 0xc0,

    /* U+449 "щ" */
    0xd9, 0xb6, 0x6d, 0x9b, 0x66, 0xd9, 0xb6, 0x6d,
    0x9b, 0x66, 0xff, 0xff, 0xf0, 0xc, 0x3,

    /* U+44A "ъ" */
    0xf8, 0x1f, 0x0, 0x60, 0xf, 0xc1, 0xfc, 0x30,
    0xc6, 0x18, 0xc3, 0x1f, 0xc3, 0xf0,

    /* U+44B "ы" */
    0xc1, 0xe0, 0xf0, 0x7f, 0x3f, 0x9e, 0x6f, 0x37,
    0x9b, 0xfd, 0xfc, 0xc0,

    /* U+44C "ь" */
    0xc0, 0x60, 0x30, 0x1f, 0xcf, 0xf6, 0xf, 0x7,
    0x83, 0xff, 0x7f, 0x0,

    /* U+44D "э" */
    0x3c, 0x7e, 0xc3, 0x3, 0x1f, 0x1f, 0x3, 0xc3,
    0x7e, 0x3c,

    /* U+44E "ю" */
    0xcf, 0x6f, 0xf6, 0x7b, 0x3f, 0x9f, 0xcf, 0x67,
    0xb3, 0xdf, 0xe7, 0x80,

    /* U+44F "я" */
    0x3f, 0x7f, 0xc3, 0xc3, 0xc3, 0xff, 0x3f, 0x73,
    0x63, 0xe3
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 173, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 173, .box_w = 3, .box_h = 13, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 173, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 10, .adv_w = 173, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 173, .box_w = 8, .box_h = 18, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 45, .adv_w = 173, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 173, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 173, .box_w = 2, .box_h = 5, .ofs_x = 4, .ofs_y = 8},
    {.bitmap_index = 82, .adv_w = 173, .box_w = 6, .box_h = 17, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 95, .adv_w = 173, .box_w = 6, .box_h = 17, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 108, .adv_w = 173, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 120, .adv_w = 173, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 129, .adv_w = 173, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 132, .adv_w = 173, .box_w = 6, .box_h = 2, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 134, .adv_w = 173, .box_w = 3, .box_h = 3, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 173, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 156, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 173, .box_w = 3, .box_h = 10, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 173, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 307, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 317, .adv_w = 173, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 323, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 333, .adv_w = 173, .box_w = 7, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 173, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 365, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 445, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 583, .adv_w = 173, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 599, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 627, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 642, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 655, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 173, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 687, .adv_w = 173, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 173, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 173, .box_w = 5, .box_h = 17, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 745, .adv_w = 173, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 765, .adv_w = 173, .box_w = 5, .box_h = 17, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 776, .adv_w = 173, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 784, .adv_w = 173, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 787, .adv_w = 173, .box_w = 4, .box_h = 2, .ofs_x = 3, .ofs_y = 12},
    {.bitmap_index = 788, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 798, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 811, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 821, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 834, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 844, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 859, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 872, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 885, .adv_w = 173, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 901, .adv_w = 173, .box_w = 8, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 918, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 933, .adv_w = 173, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 951, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 963, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 973, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 983, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 996, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1009, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1019, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1029, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1044, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1054, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1066, .adv_w = 173, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1079, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1091, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1106, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1116, .adv_w = 173, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1136, .adv_w = 173, .box_w = 2, .box_h = 17, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 1141, .adv_w = 173, .box_w = 8, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1158, .adv_w = 173, .box_w = 9, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1163, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1178, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1191, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1204, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1217, .adv_w = 173, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1236, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1249, .adv_w = 173, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1266, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1281, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1294, .adv_w = 173, .box_w = 8, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1311, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1326, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1341, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1356, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1369, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1382, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1395, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1410, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1423, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1438, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1453, .adv_w = 173, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1471, .adv_w = 173, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1488, .adv_w = 173, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1505, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1518, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1533, .adv_w = 173, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1552, .adv_w = 173, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1569, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1584, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1599, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1612, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1627, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1640, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1650, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1663, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1673, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1683, .adv_w = 173, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1698, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1708, .adv_w = 173, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1721, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1733, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1743, .adv_w = 173, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1757, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1767, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1779, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1791, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1801, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1811, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1821, .adv_w = 173, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1834, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1844, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1856, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1871, .adv_w = 173, .box_w = 10, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1891, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1903, .adv_w = 173, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1917, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1927, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1939, .adv_w = 173, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1954, .adv_w = 173, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1968, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1980, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1992, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2002, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2014, .adv_w = 173, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0}
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
lv_font_t San_Francisco_Bold_18 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 20,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -3,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if SAN_FRANCISCO_BOLD_18*/

