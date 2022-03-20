#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include <vector>
#include "PingPongBuffer.h"

class DataCenter;
class Account{
    public:
    //* Event types
    typedef enum {
        EVENT_NONE,
        EVENT_PUB_PUBLISH,
        EVENT_SUB_PULL,
        EVENT_SUB_NOTIFY,
        EVENT_TIMER,
    }EventCode_t;

    //* Error types
    typedef enum{
        RES_OK                  =  0,
        RES_UNKNOW              = -1,
        RES_SIZE_MISMATCH       = -2,
        RES_UNSUPPORTED_REQUEST = -3,
        RES_NO_CALLBACK         = -4,
        RES_NO_CACHE            = -5,
        RES_NO_COMMITED         = -6,
        RES_NOT_FOUND           = -7,
        RES_PARAM_ERROR         = -8
    } ResCode_t;

    typedef struct{
        EventCode_t event;
        Account* tran;
        Account* recv;
        std::shared_ptr<Buffer> data_p;
        void* pull_p;
        uint32_t size;
    }EventParam_t;

    //* Event callback function pointer
    typedef int (*EventCallback_t)(Account* account, EventParam_t* param);

    typedef std::vector<Account*> AccountVector_t;

    public:
    Account(const char* id, DataCenter* center, uint32_t bufSize = 0, void* userData = nullptr);
    ~Account();
    Account* Subscribe(const char* pubID);
    bool Unsubscribe(const char* pubID);
    bool Commit(const void* data_p, uint32_t size);
    int Publish();
    int Pull(const char* pubID, void* data_p, uint32_t size);
    int Pull(Account* pub, void* data_p, uint32_t size);
    int Notify(const char* pubID, const void* data_p, uint32_t size);
    int Notify(Account* pub, const void* data_p, uint32_t size);
    void SetEventCallback(EventCallback_t callback);
    size_t GetPublishersSize();
    size_t GetSubscribersSize();

    public:
    const char* ID;
    DataCenter* Center;
    void* UserData;
    //* This Account subscribe to
    AccountVector_t Publishers;
    //* Account subscribes to this
    AccountVector_t Subscribers;

    struct {
        EventCallback_t EventCallback;
        PingPongBuffer_t BufferManager;
        uint32_t BufferSize;
    }priv;
};

#endif // _ACCOUNT_H_