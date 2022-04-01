#include "DataProc.h"

#define CONFIG_AP3216C_REFR_PERIOD              250 // ms


static void onTimer(Account* account)
{
    HAL::Ap3216c_Info_t ap3216cInfo;
    HAL::Ap3216c_GetInfo(&ap3216cInfo);
    account->Commit(&ap3216cInfo, sizeof(ap3216cInfo));
    account->Publish();
}

static int onEvent(Account* account, Account::EventParam_t* param){
    if (param->event == Account::EVENT_TIMER)
    {
        onTimer(account);
        return 0;
    }

    if (param->event != Account::EVENT_SUB_PULL)
    {
        return Account::RES_UNSUPPORTED_REQUEST;
    }

    if (param->size != sizeof(HAL::Ap3216c_Info_t))
    {
        return Account::RES_SIZE_MISMATCH;
    }
    param->data_p->ReadBuffer(param->pull_p, param->size);
    return 0;
}

void DP_Ap3216c_Init(Account* account){
    //* init pub account
    account -> SetEventCallback(onEvent);
    account -> SetTimerPeriod(CONFIG_AP3216C_REFR_PERIOD);
}