#include "HomePage.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

using namespace Page;

#define ICON_PATH   ("/root/assets/icon/")
#define ICON_SIZE           (64)
#define ICON_ROW_COUNT      (4)
#define ICON_COLUNM_COUNT   (6)
#define ICON_ROW_SPACE      (60)
#define ICON_COL_SPACE      (90)//((ICON_HOR_RES - (ICON_SIZE * ICON_COLUNM_COUNT)) / (ICON_COLUNM_COUNT - 1))
#define ICON_HOR_RES        (4 + (ICON_SIZE * ICON_COLUNM_COUNT) + (ICON_COL_SPACE * (ICON_COLUNM_COUNT - 1)))//((LV_HOR_RES - ICON_PAD_LEFT - ICON_PAD_RIGHT))        // 列间距
#define ICON_VER_RES        (4 + (ICON_SIZE * ICON_ROW_COUNT) + (ICON_ROW_SPACE * (ICON_ROW_COUNT - 1)))//((LV_VER_RES - ICON_PAD_TOP  - ICON_PAD_BOTTOM))       // 行间距

void HomePageView::Create(lv_obj_t* root)
{
    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);

    lv_obj_t* backGround = lv_img_create(root);
    lv_img_set_src(backGround, "./icon/net.ask100.lvgl.bg.png");
    ui.BackGround = backGround;

    TopInfo_Create(root);
    AppCont_Create(root);
    Label_Create(root, "Map", ui.AppCont.mapIcon);
    Label_Create(root, "Music", ui.AppCont.musicIcon);
    BottomCont_Create(root);

    ui.anim_timeline = lv_anim_timeline_create();
#define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

#define ANIM_OPA_DEF(start_time, obj) \
    ANIM_DEF(start_time, obj, opa_scale, LV_OPA_TRANSP, LV_OPA_COVER)

    lv_coord_t y_tar_bottom = lv_obj_get_y(ui.BottomCont.cont);
    lv_anim_timeline_wrapper_t wrapper[] =
    {
        ANIM_DEF(100, ui.BottomCont.cont, y, LV_VER_RES + lv_obj_get_height(ui.BottomCont.cont), y_tar_bottom),
        LV_ANIM_TIMELINE_WRAPPER_END
    };
    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);
}

void HomePageView::Delete()
{
    if(ui.anim_timeline)
    {
        lv_anim_timeline_del(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
    lv_style_reset(&ui.bottomContStyle);
    lv_style_reset(&ui.topInfoContStyle);
    lv_style_reset(&ui.appContStyle);
}

void HomePageView::BottomCont_Create(lv_obj_t* par)
 {
    lv_obj_t* cont = lv_obj_create(par);

    lv_style_init(&ui.bottomContStyle);
    lv_style_set_pad_all(&ui.bottomContStyle, 0);
    lv_style_set_bg_opa(&ui.bottomContStyle, LV_OPA_50);
    lv_style_set_pad_left(&ui.bottomContStyle, 10);
    lv_style_set_pad_right(&ui.bottomContStyle, 10);
    lv_style_set_border_opa(&ui.bottomContStyle, 0);
    lv_style_set_radius(&ui.bottomContStyle, 22);

    lv_obj_set_size(cont,  LV_PCT(70), 80);
    lv_obj_add_style(cont, &ui.bottomContStyle, 0);
    lv_obj_set_layout(cont, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_align(cont, LV_ALIGN_BOTTOM_MID, 0, -15);   
    ui.BottomCont.cont = cont;

    lv_obj_t* brightnessicon = lv_img_create(ui.BottomCont.cont);
    lv_img_set_src(brightnessicon, "./icon/net.ask100.lvgl.SetBrightness.png");
    ui.BottomCont.brightnessIcon = brightnessicon;
    lv_obj_add_flag(ui.BottomCont.brightnessIcon, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t* calcicon = lv_img_create(ui.BottomCont.cont);
    lv_img_set_src(calcicon, "./icon/net.ask100.lvgl.Calc.png");
}

void HomePageView::AppCont_Create(lv_obj_t* par)
{
    lv_style_init(&ui.appContStyle);
    lv_style_init(&ui.appContStyle);
	lv_style_set_bg_opa(&ui.appContStyle, 0);
	lv_style_set_radius(&ui.appContStyle, 0);
	lv_style_set_pad_all(&ui.appContStyle, 0); 
    lv_style_set_border_opa(&ui.appContStyle, 0);

    lv_obj_t * cont = lv_obj_create(par);
    lv_obj_set_style_base_dir(cont, LV_BASE_DIR_LTR, 0);
    lv_obj_set_style_pad_row(cont, ICON_ROW_SPACE, 0);
    lv_obj_set_style_pad_column(cont, ICON_COL_SPACE, 0);
    lv_obj_set_size(cont, ICON_HOR_RES, ICON_VER_RES);
    lv_obj_center(cont);
    lv_obj_add_style(cont, &ui.appContStyle, 0);
    lv_obj_set_layout(cont, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);
    ui.AppCont.cont = cont;

    lv_obj_t* mapicon = lv_img_create(ui.AppCont.cont);
    lv_img_set_src(mapicon, "./icon/net.ask100.lvgl.FileManager.png");
    lv_obj_add_flag(mapicon, LV_OBJ_FLAG_CLICKABLE);
    ui.AppCont.mapIcon = mapicon;

    lv_obj_t* musicicon = lv_img_create(ui.AppCont.cont);
    lv_img_set_src(musicicon, "./icon/net.ask100.lvgl.Music.png");
    lv_obj_add_flag(musicicon, LV_OBJ_FLAG_CLICKABLE);
    ui.AppCont.musicIcon = musicicon;
}

void HomePageView::TopInfo_Create(lv_obj_t* par)
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

void HomePageView::Label_Create(lv_obj_t* par, const char* labelname, lv_obj_t* base){
    lv_obj_t* label = lv_label_create(par);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(label, 64);
    lv_label_set_text(label, labelname);
    lv_obj_align_to(label, base, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
}

void HomePageView::lv_timer_update_time(lv_timer_t * timer)
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

void HomePageView::AppearAnimStart(bool reverse)
{
    lv_anim_timeline_set_reverse(ui.anim_timeline, reverse);
    lv_anim_timeline_start(ui.anim_timeline);
}