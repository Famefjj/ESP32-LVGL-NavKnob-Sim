
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <unistd.h>

#include "lvgl/lvgl.h"
#include "lvgl/demos/widgets/lv_demo_widgets.h"
#include "lv_drivers/win32drv/win32drv.h"
#include "lvgl/examples/lv_examples.h"

#include <windows.h>


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);
static int tick_thread(void *data);

/**********************
 *  STATIC VARIABLES
 **********************/
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;
static lv_group_t *lv_group;
static lv_obj_t *lv_btn_1;
static lv_obj_t *lv_btn_2;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL for LittlevGL*/
    lv_win32_init(hInstance, SW_SHOWNORMAL, 480, 480, NULL);

    /*Output prompt information to the console, you can also use printf() to print directly*/
    LV_LOG_USER("LVGL initialization completed!");

    /*Run the demo*/
    // lv_demo_widgets();
    //lv_example_get_started_new();

    //ben10_mainpage();

    lv_mainpage(-1);


    while(!lv_win32_quit_signal) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(10000);       /*Just to let the system breath*/
    }
    return 0;
}
