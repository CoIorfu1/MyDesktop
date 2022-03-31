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
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP);
}

void Brightness::onViewLoad()
{
    View.Create(root);
}

void Brightness::onViewDidLoad()
{

}

void Brightness::onViewWillAppear()
{ 
    
}

void Brightness::onViewDidAppear()
{

}

void Brightness::onViewWillDisappear()
{
    
    lv_obj_fade_out(root, 250, 250);
}

void Brightness::onViewDidDisappear()
{
}

void Brightness::onViewDidUnload()
{
    View.Delete();
}



