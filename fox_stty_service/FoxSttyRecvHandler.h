#pragma once

#include <FoxSttyHandler.h>
#include <STLFIFOBuffers.h>
#include <ILogger.h>
#include <FoxRestfulAsyncTasks.h>

class FoxSttyRecvHandler : public FoxSttyHandler
{
public:
	FoxSttyRecvHandler(FoxRestfulAsyncTasks* tasks);
	virtual ~FoxSttyRecvHandler();

public:
	virtual void handleOpen(const int fd, const char* name);

	virtual void handleRead(const int fd, const char* name, const unsigned char* buff, int length);

	virtual void handleNoRead(const int fd, const char* name);

	virtual void handleClosed(const int fd, const char* name);

private:
	/*
	* 串口接收缓存：将串口一个个字节接收过来的数据，组成连续性的数据
	*/
	STLFIFOBuffers		buffers;
	FoxRestfulAsyncTasks*	tasks;

	static ILogger*		logger;
};

