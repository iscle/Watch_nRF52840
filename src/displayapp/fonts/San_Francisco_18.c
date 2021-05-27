/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef SAN_FRANCISCO_18
#define SAN_FRANCISCO_18 1
#endif

#if SAN_FRANCISCO_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+004D "M" */
    0xe0, 0x3f, 0x1, 0xf8, 0xf, 0xe0, 0xfd, 0x5,
    0xec, 0x6f, 0x22, 0x79, 0x13, 0xcd, 0x9e, 0x28,
    0xf1, 0xc7, 0x84, 0x30,

    /* U+004E "N" */
    0xc0, 0xf8, 0x3f, 0xf, 0x43, 0xd8, 0xf2, 0x3c,
    0x4f, 0x1b, 0xc2, 0xf0, 0xfc, 0x1f, 0x3,

    /* U+0055 "U" */
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x36, 0x18, 0xfc,

    /* U+0061 "a" */
    0x3e, 0x67, 0xc3, 0x3, 0x7f, 0xc3, 0xc3, 0xc7,
    0x7b,

    /* U+0063 "c" */
    0x3e, 0x31, 0xb0, 0x58, 0xc, 0x6, 0x3, 0x4,
    0xc6, 0x3e, 0x0,

    /* U+0064 "d" */
    0x1, 0x80, 0xc0, 0x67, 0xb6, 0x3e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xd8, 0xe7, 0xb0,

    /* U+0065 "e" */
    0x3c, 0x66, 0xc3, 0xc3, 0xff, 0xc0, 0xc0, 0x66,
    0x3c,

    /* U+0066 "f" */
    0x3b, 0x19, 0xf6, 0x31, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0069 "i" */
    0xf3, 0xff, 0xff,

    /* U+006C "l" */
    0xff, 0xff, 0xff,

    /* U+006F "o" */
    0x3e, 0x31, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x6,
    0xc6, 0x3e, 0x0,

    /* U+0072 "r" */
    0xff, 0x31, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0073 "s" */
    0x7d, 0x9f, 0x7, 0x7, 0xc1, 0xc1, 0xe3, 0x7c,

    /* U+0074 "t" */
    0x63, 0x3e, 0xc6, 0x31, 0x8c, 0x63, 0xe
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 59, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 239, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 201, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 201, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 145, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 144, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 159, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 148, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 87, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 59, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 59, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 153, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 89, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 87, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x2d, 0x2e, 0x35, 0x41, 0x43, 0x44, 0x45,
    0x46, 0x49, 0x4c, 0x4f, 0x52, 0x53, 0x54
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 85, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 15, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t San_Francisco_18 = {
#else
lv_font_t San_Francisco_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -4,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if SAN_FRANCISCO_18*/
