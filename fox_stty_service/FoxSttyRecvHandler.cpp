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
	// ��飺�Ƿ�Ϊ������
	int size = 0;
	if (!this->buffers.queryBuff(fd, size))
	{
		return;
	}

	STLByteArray data;
	this->buffers.removeBuff(fd, data);
	data.add(0);

	logger->info("recv stty name=%s, line:%s", name, data.getData());

	// ��ȡ���ڵĶ�����
	string fullname = name;
	string dev = "/dev/";
	string shortname = fullname.substr(dev.size(), fullname.size());

	// ��ѯ���������û�ж�Ӧ������
	list<FoxRestfulAsyncTask> tasksByObject;
	this->tasks->queryTasksByObjectId(shortname, tasksByObject);

	// û�ж�Ӧ�����񣺿������豸�����͹����ģ�Ҳ�����������������������
	if (tasksByObject.empty())
	{
		return;
	}

	FoxRestfulAsyncTask& taskAt = tasksByObject.front();

	// �Ѿ�������ɵ������񣺶����������ݣ��ȴ��ͻ���ȡ��
	if (taskAt.status == fox::status_finish)
	{
		return;
	}

	// ������ɵ�����ŵ������У��ȴ�ȡ	
	STLStringUtils::bytes2str(data,taskAt.respond);
	this->tasks->finishTask(taskAt);	
}

void FoxSttyRecvHandler::handleClosed(const int fd, const char* name)
{
	// ɾ������
	STLByteArray data;
	this->buffers.removeBuff(fd, data);

	logger->info("remove stty fd=%d buffer",fd);
}

