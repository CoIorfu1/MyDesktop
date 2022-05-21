#include "App.h"
#include "Pages/AppFactory.h"
#include "../Utils/PageManager/PageManager.h"
#include "../Utils/lv_lib_png/lv_png.h"

static AppFactory factory;
static PageManager manager(&factory);

void App_Init()
{
    lv_obj_t* scr = lv_scr_act();
    lv_obj_remove_style_all(scr);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());

    manager.Install("HomePage","Pages/HomePage");
    manager.Install("Brightness", "Pages/Brightness");

    manager.SetGlobalLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500);

    manager.Push("Pages/HomePage");
}

void Pop(){
    manager.Pop();
}

void App_Uninit()
{
    
}
