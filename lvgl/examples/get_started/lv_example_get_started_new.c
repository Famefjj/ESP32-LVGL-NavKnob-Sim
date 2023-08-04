#include "../lv_examples.h"

#if LV_USE_ROLLER && LV_BUILD_EXAMPLES
lv_obj_t* roller;
lv_obj_t* obj;
extern lv_group_t* g;

static void event_handler(lv_event_t* e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED){
        int index = lv_roller_get_selected(obj);
//        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected month: %d \n", index);
        lv_obj_clean(lv_scr_act());
        lv_mainpage(index);
    }
}

/**
 * Create a button with a label and react on click event.
 */

void lv_example_get_started_new(void)
{
    lv_encoder();

    // setup base object
    roller = lv_roller_create(lv_scr_act());
    lv_roller_set_options(roller,
                         "Living room\n"
                         "Bedroom\n"
                         "Bathroom\n"
                         "Kitchen",
                         LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(roller, 4);
    lv_obj_center(roller);
    lv_group_set_editing(g, true);
    lv_obj_add_event_cb(roller, event_handler, LV_EVENT_ALL, NULL);
}



#endif

