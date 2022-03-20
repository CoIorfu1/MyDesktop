#include <stdio.h>
#include <algorithm>
#include <cstring>
#include "DataCenter.h"

DataCenter::DataCenter(const char* name) : AccountMain(name,this){
    Name = name;
}

Account* DataCenter::SearchAccount(const char* id){
    return Find(&AccountPool, id);
}

Account* DataCenter::Find(Account::AccountVector_t* vec, const char* id){
    for(auto& iter : *vec){
        if(strcmp(id, iter->ID) == 0){
            return iter;
        }
    }
    //There is no Account[id] and return nullptr
    return nullptr;
}

bool DataCenter::AddAccount(Account* account){
    if(account == &AccountMain){
        return false;
    }
    // There is already have this Account
    if(SearchAccount(account->ID) != nullptr){
        printf("Account already exists\n");
        return false;
    }
    AccountPool.emplace_back(account);
    AccountMain.Subscribe(account->ID);
    return true;
}

bool DataCenter::RemoveAccount(Account* account){
    return Remove(&AccountPool, account);
}

bool DataCenter::Remove(Account::AccountVector_t* vec, Account* account){
    auto iter = std::find(vec->begin(), vec->end(), account);
    if(iter == vec->end()){
        printf("There is no Account\n");
        return false;
    }
    vec->erase(iter);
    return true;
}

size_t DataCenter::GetAccountLen(){
    return AccountPool.size();
}