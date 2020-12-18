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
    // ������һ���ͻ�socket
    logger->info("handleConnect from client, address : %s, port : %d ,Socket Num : % d",
        inet_ntoa(key.getSocketAddr().sin_addr),
        key.getSocketAddr().sin_port,
        key.getSocket());
}

void FoxTcpServerSttyHandler::handleRead(FoxSocketKey& key, const void* buff, int length)
{
    // ���յ�������
    logger->info("handleRead from client, address : %s, port : %d ,Socket Num : % d,message =  %s",
        inet_ntoa(key.getSocketAddr().sin_addr),
        key.getSocketAddr().sin_port,
        key.getSocket(),
        buff);

    // �����ݿ������ջ��棬ƴ�ӳ�����������
    this->buffs.appendBuff(key.getSocket(), buff, length);
}

void FoxTcpServerSttyHandler::handleHasRead(FoxSocketKey& key)
{
    // �Ѿ�ȡ��������һ֡����
    this->doHasRead(key);
}

void FoxTcpServerSttyHandler::handleNoRead(FoxSocketKey& key)
{
    // �ﵽ���ʱû�н��յ��µ�����
    this->doHasRead(key);
}

void FoxTcpServerSttyHandler::handleDisconnect(FoxSocketKey& key)
{
    // ������һ���ͻ�socket
    logger->info("handleDisconnect from client, address : %s, port : %d ,Socket Num : % d",
        inet_ntoa(key.getSocketAddr().sin_addr),
        key.getSocketAddr().sin_port,
        key.getSocket());

    // �ͷŶ�Ӧsocket����
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

    // ȡ������������
    STLByteArray buff;
    this->buffs.removeBuff(key.getSocket(), buff);

    // ���һ���ַ����Ľ�����
    buff.add(0x00);

    // ������ת�����ַ���
    string strJson = (const char*)buff.getData();

    // ����proxy����json����
    string result = this->proxy->doJson(strJson);

    // ���ַ�����ת��������
    STLByteArray byArray;
    byArray.append(result.c_str(), result.size());
    byArray.add(0x00);

    // �����ݷ���
    key.send(byArray.getData(), byArray.getSize());
}

