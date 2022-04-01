#ifndef __BRIGHTNESS_MODEL_H
#define __BRIGHTNESS_MODEL_H

#include <atomic>
#include <limits.h>
#include "../../DataProc/DataProc.h"

namespace Page
{

class BrightnessModel
{

public:
    HAL::Ap3216c_Info_t ap3216cInfo;

public:
    void Init();
    void Deinit();

    unsigned short GetIR()
    {
        if(irReadFlag) {
            irReadFlag = false;
            return ap3216cInfo.IR;
        }
        return USHRT_MAX;
    }

    unsigned short GetALS()
    {     
        if(alsReadFlag) {
            alsReadFlag = false;
            return ap3216cInfo.ALS;
        }
        return USHRT_MAX;
    }

    unsigned short GetPS()
    {
        if(psReadFlag) {
            psReadFlag = false;
            return ap3216cInfo.PS;
        }
        return USHRT_MAX;
    }

private:
    Account* account;
    std::atomic_bool irReadFlag;
    std::atomic_bool alsReadFlag;
    std::atomic_bool psReadFlag;

private:
    static int onEvent(Account* account, Account::EventParam_t* param);
};

}

#endif