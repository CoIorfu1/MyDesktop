#include "PageManager.h"
#include "PM_Log.h"
#include <algorithm>

#define PM_EMPTY_PAGE_NAME "EMPTY_PAGE"

PageManager::PageManager(PageFactory* factory)
    : Factory(factory)
    , PagePrev(nullptr)
    , PageCurrent(nullptr)
{
    memset(&AnimState, 0, sizeof(AnimState));

    SetGlobalLoadAnimType();
}

PageManager::~PageManager()
{
}

PageBase* PageManager::FindPageInPool(const char* name)
{
    for (auto iter : PagePool)
    {
        if (strcmp(name, iter->Name) == 0)
        {
            return iter;
        }
    }
    return nullptr;
}

PageBase* PageManager::FindPageInStack(const char* name)
{
    decltype(PageStack) stk = PageStack;
    while (!stk.empty())
    {
        PageBase* base = stk.top();

        if (strcmp(name, base->Name) == 0)
        {
            return base;
        }

        stk.pop();
    }

    return nullptr;
}

PageBase* PageManager::Install(const char* className, const char* appName)
{
    if (Factory == nullptr)
    {
        PM_LOG_ERROR("Factory is not regsite, can't install page");
        return nullptr;
    }

    PageBase* base = Factory->CreatePage(className);
    if (base == nullptr)
    {
        PM_LOG_ERROR("Factory has not %s", className);
        return nullptr;
    }

    base->root = nullptr;
    base->ID = 0;
    base->Manager = nullptr;
    base->UserData = nullptr;
    memset(&base->priv, 0, sizeof(base->priv));

    base->onCustomAttrConfig();

    if (appName == nullptr)
    {
        PM_LOG_WARN("appName has not set");
        appName = className;
    }

    PM_LOG_INFO("Install Page[class = %s, name = %s]", className, appName);
    Register(base, appName);
    return base;
}

bool PageManager::Uninstall(const char* appName)
{
    PM_LOG_INFO("Page(%s) uninstall...", appName);

    PageBase* base = FindPageInPool(appName);
    if (base == nullptr)
    {
        PM_LOG_ERROR("Page(%s) was not found", appName);
        return false;
    }

    if (!Unregister(appName))
    {
        PM_LOG_ERROR("Page(%s) unregister failed", appName);
        return false;
    }

    if (base->priv.IsCached)
    {
        PM_LOG_WARN("Page(%s) has cached, unloading...", appName);
        base->priv.State = PageBase::PAGE_STATE_UNLOAD;
        StateUpdate(base);
    }
    else
    {
        PM_LOG_INFO("Page(%s) has not cache", appName);
    }

    delete base;
    PM_LOG_INFO("Uninstall OK");
    return true;
}

bool PageManager::Register(PageBase* base, const char* name)
{
    if (FindPageInPool(name) != nullptr)
    {
        PM_LOG_ERROR("Page(%s) was multi registered", name);
        return false;
    }

    base->Manager = this;
    base->Name = name;

    PagePool.push_back(base);

    return true;
}

bool PageManager::Unregister(const char* name)
{
    PM_LOG_INFO("Page(%s) unregister...", name);

    PageBase* base = FindPageInStack(name);

    if (base != nullptr)
    {
        PM_LOG_ERROR("Page(%s) was in stack", name);
        return false;
    }

    base = FindPageInPool(name);
    if (base == nullptr)
    {
        PM_LOG_ERROR("Page(%s) was not found", name);
        return false;
    }

    auto iter = std::find(PagePool.begin(), PagePool.end(), base);

    if (iter == PagePool.end())
    {
        PM_LOG_ERROR("Page(%s) was not found in PagePool", name);
        return false;
    }

    PagePool.erase(iter);

    PM_LOG_INFO("Unregister OK");
    return true;
}

PageBase* PageManager::GetStackTop()
{
    return PageStack.empty() ? nullptr : PageStack.top();
}

PageBase* PageManager::GetStackTopAfter()
{
    PageBase* top = GetStackTop();

    if (top == nullptr)
    {
        return nullptr;
    }

    PageStack.pop();

    PageBase* topAfter = GetStackTop();

    PageStack.push(top);

    return topAfter;
}

void PageManager::SetStackClear(bool keepBottom)
{
    while (1)
    {
        PageBase* top = GetStackTop();

        if (top == nullptr)
        {
            PM_LOG_INFO("Page stack is empty, breaking...");
            break;
        }

        PageBase* topAfter = GetStackTopAfter();

        if (topAfter == nullptr)
        {
            if (keepBottom)
            {
                PagePrev = top;
                PM_LOG_INFO("Keep page stack bottom(%s), breaking...", top->Name);
                break;
            }
            else
            {
                PagePrev = nullptr;
            }
        }

        FourceUnload(top);

        PageStack.pop();
    }
    PM_LOG_INFO("Stack clear done");
}

const char* PageManager::GetPagePrevName()
{
    return PagePrev ? PagePrev->Name : PM_EMPTY_PAGE_NAME;
}
