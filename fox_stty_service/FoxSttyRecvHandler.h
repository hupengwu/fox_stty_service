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
	* 串口接收缓存：将串口一个个字节接收过来的数据，组成连续性的数据
	*/
	STLFIFOBuffers	buffers;

	static ILogger* logger;
};

