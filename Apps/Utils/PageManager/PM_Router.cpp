#include "PageManager.h"
#include "PM_Log.h"

PageBase* PageManager::Push(const char* name, const PageBase::Stash_t* stash)
{
    /* Check whether the animation of switching pages is being executed */
    if (!SwitchAnimStateCheck())
    {
        return nullptr;
    }

    /* Check whether the stack is repeatedly pushed  */
    if (FindPageInStack(name) != nullptr)
    {
        printf("Page(%s) was multi push", name);
        return nullptr;
    }

    /* Check if the page is registered in the page pool */
    PageBase* base = FindPageInPool(name);
    printf("push Page(%s)\n", name);
    if (base == nullptr)
    {
        printf("Page(%s) was not install", name);
        return nullptr;
    }

    /* Synchronous automatic cache configuration */
    base->priv.IsDisableAutoCache = base->priv.ReqDisableAutoCache;

    /* Push into the stack */
    PageStack.push(base);

    PM_LOG_INFO("Page(%s) push >> [Screen] (stash = 0x%p)", name, stash);

    /* Page switching execution */
    SwitchTo(base, true, stash);

    return base;
}

PageBase* PageManager::Pop()
{
    /* Check whether the animation of switching pages is being executed */
    if (!SwitchAnimStateCheck())
    {
        return nullptr;
    }

    /* Get the top page of the stack */
    PageBase* top = GetStackTop();

    if (top == nullptr)
    {
        printf("Page stack is empty, cat't pop");
        return nullptr;
    }

    /* Whether to turn off automatic cache */
    if (!top->priv.IsDisableAutoCache)
    {
        PM_LOG_INFO("Page(%s) has auto cache, cache disabled", top->Name);
        top->priv.IsCached = false;
    }

    PM_LOG_INFO("Page(%s) pop << [Screen]", top->Name);
    printf("Page(%s) pop\n", top->Name);

    /* Page popup */
    PageStack.pop();

    /* Get the next page */
    top = GetStackTop();

    if (top != nullptr)
    {
        /* Page switching execution */
        SwitchTo(top, false, nullptr);
    }

    return top;
}

void PageManager::SwitchTo(PageBase* newNode, bool isPushAct, const PageBase::Stash_t* stash)
{
    if (newNode == nullptr)
    {
        printf("newNode is nullptr");
        return;
    }

    /* Whether page switching has been requested */
    if (AnimState.IsSwitchReq)
    {
        printf("Page switch busy, reqire(%s) is ignore", newNode->Name);
        return;
    }

    AnimState.IsSwitchReq = true;

    /* Is there a parameter to pass */
    if (stash != nullptr)
    {
        PM_LOG_INFO("stash is detect, %s >> stash(0x%p) >> %s", GetPagePrevName(), stash, newNode->Name);

        void* buffer = nullptr;

        if (newNode->priv.Stash.ptr == nullptr)
        {
            buffer = lv_mem_alloc(stash->size);
            if (buffer == nullptr)
            {
                printf("stash malloc failed");
            }
            else
            {
                PM_LOG_INFO("stash(0x%p) malloc[%d]", buffer, stash->size);
            }
        }
        else if(newNode->priv.Stash.size == stash->size)
        {
            buffer = newNode->priv.Stash.ptr;
            PM_LOG_INFO("stash(0x%p) is exist", buffer);
        }

        if (buffer != nullptr)
        {
            memcpy(buffer, stash->ptr, stash->size);
            PM_LOG_INFO("stash memcpy[%d] 0x%p >> 0x%p", stash->size, stash->ptr, buffer);
            newNode->priv.Stash.ptr = buffer;
            newNode->priv.Stash.size = stash->size;
        }
    }

    /* Record current page */
    PageCurrent = newNode;

    /* If the current page has a cache */
    if (PageCurrent->priv.IsCached)
    {
        /* Direct display, no need to load */
        PM_LOG_INFO("Page(%s) has cached, appear driectly", PageCurrent->Name);
        PageCurrent->priv.State = PageBase::PAGE_STATE_WILL_APPEAR;
    }
    else
    {
        /* Load page */
        PageCurrent->priv.State = PageBase::PAGE_STATE_LOAD;
    }

    if (PagePrev != nullptr)
    {
        PagePrev->priv.Anim.IsEnter = false;
    }

    PageCurrent->priv.Anim.IsEnter = true;

    AnimState.IsPushing = isPushAct;

    if (AnimState.IsPushing)
    {
        /* Update the animation configuration according to the current page */
        SwitchAnimTypeUpdate(PageCurrent);
    }

    /* Update the state machine of the previous page */
    StateUpdate(PagePrev);
    /* Update the state machine of the current page */
    StateUpdate(PageCurrent);

    /* Move the layer, move the new page to the front */
    if (AnimState.IsPushing)
    {
        PM_LOG_INFO("Page PUSH is detect, move Page(%s) to foreground", PageCurrent->Name);
        if (PagePrev){
            lv_obj_move_foreground(PagePrev->root);
        }
        lv_obj_move_foreground(PageCurrent->root);
    }
    else
    {
        PM_LOG_INFO("Page POP is detect, move Page(%s) to foreground", GetPagePrevName());
        lv_obj_move_foreground(PageCurrent->root);
        if (PagePrev){
            lv_obj_move_foreground(PagePrev->root);
        }
    }
}

bool PageManager::FourceUnload(PageBase* base)
{
    if (base == nullptr)
    {
        printf("Page is nullptr, Unload failed");
        return false;
    }

    PM_LOG_INFO("Page(%s) Fource unloading...", base->Name);

    if (base->priv.State == PageBase::PAGE_STATE_ACTIVITY)
    {
        PM_LOG_INFO("Page state is ACTIVITY, Disappearing...");
        base->onViewWillDisappear();
        base->onViewDidDisappear();
    }

    base->priv.State = StateUnloadExecute(base);

    return true;
}

bool PageManager::BackHome()
{
    /* Check whether the animation of switching pages is being executed */
    if (!SwitchAnimStateCheck())
    {
        return false;
    }

    SetStackClear(true);

    PagePrev = nullptr;

    PageBase* home = GetStackTop();

    SwitchTo(home, false);

    return true;
}

bool PageManager::SwitchAnimStateCheck()
{
    if (AnimState.IsSwitchReq)
    {
        printf(
            "Page switch busy[AnimState.IsSwitchReq = %d,"
            "request ignored",
            AnimState.IsSwitchReq
        );
        return false;
    }

    return true;
}

bool PageManager::SwitchReqCheck()
{
    bool ret = false;
    bool lastNodeBusy = PagePrev && PagePrev->priv.Anim.IsBusy;

    if (!PageCurrent->priv.Anim.IsBusy && !lastNodeBusy)
    {
        PM_LOG_INFO("----Page switch was all finished----");
        AnimState.IsSwitchReq = false;
        printf("----Page switch was all finished----\n");
        ret = true;
        PagePrev = PageCurrent;
    }
    else
    {
        if (PageCurrent->priv.Anim.IsBusy)
        {
            printf("Page PageCurrent(%s) is busy", PageCurrent->Name);
        }
        else
        {
            printf("Page PagePrev(%s) is busy\n", GetPagePrevName());
        }
    }

    return ret;
}

void PageManager::onSwitchAnimFinish(lv_anim_t* a)
{
    PageBase* base = (PageBase*)lv_anim_get_user_data(a);
    PageManager* manager = base->Manager;

    PM_LOG_INFO("Page(%s) Anim finish", base->Name);
    manager->StateUpdate(base);
    base->priv.Anim.IsBusy = false;
    bool isFinished = manager->SwitchReqCheck();

    if (!manager->AnimState.IsPushing && isFinished)
    {
        manager->SwitchAnimTypeUpdate(manager->PageCurrent);
    }
}

void PageManager::SwitchAnimCreate(PageBase* base)
{
    LoadAnimAttr_t animAttr;
    if (!GetCurrentLoadAnimAttr(&animAttr))
    {
        return;
    }

    lv_anim_t a;
    AnimDefaultInit(&a);
    lv_anim_set_user_data(&a, base);
    lv_anim_set_var(&a, base->root);
    lv_anim_set_ready_cb(&a, onSwitchAnimFinish);
    lv_anim_set_exec_cb(&a, animAttr.setter);

    int32_t start = 0;

    if (animAttr.getter)
    {
        start = animAttr.getter(base->root);
    }

    if (AnimState.IsPushing)
    {
        if (base->priv.Anim.IsEnter)
        {
            lv_anim_set_values(
                &a,
                animAttr.push.enter.start,
                animAttr.push.enter.end
            );
        }
        else /* Exit */
        {
            lv_anim_set_values(
                &a,
                start,
                animAttr.push.exit.end
            );
        }
    }
    else /* Pop */
    {
        if (base->priv.Anim.IsEnter)
        {
            lv_anim_set_values(
                &a,
                animAttr.pop.enter.start,
                animAttr.pop.enter.end
            );
        }
        else /* Exit */
        {
            lv_anim_set_values(
                &a,
                start,
                animAttr.pop.exit.end
            );
        }
    }
    lv_anim_start(&a);
    base->priv.Anim.IsBusy = true;
}

void PageManager::SetGlobalLoadAnimType(LoadAnim_t anim, uint16_t time, lv_anim_path_cb_t path)
{
    if (anim > _LOAD_ANIM_LAST)
    {
        anim = LOAD_ANIM_NONE;
    }

    AnimState.Global.Type = anim;
    AnimState.Global.Time = time;
    AnimState.Global.Path = path;

    PM_LOG_INFO("Set global load anim type = %d", anim);
}

void PageManager::SwitchAnimTypeUpdate(PageBase* base)
{
    if (base->priv.Anim.Attr.Type == LOAD_ANIM_GLOBAL)
    {
        PM_LOG_INFO(
            "Page(%s) Anim.Type was not set, use AnimState.Global.Type = %d",
            base->Name,
            AnimState.Global.Type
        );
        AnimState.Current = AnimState.Global;
    }
    else
    {
        if (base->priv.Anim.Attr.Type > _LOAD_ANIM_LAST)
        {
            printf(
                "Page(%s) ERROR custom Anim.Type = %d, use AnimState.Global.Type = %d",
                base->Name,
                base->priv.Anim.Attr.Type,
                AnimState.Global.Type
            );
            base->priv.Anim.Attr = AnimState.Global;
        }
        else
        {
            PM_LOG_INFO(
                "Page(%s) custom Anim.Type set = %d",
                base->Name,
                base->priv.Anim.Attr.Type
            );
        }
        AnimState.Current = base->priv.Anim.Attr;
    }
}

void PageManager::AnimDefaultInit(lv_anim_t* a)
{
    lv_anim_init(a);

    uint32_t time = (GetCurrentLoadAnimType() == LOAD_ANIM_NONE) ? 0 : AnimState.Current.Time;
    lv_anim_set_time(a, time);
    lv_anim_set_path_cb(a, AnimState.Current.Path);
}
