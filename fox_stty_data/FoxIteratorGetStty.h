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
     * 比较该对象是否为目标数据
     *
     * @param key 元素的Key
     * @param value 元素
     * @return 是否为目标数据
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
