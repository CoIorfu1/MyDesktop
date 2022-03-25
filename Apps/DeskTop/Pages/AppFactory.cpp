#include "AppFactory.h"
#include "HomePage/HomePage.h"
#include "Brightness/Brightness.h"

#define APP_CLASS_MATCH(className)\
    if (strcmp(name, #className) == 0)\
    {\
        return new Page::className;\
    }\

PageBase* AppFactory::CreatePage(const char* name)
{
    APP_CLASS_MATCH(HomePage);
    APP_CLASS_MATCH(Brightness);
    return nullptr;
}
