#include <stdio.h>
#include <cstring>
#include "Account.h"
#include "DataCenter.h"

Account::Account(const char* id, DataCenter* center, uint32_t bufSize, void* userData){
    memset(&priv, 0, sizeof(priv));
    ID = id;
    Center = center;
    UserData = userData;

    if(bufSize != 0){
        priv.BufferManager.buffers_[0] = std::make_shared<Buffer>(bufSize);
        priv.BufferManager.buffers_[1] = std::make_shared<Buffer>(bufSize);
        priv.BufferManager.read_index = 0;
        priv.BufferSize = bufSize;
    }
    //* regiter Account to DataCenter 
    Center->AddAccount(this);
    printf("Account[%s] created\n", ID);
}

Account::~Account(){
    //* Account (subscribes to this) to unsubscribe
    for(auto& iter : Subscribers){
        iter->Unsubscribe(ID);
    }
    //* Publisher (this subscribes to) remove this from Subscribers
    for(auto& iter : Publishers){
        Center->Remove(&iter->Subscribers, this);
    }
    //* DataCenter removes this
    Center->RemoveAccount(this);
}

Account* Account::Subscribe(const char* pubID){
    if(strcmp(pubID, ID) == 0){
        printf("Can not subscribe to itself\n"); 
    }
    Account* pub = Center->Find(&Publishers, pubID);
    if(pub != nullptr){
        printf("Already subscribe to\n");
    }
    pub = Center->SearchAccount(pubID);
    if(pub == nullptr){
        printf("There is no Account[]%s\n", pubID);
    }
    Publishers.emplace_back(pub);
    pub->Subscribers.emplace_back(this);
    return pub;
}

bool Account::Unsubscribe(const char* pubID){
    Account* pub = Center->Find(&Publishers, pubID);
    if(pub == nullptr){
        printf("NO subscribe to Account[%s]\n", pubID);
        return false;
    }
    Center->Remove(&Publishers, pub);
    Center->Remove(&pub->Subscribers, this);
    return true;
}

bool Account::Commit(const void* data_p, uint32_t size){
    if(!size || size != priv.BufferSize){
        printf("Account[%s] has no cache\n", ID);
        return false;
    }
    std::shared_ptr<Buffer> wBuf = PingPongBuffer_GetWriteBuf(&priv.BufferManager);
    wBuf->WriteBuffer(data_p, size);
    PingPongBuffer_SetWriteDone(&priv.BufferManager);
    return true;
}

int Account::Publish(){
    int ret = RES_OK;
    if(!priv.BufferSize){
        printf("Account[%s] has no cache\n", ID);
        return RES_NO_CACHE;
    }
    EventParam_t param;
    param.event = EVENT_PUB_PUBLISH;
    param.tran = this;
    param.recv = nullptr;
    //* priv.BufferManager.buffers_[read].use_count() = 2
    param.data_p = PingPongBuffer_GetReadBuf(&priv.BufferManager);
    param.size = priv.BufferSize;

    for(auto& iter : Subscribers){
        EventCallback_t callback = iter->priv.EventCallback;
        if(callback != nullptr){
            ret = callback(iter, &param);
            //* param->data_p->ReadBuffer(des_p, param.size);
            printf("publish to %s done\n", iter->ID);
        }
        else{
            printf("sub[%s] not register callback\n", iter->ID);
        }
    }
    return ret;
}

int Account::Pull(const char* pubID, void* data_p, uint32_t size){
    Account* pub = Center->Find(&Publishers, pubID);
    if(pub == nullptr){
        printf("This Account donot subscribe to %s\n", pubID);
        return RES_NOT_FOUND;
    }
    return Pull(pub, data_p, size);
}

int Account::Pull(Account* pub, void* pull_p, uint32_t size){
    int ret = RES_OK;
    EventCallback_t callback = pub->priv.EventCallback;
    if(callback != nullptr){
        EventParam_t param;
        param.event = EVENT_SUB_PULL;
        param.tran = this;
        param.recv = pub;
        param.data_p = PingPongBuffer_GetReadBuf(&pub->priv.BufferManager);
        param.pull_p = pull_p;
        param.size = size;
        ret = callback(pub, &param);
        //* param->data_p->ReadBuffer(param->pull_p, size);
    }
    else{
        //* read commit cache
        std::shared_ptr<Buffer> rBuf = PingPongBuffer_GetReadBuf(&pub->priv.BufferManager);
        rBuf->ReadBuffer(pull_p, size);
        printf("read commit cache\n");
    }
    return ret;
}

int Account::Notify(const char* pubID, const void* data_p, uint32_t size){
    Account* pub = Center->Find(&Publishers, pubID);
    if(pub == nullptr){
        printf("This Account donot subscribe to %s\n", pubID);
        return RES_NOT_FOUND;
    }
    return Notify(pub, data_p, size);
}

int Account::Notify(Account* pub, const void* data_p, uint32_t size){
    int ret = RES_OK;
    EventCallback_t callback = pub->priv.EventCallback;
    if(callback != nullptr){
        EventParam_t param;
        param.event = EVENT_SUB_NOTIFY;
        param.tran = this;
        param.recv = pub;
        param.pull_p = (void*)data_p;
        param.size = size;
        ret = callback(pub, &param);
        //* memcpy(des_p, param->pull_p, param->size);
    }
    else{
        printf("pub no register callback\n");
        return RES_NO_CALLBACK;
    }
    return ret;
}

void Account::SetEventCallback(EventCallback_t callback){
    priv.EventCallback = callback;
}

size_t Account::GetPublishersSize(){
    return Publishers.size();
}

size_t Account::GetSubscribersSize(){
    return Subscribers.size();
}

