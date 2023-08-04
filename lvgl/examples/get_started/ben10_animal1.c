#include "../lv_examples.h"

#if LV_USE_ROLLER && LV_BUILD_EXAMPLES

lv_obj_t* img1;


extern lv_group_t* g;

extern void ben10_encoder(void);
extern const lv_img_dsc_t omnitrix_animal1;
extern lv_indev_t* cur_drv;

lv_indev_data_t* my_dev;

static void scroll_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
//    char c = *((char*)lv_event_get_param(e));

//    int* key = (int*)lv_indev_get_key(lv_indev_get_act());
    if (code != LV_EVENT_CLICKED && my_dev->enc_diff == -1 && code == LV_EVENT_VALUE_CHANGED)
    {
        LV_LOG_USER("%d\n", my_dev->enc_diff);
        lv_obj_clean(lv_scr_act());
        ben10_animal2();
    }
    else if (code != LV_EVENT_CLICKED && my_dev->enc_diff == 1 && code == LV_EVENT_VALUE_CHANGED)
    {
        LV_LOG_USER("%d\n", my_dev->enc_diff);
        lv_obj_clean(lv_scr_act());
        ben10_animal3();
    }
    else if (code == LV_EVENT_CLICKED)
    {
        lv_obj_clean(lv_scr_act());
        ben10_mainpage();
    }

//        LV_LOG_USER("HELLO\n");
}

/**
 * Create a button with a label and react on click event.
 */

void ben10_animal1(void)
{
    ben10_encoder();

    /*===================== image 1 =========================*/
    //create button and set opacity
    //ben10 animal1
    img1 = lv_img_create(lv_scr_act());
    lv_img_set_src(img1, &omnitrix_animal1);
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(img1,480,480);
    /*======================================================*/

    lv_obj_add_flag(img1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(img1, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_add_flag(img1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(img1, LV_OBJ_FLAG_CHECKABLE);

    lv_group_add_obj(g, img1);
    lv_group_set_editing(g, true);


    lv_obj_add_event_cb(img1, scroll_event_handler, LV_EVENT_ALL, NULL);
}



#endif

