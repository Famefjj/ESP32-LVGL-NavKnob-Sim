#include "../lv_examples.h"
#include "../../../lv_drivers/win32drv/win32drv.h"

#if LV_BUILD_EXAMPLES && LV_USE_BTN

lv_group_t* g;
extern const lv_img_dsc_t omnitrix_main;
lv_obj_t* btn;
lv_obj_t* icon;
lv_indev_t* cur_drv;

/**
 * Create a button with a label and react on click event.
 */

void ben10_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);
//    LV_LOG_USER("main page: %d\n", code);

    if (code == LV_EVENT_CLICKED)
    {
        lv_obj_clean(lv_scr_act());
        ben10_animal1();
    }

}

void ben10_encoder(void)
{
    g = lv_group_create();
    lv_group_set_default(g);

    cur_drv = NULL;
    while(true)
    {
        cur_drv = lv_indev_get_next(cur_drv);
        if (!cur_drv){
            break;
        }
        if(cur_drv->driver->type == LV_INDEV_TYPE_ENCODER)
        {
            lv_indev_set_group(cur_drv, g);
        }
    }
}


void ben10_mainpage(void)
{
    lv_encoder();

    //create background
    lv_obj_t* obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj, 480,480);
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);

    //create button and set opacity
    lv_obj_t* btn = lv_btn_create(obj);
    lv_obj_set_size(btn,480,480);
    lv_obj_set_style_opa(btn, 255, 0);
    lv_obj_align_to(btn, obj, LV_ALIGN_CENTER, 0, 0);


    //ben10 main image
    lv_obj_t* icon = lv_img_create(btn);
    lv_img_set_src(icon, &omnitrix_main);
    lv_obj_align_to(icon, btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(icon,480,480);

    lv_obj_add_event_cb(btn, ben10_event_handler, LV_EVENT_ALL, NULL);

}



#endif
