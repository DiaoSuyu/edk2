#include "../../lv_examples.h"
#if LV_USE_FLEX && LV_BUILD_EXAMPLES

/**
 * Reverse the order of flex items
 */
void lv_example_flex_4(void)
{

    lv_obj_t * cont = lv_obj_create(lv_screen_active());
    lv_obj_set_size(cont, 300, 220);
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN_REVERSE);

    uint32_t i;
    for(i = 0; i < 6; i++) {
        lv_obj_t * obj = lv_obj_create(cont);
        lv_obj_set_size(obj, 100, 50);

        lv_obj_t * label = lv_label_create(obj);
        // <Sam_Diao20250607+>
        // Fix build error
        #if defined(REMOVE_LVGL_ORIGINAL_SETTING) && (REMOVE_LVGL_ORIGINAL_SETTING == 1)
        lv_label_set_text_fmt(label, "%u", i);
        #else
        lv_label_set_text_fmt(label, "%" LV_PRIu32, i);
        #endif
        // <Sam_Diao20250607->
        lv_obj_center(label);
    }
}

#endif
