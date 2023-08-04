#include "../lv_examples.h"

#if LV_USE_ROLLER && LV_BUILD_EXAMPLES

lv_obj_t* obj;
lv_obj_t* img3;
extern lv_group_t* g;
extern lv_indev_data_t* my_data;
extern void ben10_encoder(void);
extern const lv_img_dsc_t omnitrix_main;
extern const lv_img_dsc_t omnitrix_animal3;
extern lv_indev_t* cur_drv;


static void event_handler(lv_event_t* e){
    lv_event_code_t code = lv_event_get_code(e);
    obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED){
//        char buf[16];
//        lv_roller_get_selected_str(obj, buf, sizeof(buf));
//        LV_LOG_USER("elected month: %s\n", buf);

        lv_obj_clean(lv_scr_act());
        ben10_mainpage();

    }
}

static void scroll_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code != LV_EVENT_CLICKED && my_data->enc_diff == -1 && code == LV_EVENT_VALUE_CHANGED)
    {
        LV_LOG_USER("%d\n", my_data->enc_diff);
        lv_obj_clean(lv_scr_act());
        ben10_animal1();
    }
    else if (code != LV_EVENT_CLICKED && my_data->enc_diff == 1 && code == LV_EVENT_VALUE_CHANGED)
    {
        LV_LOG_USER("%d\n", my_data->enc_diff);
        lv_obj_clean(lv_scr_act());
        ben10_animal2();
    }
    else if (code == LV_EVENT_CLICKED)
    {
        lv_obj_clean(lv_scr_act());
        ben10_mainpage();
    }
}

/**
 * Create a button with a label and react on click event.
 */



void ben10_animal3(void)
{
    ben10_encoder();
    //create background
    /*===================== image 1 =========================*/
    //create button and set opacity
    //ben10 animal1
    img3 = lv_img_create(lv_scr_act());
    lv_img_set_src(img3, &omnitrix_animal3);
    lv_obj_align(img3, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(img3,480,480);
    /*======================================================*/

    lv_obj_add_flag(img3, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img3, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(img3, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(img3, LV_OBJ_FLAG_CHECKABLE);

    lv_group_add_obj(g, img3);

    lv_group_set_editing(g, true);

    lv_obj_add_event_cb(img3, scroll_event_handler, LV_EVENT_ALL, NULL);
}



#endif

