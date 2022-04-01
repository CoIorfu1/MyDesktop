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
    
    Ap3216cInfo_Create(root);
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
    lv_label_set_text(label, "waiting");
    info->lableValue = label;

    info->cont = cont;
}

void BrightnessView::Delete()
{
    
}





