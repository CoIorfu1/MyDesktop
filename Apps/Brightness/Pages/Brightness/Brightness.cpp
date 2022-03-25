#include "Brightness.h"
#include <stdio.h>

using namespace Page;

Brightness::Brightness()
{
}

Brightness::~Brightness()
{
}

void Brightness::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void Brightness::onViewLoad()
{
    View.Create(root);
    printf("view creat\n");
    AttachEvent(View.ui.Slider);
    printf("attch event\n");
}

void Brightness::onViewDidLoad()
{

}

void Brightness::onViewWillAppear()
{ 
    
    lv_obj_clear_flag(View.ui.TopInfo.cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(View.ui.Slider);
    lv_obj_move_foreground(View.ui.TopInfo.cont);
    printf("view will appear\n");
    View.AppearAnimStart();
}

void Brightness::onViewDidAppear()
{
    //lv_obj_cleaBrightnessPager_flag(View.ui.AppCont.cont, LV_OBJ_FLAG_HIDDEN);
}

void Brightness::onViewWillDisappear()
{
    lv_obj_add_flag(View.ui.TopInfo.cont, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(View.ui.Slider, LV_OBJ_FLAG_HIDDEN);
    
    lv_obj_fade_out(root, 250, 250);
    //View.AppearAnimStart(true);
}

void Brightness::onViewDidDisappear()
{
}

void Brightness::onViewDidUnload()
{
    View.Delete();
}

void Brightness::AttachEvent(lv_obj_t* obj)
{
    printf("test\n");
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Brightness::onEvent(lv_event_t* event)
{ 
    Brightness* instance = (Brightness*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if(code == LV_EVENT_REFR_EXT_DRAW_SIZE) {
        lv_coord_t *s = (lv_coord_t *)lv_event_get_param(event);
        *s = LV_MAX(*s, 60);
    } else if(code == LV_EVENT_DRAW_PART_END) {
        lv_obj_draw_part_dsc_t * dsc = (lv_obj_draw_part_dsc_t *)lv_event_get_param(event);
        if(dsc->part == LV_PART_KNOB && lv_obj_has_state(obj, LV_STATE_PRESSED)) {
            char buf[8];
            lv_snprintf(buf, sizeof(buf), "%d", lv_slider_get_value(obj));

            lv_point_t text_size;
            lv_txt_get_size(&text_size, buf, &lv_font_montserrat_20, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

            lv_area_t txt_area;
            txt_area.x1 = dsc->draw_area->x1 + lv_area_get_width(dsc->draw_area) / 2 - text_size.x / 2;
            txt_area.x2 = txt_area.x1 + text_size.x;
            txt_area.y2 = dsc->draw_area->y1 - 10;
            txt_area.y1 = txt_area.y2 - text_size.y;

            lv_area_t bg_area;
            bg_area.x1 = txt_area.x1 - LV_DPX(8);
            bg_area.x2 = txt_area.x2 + LV_DPX(8);
            bg_area.y1 = txt_area.y1 - LV_DPX(8);
            bg_area.y2 = txt_area.y2 + LV_DPX(8);

            lv_draw_rect_dsc_t rect_dsc;
            lv_draw_rect_dsc_init(&rect_dsc);
            rect_dsc.bg_color = lv_palette_darken(LV_PALETTE_GREY, 3);
            rect_dsc.radius = LV_DPX(5);
            lv_draw_rect(&bg_area, dsc->clip_area, &rect_dsc);

            lv_draw_label_dsc_t label_dsc;
            lv_draw_label_dsc_init(&label_dsc);
            label_dsc.color = lv_color_white();
            label_dsc.font = &lv_font_montserrat_20;
            lv_draw_label(&txt_area, dsc->clip_area, &label_dsc, buf, NULL);
        }
    }
}
