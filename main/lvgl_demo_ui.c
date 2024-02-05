/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "lvgl.h"
#include <math.h>

lv_obj_t *display;
lv_obj_t *tv1;
lv_obj_t *tv2;

lv_obj_t *label1;
lv_obj_t *label2;
lv_obj_t *arc[3];



static lv_color_t arc_color[] =
{
   LV_COLOR_MAKE(0x00, 0x00, 0x00),
   LV_COLOR_MAKE(0x00, 0x00, 0x00),
   LV_COLOR_MAKE(0x00, 0x00, 0x00),
};

#define PI  (3.14159f)

typedef struct
{
    lv_obj_t *scr;
    int count_val;
} my_timer_context_t;

static my_timer_context_t my_tim_ctx;

void anim_timer_cb(lv_timer_t *timer)
{
    my_timer_context_t *timer_ctx = (my_timer_context_t *) timer->user_data;
    int count = timer_ctx->count_val;
    lv_obj_t *scr = timer_ctx->scr;

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


        label2 = lv_label_create(tv1);
        lv_label_set_text(label2, "ELECTRONICS");
//        lv_img_set_src(label2, &ui_img_useful_electronics_png);
//        lv_obj_set_style_img_opa(label2, 0, 0);
    }

    // Move images when arc animation finished
    if ((count >= 100) && (count <= 180))
    {
        lv_coord_t offset = (sinf((count - 140) * 2.25f / 90.0f) + 1) * 20.0f;
        lv_obj_align(label1, LV_ALIGN_CENTER, 0, -offset);
        lv_obj_align(label2, LV_ALIGN_CENTER, 0,  offset);
//        lv_obj_set_style_img_opa(img_text, offset / 40.0f * 255, 0);
    }

    // Delete timer when all animation finished
    if ((count += 5) == 220)
    {
        lv_timer_del(timer);
        //switch screen
        lv_obj_set_tile_id(display, 0, 1, LV_ANIM_ON);

        // Enable button
//        lv_obj_clear_state(btn, LV_STATE_DISABLED);
    }
    else
    {
        timer_ctx->count_val = count;
    }
}

static void start_animation(lv_obj_t *scr)
{

    // Align image
    lv_obj_center(label2);

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
    lv_timer_create(anim_timer_cb, 50, &my_tim_ctx);

    // Disable button
//    lv_obj_add_state(btn, LV_STATE_DISABLED);
}

void example_lvgl_demo_ui(lv_disp_t *disp)
{
    lv_obj_t *scr = lv_disp_get_scr_act(disp);
    lv_obj_t *label = lv_label_create(scr);

    display = lv_tileview_create(scr);
	tv1 = lv_tileview_add_tile(display, 0, 0, LV_DIR_HOR);
	tv2 = lv_tileview_add_tile(display, 0, 1, LV_DIR_HOR);


    label1 = lv_label_create(tv1);
    label2 = lv_label_create(tv1);

    lv_label_set_text(label1, "USEFUL");
//    lv_label_set_text(label2, "ELECTRONICS");

    start_animation(tv1);


//    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR); /* Circular scroll */
//    lv_label_set_text(label, "Subscribe Now, Hello LVGL.");
//    /* Size of the screen (if you use rotation 90 or 270, please set disp->driver->ver_res) */
//    lv_obj_set_width(label, disp->driver->hor_res);
//    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
//
//    lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP); /* Circular scroll */
//    lv_label_set_text(label1, "USEFUL");
//    /* Size of the screen (if you use rotation 90 or 270, please set disp->driver->ver_res) */
//    lv_obj_set_width(label1, disp->driver->hor_res);
//    lv_obj_align(label1, LV_ALIGN_CENTER, 40, 0);
//
//    lv_label_set_long_mode(label2, LV_LABEL_LONG_WRAP); /* Circular scroll */
//    lv_label_set_text(label2, "ELECTRONICS");
//    /* Size of the screen (if you use rotation 90 or 270, please set disp->driver->ver_res) */
//    lv_obj_set_width(label2, disp->driver->hor_res);
//    lv_obj_align(label2, LV_ALIGN_BOTTOM_LEFT, 16, -10);




}
