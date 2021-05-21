#include "lvgl/lvgl.h"



#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_BATTERY_05
#define LV_ATTRIBUTE_IMG_BATTERY_05
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BATTERY_05 uint8_t arrowleft_map[] = {
  0x0f, 0x0e, 0x0f, 0xff, 	/*Color of index 0*/
  0xd0, 0xcf, 0xd0, 0xff, 	/*Color of index 1*/

  0x01, 
  0x10, 
  0x18, 
  0x0c, 
  0x0c, 
  0x18, 
  0x10, 
  0x01, 
};

const lv_img_dsc_t arrowleft = {
    {
       LV_IMG_CF_INDEXED_1BIT,
        0,
        0,
        8,
        8
    },
   16,
    arrowleft_map
};


