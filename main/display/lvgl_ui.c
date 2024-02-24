/**
 ******************************************************************************
 *							USEFUL ELECTRONICS
 ******************************************************************************/
/**
 ******************************************************************************
 * @file    :  lvgl_ui.c
 * @author  :  WARD ALMASARANI
 * @version :  v.1.0
 * @date    :  Feb 6, 2024
 * @link    :  https://www.youtube.com/@usefulelectronics
 *			   Hold Ctrl button and click on the link to be directed to
			   Useful Electronics YouTube channel	
 ******************************************************************************/


/* INCLUDES ------------------------------------------------------------------*/
#include "lvgl_ui.h"

#include <math.h>
#include <stdio.h>
LV_IMG_DECLARE(ui_img_ue_logo_png)
LV_IMG_DECLARE(ui_img_ue_logo_png_large)
LV_FONT_DECLARE(ui_font_SS52);
/* PRIVATE STRUCTRES ---------------------------------------------------------*/
typedef struct
{
    lv_obj_t *scr;
    int count_val;
} my_timer_context_t;
/* VARIABLES -----------------------------------------------------------------*/
static my_timer_context_t my_tim_ctx;

static lv_color_t arc_color[] =
{
   LV_COLOR_MAKE(0x00, 0x00, 0x00),
   LV_COLOR_MAKE(0x00, 0x00, 0x00),
   LV_COLOR_MAKE(0x00, 0x00, 0x00),
};

lv_obj_t *display;
lv_obj_t *tv1;
lv_obj_t *tv2;

lv_obj_t *label1;
lv_obj_t *label2;
lv_obj_t *img_logo;
lv_obj_t *arc[2];



lv_obj_t * ui_mainScreen;
lv_obj_t * ui_leftPanel;
lv_obj_t * ui_leftSegment;
lv_obj_t * ui_rightPanel;
lv_obj_t * ui_rightSegment;
lv_obj_t * ui_middleSpace;

lv_timer_t *lvgl_ui_timer;

/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/
#define PI  (3.14159f)
/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/
static void lvgl_ui_start_animation(lv_obj_t *scr);
static void lvgl_ui_anim_timer_cb(lv_timer_t *timer);
static void lvgl_ui_count_up_timer_cb(lv_timer_t *timer);
static void lvgl_ui_pause_timer();

static void lvgl_ui_reset_timer();
static void lvgl_ui_create_timer();
static void lvgl_ui_delete_timer();
static void lvgl_ui_counter_update(uint8_t left_panel, uint8_t right_panel);
/* FUNCTION PROTOTYPES -------------------------------------------------------*/
static void lvgl_ui_count_up_timer_cb(lv_timer_t *timer)
{
	static uint8_t firstPart, secondPart;

	my_timer_context_t *timer_ctx = (my_timer_context_t *) timer->user_data;

	timer_ctx->count_val += 4;

    firstPart  = timer_ctx->count_val / 100;
    secondPart = timer_ctx->count_val % 100;

    lvgl_ui_counter_update(firstPart, secondPart);

	if(timer_ctx->count_val <= 0)
	{
		lv_timer_del(timer);
	}

}
static void lvgl_ui_pause_timer()
{
	lv_timer_pause(lvgl_ui_timer);
}
static void lvgl_ui_resume_timer()
{
	lv_timer_resume(lvgl_ui_timer);
}
static void lvgl_ui_reset_timer()
{
	my_timer_context_t *timer_ctx = (my_timer_context_t *) lvgl_ui_timer->user_data;

	timer_ctx->count_val = 0;
}
static void lvgl_ui_create_timer()
{
	memset(&my_tim_ctx, 0, sizeof(my_tim_ctx));

	lvgl_ui_timer = lv_timer_create(lvgl_ui_count_up_timer_cb, 1, &my_tim_ctx);
}
static void lvgl_ui_delete_timer()
{
	lv_timer_del(lvgl_ui_timer);
	lvgl_ui_timer = NULL;
}


static void lvgl_ui_anim_timer_cb(lv_timer_t *timer)
{
    my_timer_context_t *timer_ctx = (my_timer_context_t *) timer->user_data;
    int count = timer_ctx->count_val;

    // Play arc animation
    if (count < 90)
    {
        lv_coord_t arc_start = count > 0 ? (1 - cosf(count / 180.0f * PI)) * 270 : 0;
        lv_coord_t arc_len = (sinf(count / 180.0f * PI) + 1) * 135;

        for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++) {
            lv_arc_set_bg_angles(arc[i], arc_start, arc_len);
            lv_arc_set_rotation(arc[i], (count + 120 * (i + 1)) % 360);
        }
    }

    // Delete arcs when animation finished
    if (count == 90)
    {
        for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++)
        {
            lv_obj_del(arc[i]);
        }

        // Create new image and make it transparent

//        lv_img_set_src(label2, &ui_img_useful_electronics_png);
//        lv_obj_set_style_img_opa(label2, 0, 0);
    }

    // Move images when arc animation finished
    if ((count >= 100) && (count <= 200))
    {
    	lv_img_set_angle(img_logo, count - 100);
//        img_logo = lv_img_create(tv1);
//        lv_img_set_src(img_logo, &ui_img_ue_logo_png_large);
    }
    if ((count >= 200) && (count <= 300))
    {
    	uint8_t angle = 300 - count;
		img_logo = lv_img_create(tv1);
		lv_img_set_src(img_logo, &ui_img_ue_logo_png_large);
    	lv_img_set_angle(img_logo, angle);
//        img_logo = lv_img_create(tv1);
//        lv_img_set_src(img_logo, &ui_img_ue_logo_png_large);
    }

    // Delete timer when all animation finished
    if ((count += 5) == 320)
    {
        lv_timer_del(timer);
        //switch screen
        lv_obj_set_tile_id(display, 0, 1, LV_ANIM_ON);

        my_tim_ctx.count_val = 1000;

//        lv_timer_create(lvgl_ui_count_down_timer_cb, 1, &my_tim_ctx);
    }
    else
    {
        timer_ctx->count_val = count;
    }
}

static void lvgl_ui_start_animation(lv_obj_t *scr)
{

    // Align image
//    lv_obj_center(label2);

    // Create arcs
    for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++)
    {
        arc[i] = lv_arc_create(scr);
        // Make arc center
//        lv_obj_center(arc[i]);

        lv_obj_align(arc[i], LV_ALIGN_CENTER, 0, 48);
        // Set arc caption
//        lv_obj_set_size(arc[i], 110 - 15 * i, 220 - 15 * i);

        lv_obj_set_size(arc[i], 100 - 30 * i, 200 - 30 * i);
        lv_arc_set_bg_angles(arc[i], 120 * i, 10 + 120 * i);
        lv_arc_set_value(arc[i], 0);

        // Set arc style
        lv_obj_remove_style(arc[i], NULL, LV_PART_KNOB);
        lv_obj_set_style_arc_width(arc[i], 8, 0);
        lv_obj_set_style_arc_color(arc[i], arc_color[i], 0);



    }

//    if (img_text)
//    {
//        lv_obj_del(img_text);
//        img_text = NULL;
//    }

    // Create timer for animation
    my_tim_ctx.count_val = -90;
    my_tim_ctx.scr = scr;
    lv_timer_create(lvgl_ui_anim_timer_cb, 50, &my_tim_ctx);

    // Disable button
//    lv_obj_add_state(btn, LV_STATE_DISABLED);
}

void lvgl_ui_start(lv_disp_t *disp)
{
    lv_obj_t *scr = lv_disp_get_scr_act(disp);


    display = lv_tileview_create(scr);
	tv1 = lv_tileview_add_tile(display, 0, 0, LV_DIR_HOR);
	tv2 = lv_tileview_add_tile(display, 0, 1, LV_DIR_HOR);


    img_logo = lv_img_create(tv1);
    lv_img_set_src(img_logo, &ui_img_ue_logo_png);

//    img_logo = lv_label_create(tv1);

//    lv_label_set_text(label1, "USEFUL");
//    label2 = lv_label_create(tv1);
//    lv_label_set_text(label2, "ELECTRONICS");

    lvgl_ui_start_animation(tv1);

    lv_obj_clear_flag(tv2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_mainScreen = lv_obj_create(tv2);


	ui_leftPanel = lv_obj_create(ui_mainScreen);
	lv_obj_set_width(ui_leftPanel, 57);
	lv_obj_set_height(ui_leftPanel, 55);
	lv_obj_set_x(ui_leftPanel, -31);
	lv_obj_set_y(ui_leftPanel, -32);
	lv_obj_set_align(ui_leftPanel, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_leftPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_radius(ui_leftPanel, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_leftPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_leftPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_leftPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_leftPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_leftSegment = lv_label_create(ui_leftPanel);
	lv_obj_set_width(ui_leftSegment, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_leftSegment, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_leftSegment, LV_ALIGN_CENTER);
	lv_label_set_text(ui_leftSegment, "00");
	lv_obj_set_style_text_color(ui_leftSegment, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_leftSegment, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_leftSegment, &ui_font_SS52, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_rightPanel = lv_obj_create(ui_mainScreen);
	lv_obj_set_width(ui_rightPanel, 57);
	lv_obj_set_height(ui_rightPanel, 55);
	lv_obj_set_x(ui_rightPanel, 31);
	lv_obj_set_y(ui_rightPanel, -32);
	lv_obj_set_align(ui_rightPanel, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_rightPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
	lv_obj_set_style_radius(ui_rightPanel, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_rightPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_rightPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_rightPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_rightPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_rightSegment = lv_label_create(ui_rightPanel);
	lv_obj_set_width(ui_rightSegment, LV_SIZE_CONTENT);   /// 1
	lv_obj_set_height(ui_rightSegment, LV_SIZE_CONTENT);    /// 1
	lv_obj_set_align(ui_rightSegment, LV_ALIGN_CENTER);
	lv_label_set_text(ui_rightSegment, "00");
	lv_obj_set_style_text_color(ui_rightSegment, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_rightSegment, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_rightSegment, &ui_font_SS52, LV_PART_MAIN | LV_STATE_DEFAULT);

//	ui_middleSpace = lv_obj_create(ui_mainScreen);
//	lv_obj_set_width(ui_middleSpace, 128);
//	lv_obj_set_height(ui_middleSpace, 5);
//	lv_obj_set_x(ui_middleSpace, 0);
//	lv_obj_set_y(ui_middleSpace, -32);
//	lv_obj_set_align(ui_middleSpace, LV_ALIGN_CENTER);
//	lv_obj_clear_flag(ui_middleSpace, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//	lv_obj_set_style_bg_color(ui_middleSpace, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
//	lv_obj_set_style_bg_opa(ui_middleSpace, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//	lv_obj_set_style_border_color(ui_middleSpace, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
//	lv_obj_set_style_border_opa(ui_middleSpace, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void lvgl_ui_counter_update(uint8_t left_panel, uint8_t right_panel)
{
	char temp_digit_string[10] = {0};

	sprintf(temp_digit_string, "%02d", (int)left_panel);

	lv_label_set_text(ui_leftSegment, temp_digit_string);

	sprintf(temp_digit_string, "%02d", (int)right_panel);

	lv_label_set_text(ui_rightSegment, temp_digit_string);
}
void lvgl_ui_timer_function(lvgl_timer_status_t timer_state)
{
	switch (timer_state)
	{
		case LVGL_TIMER_STOP:
			lvgl_ui_delete_timer();
			break;
		case LVGL_TIMER_CREAT:
			lvgl_ui_create_timer();
			break;
		case LVGL_TIMER_RESUME:
			lvgl_ui_resume_timer();
			break;
		case LVGL_TIMER_PAUSE:
			lvgl_ui_pause_timer();
			break;
		case LVGL_TIMER_RESET:
			lvgl_ui_reset_timer();
			break;
		default:
			break;
	}
}

bool lvgl_ui_pause_timer_check()
{
	return lvgl_ui_timer->paused;
}
bool lvgl_ui_running_timer_check(void)
{
	bool retval = false;

	if(lvgl_ui_timer != NULL)
	{
		retval = true;
	}
	return retval;
}

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
