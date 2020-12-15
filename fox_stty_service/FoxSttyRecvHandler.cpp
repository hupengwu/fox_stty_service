#include "FoxSttyRecvHandler.h"
#include <string>
#include <FoxLoggerFactory.h>


ILogger* FoxSttyRecvHandler::logger = FoxLoggerFactory::getLogger();

FoxSttyRecvHandler::FoxSttyRecvHandler()
{
}

FoxSttyRecvHandler::~FoxSttyRecvHandler()
{
}

void FoxSttyRecvHandler::handleOpen(int fd)
{
}

void FoxSttyRecvHandler::handleRead(int fd, const unsigned char* buff, int length)
{
	if (buff == nullptr || length <= 0)
	{
		return;
	}

	this->buffers.appendBuff(fd, (char*)buff, length);
}

void FoxSttyRecvHandler::handleNoRead(int fd)
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

	logger->info("recv stty fd=%d, line:%s",fd, data.getData());
}

void FoxSttyRecvHandler::handleClosed(int fd)
{
	// 删除缓存
	STLByteArray data;
	this->buffers.removeBuff(fd, data);

	logger->info("remove stty fd=%d buffer",fd);
}

