#include "Brightness.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

using namespace Page;

void BrightnessView::Create(lv_obj_t* root)
{
    lv_obj_remove_style_all(root);
    lv_obj_set_style_bg_color(root, lv_color_hex3(0xfff), 0);
    lv_obj_set_style_bg_opa(root, 255, 0);
    lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);
    
    Slider_Creat(root);
    Label_Create(root, "Waiting", ui.Slider);
}

void BrightnessView::Delete()
{
    lv_style_reset(&ui.styleMain);
    lv_style_reset(&ui.styleIndicator);
    lv_style_reset(&ui.styleKnob);
    lv_style_reset(&ui.stylePressedColor);
}

void BrightnessView::Slider_Creat(lv_obj_t* par){
    static const lv_style_prop_t props[] = {LV_STYLE_BG_COLOR};
    static lv_style_transition_dsc_t transition_dsc;
    lv_style_transition_dsc_init(&transition_dsc, props, lv_anim_path_linear, 300, 0, NULL);

    lv_style_init(&ui.styleMain);
    lv_style_set_bg_opa(&ui.styleMain, LV_OPA_COVER);
    lv_style_set_bg_color(&ui.styleMain, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_radius(&ui.styleMain, LV_RADIUS_CIRCLE);
    lv_style_set_pad_ver(&ui.styleMain, -2); /*Makes the indicator larger*/

    lv_style_init(&ui.styleIndicator);
    lv_style_set_bg_opa(&ui.styleIndicator, LV_OPA_COVER);
    lv_style_set_bg_color(&ui.styleIndicator, lv_palette_main(LV_PALETTE_ORANGE));
    lv_style_set_radius(&ui.styleIndicator, LV_RADIUS_CIRCLE);
    lv_style_set_transition(&ui.styleIndicator, &transition_dsc);

    lv_style_init(&ui.styleKnob);
    lv_style_set_bg_opa(&ui.styleKnob, LV_OPA_COVER);
    lv_style_set_bg_color(&ui.styleKnob, lv_palette_main(LV_PALETTE_ORANGE));
    lv_style_set_border_color(&ui.styleKnob, lv_palette_darken(LV_PALETTE_ORANGE, 3));
    lv_style_set_border_width(&ui.styleKnob, 2);
    lv_style_set_radius(&ui.styleKnob, LV_RADIUS_CIRCLE);
    lv_style_set_pad_all(&ui.styleKnob, 6); /*Makes the knob larger*/
    lv_style_set_transition(&ui.styleKnob, &transition_dsc);

    lv_style_init(&ui.stylePressedColor);
    lv_style_set_bg_color(&ui.stylePressedColor, lv_palette_darken(LV_PALETTE_ORANGE, 2));

    lv_obj_t * slider = lv_slider_create(par);
    lv_obj_remove_style_all(slider);        /*Remove the styles coming from the theme*/
    lv_obj_set_width(slider, LV_PCT(60));  // lv_pct(x) can be used to set the size and position in percentage
    lv_bar_set_range(slider, 0, 8);
    lv_slider_set_value(slider, 0, LV_ANIM_ON);
    lv_obj_add_style(slider, &ui.styleMain, LV_PART_MAIN);
    lv_obj_add_style(slider, &ui.styleIndicator, LV_PART_INDICATOR);
    lv_obj_add_style(slider, &ui.stylePressedColor, LV_PART_INDICATOR | LV_STATE_PRESSED);
    lv_obj_add_style(slider, &ui.styleKnob, LV_PART_KNOB);
    lv_obj_add_style(slider, &ui.stylePressedColor, LV_PART_KNOB | LV_STATE_PRESSED);
    ui.Slider = slider;
    lv_obj_center(ui.Slider);
}

void BrightnessView::Label_Create(lv_obj_t* par, const char* labelname, lv_obj_t* base){
    lv_obj_t* label = lv_label_create(par);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_40, 0);
    lv_obj_set_style_text_color(label, lv_color_hex3(0x000), 0);
    lv_label_set_text(label, labelname);
    lv_obj_align_to(label, base, LV_ALIGN_OUT_BOTTOM_MID, 0, 15);
}




