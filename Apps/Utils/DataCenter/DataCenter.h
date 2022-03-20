#ifndef _DATACENT_
#define _DATACENT_

#include "Account.h"

class DataCenter{
    public:
    /* The name of the data center will be used as the ID of the main account */
    const char* Name;
    /* Main account, will automatically follow all accounts */
    Account AccountMain;

public:
    DataCenter(const char* name);
    //~DataCenter();
    bool AddAccount(Account* account);
    bool RemoveAccount(Account* account);
    bool Remove(Account::AccountVector_t* vec, Account* account);
    Account* SearchAccount(const char* id);
    Account* Find(Account::AccountVector_t* vec, const char* id);
    size_t GetAccountLen();

private:

    /* Account pool */
    Account::AccountVector_t AccountPool;
};

#endif // _DATACENT_