#pragma once

#include <FoxSttyHandler.h>
#include <STLFIFOBuffers.h>
#include <ILogger.h>

class FoxSttyRecvHandler : public FoxSttyHandler
{
public:
	FoxSttyRecvHandler();
	virtual ~FoxSttyRecvHandler();

public:
	virtual void handleOpen(int fd);

	virtual void handleRead(int fd, const unsigned char* buff, int length);

	virtual void handleNoRead(int fd);

	virtual void handleClosed(int fd);

private:
	/*
	* ���ڽ��ջ��棺������һ�����ֽڽ��չ��������ݣ���������Ե�����
	*/
	STLFIFOBuffers	buffers;

	static ILogger* logger;
};

