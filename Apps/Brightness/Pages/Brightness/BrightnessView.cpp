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

    TopInfo_Create(root);
    Ap3216cInfo_Create(root);

    ui.anim_timeline = lv_anim_timeline_create();

#define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

#define ANIM_OPA_DEF(start_time, obj) \
    ANIM_DEF(start_time, obj, opa_scale, LV_OPA_TRANSP, LV_OPA_COVER)

    lv_coord_t y_tar_top = lv_obj_get_y(ui.TopInfo.cont);

    lv_anim_timeline_wrapper_t wrapper[] =
    {
        ANIM_DEF(50, ui.TopInfo.cont, y, -lv_obj_get_height(ui.TopInfo.cont), y_tar_top),
        LV_ANIM_TIMELINE_WRAPPER_END
    };
    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);
}

void BrightnessView::Ap3216cInfo_Create(lv_obj_t* par){
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 300, 300);
    lv_obj_center(cont);

    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        cont,
        LV_FLEX_ALIGN_SPACE_EVENLY,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER
    );
    ui.ap3216cInfo.cont = cont;

    const char* unitText[3] =
    {
        "IR:",
        "ALS:",
        "PS:"
    };

    for (int i = 0; i < 3; i++)
    {
        SubInfoGrp_Create(
            cont,
            &(ui.ap3216cInfo.labelInfoGrp[i]),
            unitText[i]
        );
    }
}

void BrightnessView::SubInfoGrp_Create(lv_obj_t* par, SubInfo_t* info, const char* unitText)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 300, 100);

    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(
        cont,
        LV_FLEX_ALIGN_START, 
        LV_FLEX_ALIGN_START, 
        LV_FLEX_ALIGN_CENTER
    );

    lv_obj_t* label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_34, 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x0), 0);
    lv_obj_set_width(label, 100);
    lv_label_set_text(label, unitText);
    info->lableUnit = label;

    label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_34, 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0x0), 0);
    lv_obj_set_width(label, 200);
    lv_label_set_text(label, "0");
    info->lableValue = label;

    info->cont = cont;
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

void BrightnessView::AppearAnimStart(bool reverse)
{
    lv_anim_timeline_set_reverse(ui.anim_timeline, reverse);
    lv_anim_timeline_start(ui.anim_timeline);
}

void BrightnessView::Delete()
{
    if(ui.anim_timeline)
    {
        lv_anim_timeline_del(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
    lv_style_reset(&ui.topInfoContStyle);
}
