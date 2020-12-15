#pragma once

#include <ILogger.h>
#include <FoxSocketHandler.h>
#include <STLFIFOBuffers.h>
#include "IFoxSttyProxy.h"

class FoxTcpServerSttyHandler : public FoxSocketHandler
{
public:
    FoxTcpServerSttyHandler(IFoxSttyProxy* proxy);
    ~FoxTcpServerSttyHandler();

public:
    /**
     * ����Accept��Ϣ����һ���ͻ��˽������˵�ʱ�򣬻Ჶ���������
     * ����NioServerSocket
     *
     * @param key SelectionKey
     */
    virtual void handleConnect(FoxSocketKey& key);

    /**
     * ����Read��Ϣ�������յ��ͻ��˷��͹���������ʱ���Ჶ���������
     * ����NioServerSocket/NioClientSocket
     *
     * @param key SelectionKey
     */
    virtual void handleRead(FoxSocketKey& key, const void* buff, int length);

    /**
     * ����HasRead��Ϣ�������յ��ͻ��˷��͹�����һ�����ݱ�������ɣ��Ჶ���������
     * ����FoxTcpServerSocket/FoxTcpClientSocket/FoxUdpSocket
     *
     * @param key FoxSocketKey
     */
    virtual void handleHasRead(FoxSocketKey& key);

    /**
     * ����NoRead��Ϣ��SELECT����һ����ʱ������û���յ������ݣ��Ჶ���������
     * ����
     *
     * @param key FoxStty
     */
    virtual void handleNoRead(FoxSocketKey& key);

    /**
     * ����Ͽ�������Ϣ�����ͻ��˸������������ӶϿ�ʱ�򣬻Ჶ���������
     * ����NioClientSocket
     *
     * @param key SelectionKey
     */
    virtual void handleDisconnect(FoxSocketKey& key);

private:
    /*
    * �����Ѿ���ȡ��ɵ�����
    */
    void        doHasRead(FoxSocketKey& key);

private:
    /**
     * ��־
     */
    static ILogger* logger;

    /*
    * �ӿڴ���ҵ��������Ӧ
    */
    IFoxSttyProxy*  proxy;

    /*
    * ���ջ���
    */
    STLFIFOBuffers  buffs;
};


