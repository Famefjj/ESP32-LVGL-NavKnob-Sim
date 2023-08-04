#include "../lv_examples.h"
#include "../../../lv_drivers/win32drv/win32drv.h"

#if LV_BUILD_EXAMPLES && LV_USE_BTN

lv_group_t* g;

/**
 * Create a button with a label and react on click event.
 */
 lv_obj_t* label1;
 lv_obj_t* label2;
 lv_obj_t* obj;
 lv_obj_t* btn;
 lv_obj_t* label_btn;
 lv_obj_t* prompt_obj;
 lv_obj_t* prompt;
 lv_obj_t* spinner;
 lv_timer_t* timer;
 bool is_null;
 bool is_reached = false;

char *dest[] = {"Living room", "Bedroom", "Bathroom", "Kitchen"};

void encoder_event_handler(lv_event_t* e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
//        lv_obj_clean(lv_scr_act());
        if (!is_null && !is_reached)
        {
            lv_timer_del(timer);
        }
//        background_blur();
        prompt_user();
//        lv_example_get_started_new();
    }
}

//void prompt_handler()
void prompt_cb(lv_event_t* e)
{
    lv_group_add_obj(g, btn);
    lv_obj_t* prompt_obj = lv_event_get_current_target(e);
    char* s = lv_msgbox_get_active_btn_text(prompt_obj);
    LV_LOG_USER("Button %s clicked", s);
    if (s == "YES")
    {
        lv_msgbox_close(prompt);
        lv_obj_clean(lv_scr_act());
        lv_example_get_started_new();
    }
    else if (s == "NO")
    {
        lv_msgbox_close(prompt);
    }

}

void prompt_user(void)
{
    static const char* btns[] = {"NO", "YES", ""};

    //create prompt
    lv_group_remove_obj(btn);
    prompt = lv_msgbox_create(NULL, "","Are you sure to change destination?", btns, false);
    lv_obj_set_width(prompt, 200);
    lv_obj_center(prompt);
    lv_group_add_obj(g, prompt);
    lv_group_set_editing(g, true);

    lv_obj_add_event_cb(prompt, prompt_cb, LV_EVENT_VALUE_CHANGED, NULL);
}

void lv_encoder(void)
{
    g = lv_group_create();
    lv_group_set_default(g);

    lv_indev_t* cur_drv = NULL;
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

void dest_reached(void)
{
    is_reached = true;
    lv_obj_t* arc = lv_arc_create(lv_scr_act());
    lv_arc_set_value(arc, 360);
    lv_arc_set_bg_angles(arc,0,360);
    lv_obj_remove_style(arc,NULL,LV_PART_KNOB);
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_center(arc);
    lv_obj_set_size(arc, 400, 400);

    lv_color_t c = lv_color_make(3, 192, 60);
    lv_obj_set_style_arc_color(arc,c, LV_PART_INDICATOR);

    //change label
    lv_label_set_text(label1, "Destination reached !");

}

void my_timer(lv_timer_t* timer)
{
    lv_group_remove_obj(spinner);
    lv_timer_del(timer);
    dest_reached();
}

void create_loading(int i)
{
    if (i !=-1)
    {
        spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
        lv_obj_set_size(spinner, 400, 400);
        lv_obj_center(spinner);

        static uint32_t user_data = 10;
        timer = lv_timer_create(my_timer, 5000, &user_data);
    }
}

void lv_mainpage(int i)
{
    lv_encoder();

    //setup base obj
    obj = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj, 400, 400);
    lv_obj_set_align(obj, LV_ALIGN_CENTER);
    lv_obj_set_pos(obj, 0, 0);

    //setup label1
    label1 = lv_label_create(obj);
    lv_label_set_text(label1, "Current Destination");
    lv_obj_align_to(label1,obj, LV_ALIGN_CENTER, 0, -40);

    //setup label2
    label2 = lv_label_create(obj);
    (i!=-1) ?  lv_label_set_text(label2, dest[i]) : lv_label_set_text(label2, "NONE");
    lv_obj_align_to(label2,obj, LV_ALIGN_CENTER, 0, 0);

    //setup button
    btn = lv_btn_create(lv_scr_act());
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 60);
    lv_obj_set_size(btn, 100, 30);

    label_btn = lv_label_create(btn);
    lv_label_set_text(label_btn, "Select");
    lv_obj_center(label_btn);

    create_loading(i);
    is_null = (i == -1) ? true : false;
    lv_obj_add_event_cb(btn, encoder_event_handler, LV_EVENT_ALL, NULL);
}



#endif
