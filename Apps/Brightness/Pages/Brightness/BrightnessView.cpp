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
    Label_Create(root, "Brightness",ui.Slider);
    TopInfo_Create(root);

    ui.anim_timeline = lv_anim_timeline_create();

#define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

#define ANIM_OPA_DEF(start_time, obj) \
    ANIM_DEF(start_time, obj, opa_scale, LV_OPA_TRANSP, LV_OPA_COVER)

    lv_coord_t y_tar_top = lv_obj_get_y(ui.TopInfo.cont);

    lv_anim_timeline_wrapper_t wrapper[] =
    {
        ANIM_DEF(0, ui.TopInfo.cont, y, -lv_obj_get_height(ui.TopInfo.cont), y_tar_top),
        LV_ANIM_TIMELINE_WRAPPER_END
    };
    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);
}

void BrightnessView::Delete()
{
    if(ui.anim_timeline)
    {
        lv_anim_timeline_del(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
}

void BrightnessView::Label_Create(lv_obj_t* par, const char* labelname, lv_obj_t* base){
    lv_obj_t* label = lv_label_create(par);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_40, 0);
    lv_obj_set_style_text_color(label, lv_color_hex3(0x000), 0);
    lv_label_set_text(label, labelname);
    lv_obj_align_to(label, base, LV_ALIGN_OUT_BOTTOM_MID, 0, 15);
}

static void lv_timer_update_time(lv_timer_t * timer)
{
    lv_obj_t* label = (lv_obj_t*)timer->user_data;

    // 获取系统时间
    char buf[32];
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    lv_label_set_text_fmt(label, "   %02d:%02d", info->tm_hour, info->tm_min);
}

void BrightnessView::TopInfo_Create(lv_obj_t* par)
{
    lv_obj_t * cont = lv_obj_create(par);     

    lv_style_init(&ui.topInfoContStyle);
    lv_style_set_pad_all(&ui.topInfoContStyle, 0);
    lv_style_set_bg_opa(&ui.topInfoContStyle, 0);
    lv_style_set_text_font(&ui.topInfoContStyle, &lv_font_montserrat_16);
    lv_style_set_border_opa(&ui.topInfoContStyle, 0);
    lv_style_set_radius(&ui.topInfoContStyle, 0);
    lv_style_set_text_color(&ui.topInfoContStyle, lv_color_hex(0x000000)); 

    lv_obj_set_size(cont,  LV_PCT(100), 30);
    lv_obj_add_style(cont, &ui.topInfoContStyle, 0);
    lv_obj_align(cont, LV_ALIGN_TOP_MID, 0, 5);
    ui.TopInfo.cont = cont;
    
    /* 右上角小图标 */
    lv_obj_t* infocont = lv_obj_create(cont);
    lv_obj_set_size(infocont,  200, 25);
    lv_obj_set_layout(infocont, LV_LAYOUT_FLEX);
    lv_obj_set_style_base_dir(infocont, LV_BASE_DIR_RTL, 0);
    lv_obj_set_flex_flow(infocont, LV_FLEX_FLOW_ROW);
    lv_obj_align(infocont, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_add_style(infocont, &ui.topInfoContStyle, 0);
    ui.TopInfo.infoCont = infocont;

    lv_obj_t* label_blank = lv_label_create(ui.TopInfo.infoCont);
    lv_label_set_text(label_blank,  " ");
    ui.TopInfo.blank = label_blank;

    lv_obj_t* label_battery = lv_label_create(ui.TopInfo.infoCont);
    lv_label_set_text(label_battery,  LV_SYMBOL_BATTERY_FULL);
    ui.TopInfo.battery = label_battery;

    lv_obj_t* label_wifi = lv_label_create(ui.TopInfo.infoCont);
    lv_label_set_text(label_wifi, LV_SYMBOL_WIFI);
    ui.TopInfo.wifi = label_wifi;
    
    lv_obj_t* label_time = lv_label_create(ui.TopInfo.cont);
    lv_label_set_text(label_time, "  ");
    lv_obj_align(label_time, LV_ALIGN_LEFT_MID, 0, 0);
    ui.TopInfo.timeInfo = label_time;
    
    ui.TopInfo.timer = lv_timer_create(lv_timer_update_time, 1000, ui.TopInfo.timeInfo);
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

void BrightnessView::AppearAnimStart(bool reverse)
{
    lv_anim_timeline_set_reverse(ui.anim_timeline, reverse);
    lv_anim_timeline_start(ui.anim_timeline);
    printf("anim time line start\n");
}
