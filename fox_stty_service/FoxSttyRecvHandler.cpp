#include "FoxSttyRecvHandler.h"
#include <string>
#include <FoxLoggerFactory.h>
#include <STLStringUtils.h>


ILogger* FoxSttyRecvHandler::logger = FoxLoggerFactory::getLogger();

FoxSttyRecvHandler::FoxSttyRecvHandler(FoxRestfulAsyncTasks* tasks)
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

	// 截取串口的短名称
	string fullname = name;
	string dev = "/dev/";
	string shortname = fullname.substr(dev.size(), fullname.size());

	// 查询这个串口有没有对应的任务
	list<FoxRestfulAsyncTask> tasksByObject;
	this->tasks->queryTasksByObjectId(shortname, tasksByObject);

	// 没有对应的任务：可能是设备主动送过来的，也可能是其他情况遗留下来的
	if (tasksByObject.empty())
	{
		return;
	}

	FoxRestfulAsyncTask& taskAt = tasksByObject.front();

	// 已经存在完成的老任务：丢弃本次数据，等待客户端取走
	if (taskAt.status == fox::status_finish)
	{
		return;
	}

	// 讲过完成的任务放到队列中，等待取	
	STLStringUtils::bytes2str(data,taskAt.respond);
	this->tasks->finishTask(taskAt);	
}

void FoxSttyRecvHandler::handleClosed(const int fd, const char* name)
{
	// 删除缓存
	STLByteArray data;
	this->buffers.removeBuff(fd, data);

	logger->info("remove stty fd=%d buffer",fd);
}

