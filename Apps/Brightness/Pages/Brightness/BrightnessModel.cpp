#include "./BrightnessModel.h"

using namespace Page;

void BrightnessModel::Init()
{
    account = new Account("BrightnessModel", DataProc::Center(), 0, this);
    account->Subscribe("Ap3216c");
    account->SetEventCallback(onEvent);
}

void BrightnessModel::Deinit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

int BrightnessModel::onEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event != Account::EVENT_PUB_PUBLISH)
    {
        return Account::RES_UNSUPPORTED_REQUEST;
    }

    if (strcmp(param->tran->ID, "Ap3216c") != 0
            || param->size != sizeof(HAL::Ap3216c_Info_t))
    {
        printf("sub account do't match!\n");
        return -1;
    }

    BrightnessModel* instance = (BrightnessModel*)account->UserData;
    if(instance->mtx.try_lock()){
        param->data_p->ReadBuffer(&instance->ap3216cInfo, sizeof(HAL::Ap3216c_Info_t));
        printf("read %d, %d, %d", instance->ap3216cInfo.IR, instance->ap3216cInfo.ALS, instance->ap3216cInfo.PS);
        instance->mtx.unlock();
    }
    
    return 0;
}