#include "FoxTcpServerSttyHandler.h"

#include <FoxLoggerFactory.h>
#include <STLStringUtils.h>
#include <arpa/inet.h>

ILogger* FoxTcpServerSttyHandler::logger = FoxLoggerFactory::getLogger();

FoxTcpServerSttyHandler::FoxTcpServerSttyHandler(IFoxSttyProxy* proxy)
{
    this->proxy = proxy;
}

FoxTcpServerSttyHandler::~FoxTcpServerSttyHandler()
{
    if (this->proxy != nullptr)
    {
        delete this->proxy;
        this->proxy = nullptr;
    }
}

void FoxTcpServerSttyHandler::handleConnect(FoxSocketKey& key)
{
    // 接入了一个客户socket
    logger->info("handleConnect from client, address : %s, port : %d ,Socket Num : % d",
        inet_ntoa(key.getSocketAddr().sin_addr),
        key.getSocketAddr().sin_port,
        key.getSocket());
}

void FoxTcpServerSttyHandler::handleRead(FoxSocketKey& key, const void* buff, int length)
{
    // 接收到的数据
    logger->info("handleRead from client, address : %s, port : %d ,Socket Num : % d,message =  %s",
        inet_ntoa(key.getSocketAddr().sin_addr),
        key.getSocketAddr().sin_port,
        key.getSocket(),
        buff);

    // 将数据块放入接收缓存，拼接成连续性数据
    this->buffs.appendBuff(key.getSocket(), buff, length);
}

void FoxTcpServerSttyHandler::handleHasRead(FoxSocketKey& key)
{
    // 已经取完完整的一帧数据
    this->doHasRead(key);
}

void FoxTcpServerSttyHandler::handleNoRead(FoxSocketKey& key)
{
    // 达到最大超时没有接收到新的数据
    this->doHasRead(key);
}

void FoxTcpServerSttyHandler::handleDisconnect(FoxSocketKey& key)
{
    // 接入了一个客户socket
    logger->info("handleDisconnect from client, address : %s, port : %d ,Socket Num : % d",
        inet_ntoa(key.getSocketAddr().sin_addr),
        key.getSocketAddr().sin_port,
        key.getSocket());

    // 释放对应socket缓存
    STLByteArray buff;
    this->buffs.removeBuff(key.getSocket(), buff);
}

void FoxTcpServerSttyHandler::doHasRead(FoxSocketKey& key)
{
    int size = 0;
    if (!this->buffs.queryBuff(key.getSocket(), size))
    {
        return;
    }
    if (size == 0)
    {
        return;
    }

    // 取出完整的数据
    STLByteArray buff;
    this->buffs.removeBuff(key.getSocket(), buff);

    // 添加一个字符串的结束符
    buff.add(0x00);

    // 将数组转换成字符串
    string strJson = (const char*)buff.getData();

    // 交由proxy进行json处理
    string result = this->proxy->doJson(strJson);

    // 将字符串组转换成数组
    STLByteArray byArray;
    byArray.append(result.c_str(), result.size());
    byArray.add(0x00);

    // 将数据返回
    key.send(byArray.getData(), byArray.getSize());
}

