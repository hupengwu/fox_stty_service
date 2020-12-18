#include "FoxSttyRecvHandler.h"
#include <string>
#include <FoxLoggerFactory.h>


ILogger* FoxSttyRecvHandler::logger = FoxLoggerFactory::getLogger();

FoxSttyRecvHandler::FoxSttyRecvHandler(FoxSttyTaskList* tasks)
{
	this->tasks = tasks;
}

FoxSttyRecvHandler::~FoxSttyRecvHandler()
{
}

void FoxSttyRecvHandler::handleOpen(const int fd, const char* name)
{
}

void FoxSttyRecvHandler::handleRead(const int fd, const char* name, const unsigned char* buff, int length)
{
	if (buff == nullptr || length <= 0)
	{
		return;
	}

	this->buffers.appendBuff(fd, (char*)buff, length);
}

void FoxSttyRecvHandler::handleNoRead(const int fd, const char* name)
{
	// 检查：是否为空数据
	int size = 0;
	if (!this->buffers.queryBuff(fd, size))
	{
		return;
	}

	STLByteArray data;
	this->buffers.removeBuff(fd, data);
	data.add(0);

	logger->info("recv stty name=%s, line:%s", name, data.getData());

	string fullname = name;
	string dev = "/dev/";
	string shortname = fullname.substr(dev.size(), fullname.size());

	
	
}

void FoxSttyRecvHandler::handleClosed(const int fd, const char* name)
{
	// 删除缓存
	STLByteArray data;
	this->buffers.removeBuff(fd, data);

	logger->info("remove stty fd=%d buffer",fd);
}

