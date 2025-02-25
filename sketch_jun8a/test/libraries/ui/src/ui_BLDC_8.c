// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.6
// Project name: ui-lcd-480x320_v2_1

#include "ui.h"

void ui_BLDC_8_screen_init(void)
{
    ui_BLDC_8 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_BLDC_8, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BLDC_8, lv_color_hex(0x403890), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BLDC_8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_BLDC8 = lv_label_create(ui_BLDC_8);
    lv_obj_set_width(ui_BLDC8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_BLDC8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_BLDC8, -88);
    lv_obj_set_y(ui_BLDC8, -105);
    lv_obj_set_align(ui_BLDC8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_BLDC8, "SPEED BLDC 8");
    lv_obj_set_style_text_color(ui_BLDC8, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_BLDC8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_BLDC8, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonKembali7 = lv_btn_create(ui_BLDC_8);
    lv_obj_set_width(ui_ButtonKembali7, 124);
    lv_obj_set_height(ui_ButtonKembali7, 34);
    lv_obj_set_x(ui_ButtonKembali7, 156);
    lv_obj_set_y(ui_ButtonKembali7, 124);
    lv_obj_set_align(ui_ButtonKembali7, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_ButtonKembali7, lv_color_hex(0x7DFF69), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonKembali7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelKembali7 = lv_label_create(ui_BLDC_8);
    lv_obj_set_width(ui_LabelKembali7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelKembali7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelKembali7, 158);
    lv_obj_set_y(ui_LabelKembali7, 123);
    lv_obj_set_align(ui_LabelKembali7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelKembali7, "RETURN");

    ui_ArcSpeed8 = lv_arc_create(ui_BLDC_8);
    lv_obj_set_width(ui_ArcSpeed8, 170);
    lv_obj_set_height(ui_ArcSpeed8, 170);
    lv_obj_set_x(ui_ArcSpeed8, -84);
    lv_obj_set_y(ui_ArcSpeed8, 24);
    lv_obj_set_align(ui_ArcSpeed8, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ArcSpeed8, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_arc_set_range(ui_ArcSpeed8, 0, 180);
    lv_arc_set_value(ui_ArcSpeed8, 0);


    ui_LabelSpeed8 = lv_label_create(ui_BLDC_8);
    lv_obj_set_width(ui_LabelSpeed8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSpeed8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelSpeed8, -82);
    lv_obj_set_y(ui_LabelSpeed8, -9);
    lv_obj_set_align(ui_LabelSpeed8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelSpeed8, "0");
    lv_obj_set_style_text_color(ui_LabelSpeed8, lv_color_hex(0xFAFAFA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelSpeed8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelSpeed8, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CheckboxState15 = lv_checkbox_create(ui_BLDC_8);
    lv_checkbox_set_text(ui_CheckboxState15, "ON/OFF");
    lv_obj_set_width(ui_CheckboxState15, 90);
    lv_obj_set_height(ui_CheckboxState15, 25);
    lv_obj_set_x(ui_CheckboxState15, 154);
    lv_obj_set_y(ui_CheckboxState15, 10);
    lv_obj_set_align(ui_CheckboxState15, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_CheckboxState15, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxState15, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxState15, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SliderSpeed8 = lv_slider_create(ui_BLDC_8);
    lv_slider_set_value(ui_SliderSpeed8, 0, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_SliderSpeed8) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_SliderSpeed8, 0,
                                                                                                 LV_ANIM_OFF);
    lv_obj_set_width(ui_SliderSpeed8, 209);
    lv_obj_set_height(ui_SliderSpeed8, 14);
    lv_obj_set_x(ui_SliderSpeed8, -80);
    lv_obj_set_y(ui_SliderSpeed8, 63);
    lv_obj_set_align(ui_SliderSpeed8, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_SliderSpeed8, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderSpeed8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_SliderSpeed8, lv_color_hex(0x7DFF69), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderSpeed8, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_SliderSpeed8, lv_color_hex(0x7DFF69), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SliderSpeed8, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Label63 = lv_label_create(ui_BLDC_8);
    lv_obj_set_width(ui_Label63, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label63, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label63, -84);
    lv_obj_set_y(ui_Label63, -72);
    lv_obj_set_align(ui_Label63, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label63, "");

    ui_CheckboxState16 = lv_checkbox_create(ui_BLDC_8);
    lv_checkbox_set_text(ui_CheckboxState16, "CW/CCW");
    lv_obj_set_width(ui_CheckboxState16, 94);
    lv_obj_set_height(ui_CheckboxState16, 25);
    lv_obj_set_x(ui_CheckboxState16, 153);
    lv_obj_set_y(ui_CheckboxState16, -24);
    lv_obj_set_align(ui_CheckboxState16, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_CheckboxState16, LV_STATE_CHECKED);       /// States
    lv_obj_add_flag(ui_CheckboxState16, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxState16, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxState16, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Switch15 = lv_switch_create(ui_BLDC_8);
    lv_obj_set_width(ui_Switch15, 80);
    lv_obj_set_height(ui_Switch15, 40);
    lv_obj_set_x(ui_Switch15, 159);
    lv_obj_set_y(ui_Switch15, -100);
    lv_obj_set_align(ui_Switch15, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_Switch15, lv_color_hex(0x9F9F9F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Switch15, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Switch15, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Switch15, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Label64 = lv_label_create(ui_BLDC_8);
    lv_obj_set_width(ui_Label64, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label64, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label64, 161);
    lv_obj_set_y(ui_Label64, -67);
    lv_obj_set_align(ui_Label64, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label64, "CW/CCW");
    lv_obj_set_style_text_color(ui_Label64, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label64, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label64, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Switch16 = lv_switch_create(ui_BLDC_8);
    lv_obj_set_width(ui_Switch16, 80);
    lv_obj_set_height(ui_Switch16, 40);
    lv_obj_set_x(ui_Switch16, 161);
    lv_obj_set_y(ui_Switch16, -15);
    lv_obj_set_align(ui_Switch16, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_Switch16, LV_STATE_CHECKED);       /// States
    lv_obj_set_style_bg_color(ui_Switch16, lv_color_hex(0x9F9F9F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Switch16, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Switch16, lv_color_hex(0xFF3F3F), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Switch16, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_Switch16, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Switch16, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_Label65 = lv_label_create(ui_BLDC_8);
    lv_obj_set_width(ui_Label65, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label65, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label65, 163);
    lv_obj_set_y(ui_Label65, 19);
    lv_obj_set_align(ui_Label65, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label65, "ON/OFF");
    lv_obj_set_style_text_color(ui_Label65, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label65, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label65, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ButtonSimpan7 = lv_btn_create(ui_BLDC_8);
    lv_obj_set_width(ui_ButtonSimpan7, 124);
    lv_obj_set_height(ui_ButtonSimpan7, 34);
    lv_obj_set_x(ui_ButtonSimpan7, 156);
    lv_obj_set_y(ui_ButtonSimpan7, 81);
    lv_obj_set_align(ui_ButtonSimpan7, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_ButtonSimpan7, lv_color_hex(0x7DFF69), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ButtonSimpan7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label66 = lv_label_create(ui_BLDC_8);
    lv_obj_set_width(ui_Label66, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label66, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label66, 156);
    lv_obj_set_y(ui_Label66, 81);
    lv_obj_set_align(ui_Label66, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label66, "SAVE");
    lv_obj_set_style_text_color(ui_Label66, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label66, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label66, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ContainerMsgBox7 = lv_obj_create(ui_BLDC_8);
    lv_obj_remove_style_all(ui_ContainerMsgBox7);
    lv_obj_set_width(ui_ContainerMsgBox7, 276);
    lv_obj_set_height(ui_ContainerMsgBox7, 252);
    lv_obj_set_x(ui_ContainerMsgBox7, -67);
    lv_obj_set_y(ui_ContainerMsgBox7, -11);
    lv_obj_set_align(ui_ContainerMsgBox7, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ContainerMsgBox7, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_ContainerMsgBox7, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Panel9 = lv_obj_create(ui_ContainerMsgBox7);
    lv_obj_set_width(ui_Panel9, 270);
    lv_obj_set_height(ui_Panel9, 250);
    lv_obj_set_x(ui_Panel9, 0);
    lv_obj_set_y(ui_Panel9, -1);
    lv_obj_set_align(ui_Panel9, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel9, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Panel9, lv_color_hex(0x2D3273), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel9, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label67 = lv_label_create(ui_ContainerMsgBox7);
    lv_obj_set_width(ui_Label67, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label67, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label67, 1);
    lv_obj_set_y(ui_Label67, -24);
    lv_obj_set_align(ui_Label67, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label67, "SAVING DATA ?");
    lv_obj_set_style_text_color(ui_Label67, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label67, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label67, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button25 = lv_btn_create(ui_ContainerMsgBox7);
    lv_obj_set_width(ui_Button25, 100);
    lv_obj_set_height(ui_Button25, 40);
    lv_obj_set_x(ui_Button25, 61);
    lv_obj_set_y(ui_Button25, 89);
    lv_obj_set_align(ui_Button25, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_Button25, lv_color_hex(0x7DFF69), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button25, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button26 = lv_btn_create(ui_ContainerMsgBox7);
    lv_obj_set_width(ui_Button26, 100);
    lv_obj_set_height(ui_Button26, 40);
    lv_obj_set_x(ui_Button26, -63);
    lv_obj_set_y(ui_Button26, 89);
    lv_obj_set_align(ui_Button26, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_Button26, lv_color_hex(0x7DFF69), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button26, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_blend_mode(ui_Button26, LV_BLEND_MODE_NORMAL, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label68 = lv_label_create(ui_ContainerMsgBox7);
    lv_obj_set_width(ui_Label68, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label68, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label68, -60);
    lv_obj_set_y(ui_Label68, 88);
    lv_obj_set_align(ui_Label68, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label68, "CANCEL");

    ui_Label69 = lv_label_create(ui_ContainerMsgBox7);
    lv_obj_set_width(ui_Label69, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label69, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label69, 60);
    lv_obj_set_y(ui_Label69, 88);
    lv_obj_set_align(ui_Label69, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label69, "YES");

    lv_obj_add_event_cb(ui_ButtonKembali7, ui_event_ButtonKembali7, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ArcSpeed8, ui_event_ArcSpeed8, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_LabelSpeed8, ui_event_LabelSpeed8, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CheckboxState15, ui_event_CheckboxState15, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SliderSpeed8, ui_event_SliderSpeed8, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonSimpan7, ui_event_ButtonSimpan7, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button25, ui_event_Button25, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button26, ui_event_Button26, LV_EVENT_ALL, NULL);

}
