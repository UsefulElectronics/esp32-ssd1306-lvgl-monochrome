// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Timer

#include "../ui.h"

void ui_mainScreen_screen_init(void)
{
    ui_mainScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_mainScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_leftPanel = lv_obj_create(ui_mainScreen);
    lv_obj_set_width(ui_leftPanel, 57);
    lv_obj_set_height(ui_leftPanel, 55);
    lv_obj_set_x(ui_leftPanel, -31);
    lv_obj_set_y(ui_leftPanel, 0);
    lv_obj_set_align(ui_leftPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_leftPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_leftPanel, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_leftPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_leftPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_leftPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_leftPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_leftSegment = lv_label_create(ui_leftPanel);
    lv_obj_set_width(ui_leftSegment, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_leftSegment, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_leftSegment, LV_ALIGN_CENTER);
    lv_label_set_text(ui_leftSegment, "10");
    lv_obj_set_style_text_color(ui_leftSegment, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_leftSegment, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_leftSegment, &ui_font_SS52, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rightPanel = lv_obj_create(ui_mainScreen);
    lv_obj_set_width(ui_rightPanel, 57);
    lv_obj_set_height(ui_rightPanel, 55);
    lv_obj_set_x(ui_rightPanel, 31);
    lv_obj_set_y(ui_rightPanel, 0);
    lv_obj_set_align(ui_rightPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_rightPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_rightPanel, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rightPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rightPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_rightPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_rightPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rightSegment = lv_label_create(ui_rightPanel);
    lv_obj_set_width(ui_rightSegment, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_rightSegment, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_rightSegment, LV_ALIGN_CENTER);
    lv_label_set_text(ui_rightSegment, "12");
    lv_obj_set_style_text_color(ui_rightSegment, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_rightSegment, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_rightSegment, &ui_font_SS52, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_middleSpace = lv_obj_create(ui_mainScreen);
    lv_obj_set_width(ui_middleSpace, 128);
    lv_obj_set_height(ui_middleSpace, 5);
    lv_obj_set_align(ui_middleSpace, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_middleSpace, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_middleSpace, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_middleSpace, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_middleSpace, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_middleSpace, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


}