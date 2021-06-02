/**
 * @file lv_watch_theme.h
 *
 */

#ifndef LV_WATCH_THEME_H
#define LV_WATCH_THEME_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <lvgl/lvgl.h>

/*********************
 *      DEFINES
 *********************/
/*Colors*/
#define LV_WATCH_WHITE      lv_color_hex(0xffffff)
#define LV_WATCH_LIGHT      lv_color_hex(0xf3f8fe)
#define LV_WATCH_GRAY       lv_color_hex(0x8a8a8a)
#define LV_WATCH_LIGHT_GRAY lv_color_hex(0xc4c4c4)
#define LV_WATCH_BLUE       lv_color_hex(0x2f3243) // 006fb6
#define LV_WATCH_GREEN      lv_color_hex(0x4cb242)
#define LV_WATCH_RED        lv_color_hex(0xd51732)
#define LV_CHARGING_GRAY    lv_color_hex(0x302E2C)
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the default
 * @param color_primary the primary color of the theme
 * @param color_secondary the secondary color for the theme
 * @param flags ORed flags starting with `LV_THEME_DEF_FLAG_...`
 * @param font_small pointer to a small font
 * @param font_normal pointer to a normal font
 * @param font_subtitle pointer to a large font
 * @param font_title pointer to a extra large font
 * @return a pointer to reference this theme later
 */
lv_theme_t* lv_watch_theme_init(lv_color_t color_primary,
                                   lv_color_t color_secondary,
                                   uint32_t flags,
                                   const lv_font_t* font_small,
                                   const lv_font_t* font_normal,
                                   const lv_font_t* font_subtitle,
                                   const lv_font_t* font_title);
/**********************
 *      MACROS
 **********************/

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
