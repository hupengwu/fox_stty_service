#pragma once

#include <string>
#include <list>
#include <STLKVIterator.h>

#include "FoxSttyItem.h"

class FoxIteratorSttyGetConfig : public STLKVIterator
{
public:
    FoxIteratorSttyGetConfig() {};
    virtual ~FoxIteratorSttyGetConfig() {};

public:
    list<FoxSttyItem*> itemList;

public:
    /**
     * �Ƚϸö����Ƿ�ΪĿ������
     *
     * @param key Ԫ�ص�Key
     * @param value Ԫ��
     * @return �Ƿ�ΪĿ������
     */
    virtual bool doKeyValue(void* keyp, void* valuep) {
        if (keyp == nullptr || valuep == nullptr)
        {
            return false;
        }

    //    const std::string& key = *((std::string*)(keyp));
        FoxSttyItem* value = *((FoxSttyItem**)(valuep));


        itemList.push_back(value);

        return true;
    }
};
