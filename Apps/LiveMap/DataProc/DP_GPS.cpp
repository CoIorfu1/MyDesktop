#include "DataProc.h"

#define CONFIG_GPS_REFR_PERIOD              100 // ms


static void onTimer(Account* account)
{
    HAL::GPS_Info_t gpsInfo;
    HAL::GPS_GetInfo(&gpsInfo);
    account->Commit(&gpsInfo, sizeof(gpsInfo));
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

    if (param->size != sizeof(HAL::GPS_Info_t))
    {
        return Account::RES_SIZE_MISMATCH;
    }
    param->data_p->ReadBuffer(param->pull_p, param->size);
    return 0;
}

void DP_GPS_Init(Account* account){
    //* init pub account
    account -> SetEventCallback(onEvent);
    account -> SetTimerPeriod(CONFIG_GPS_REFR_PERIOD);
}