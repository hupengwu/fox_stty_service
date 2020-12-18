#include "FoxSttyTaskList.h"
#include <UUIDUtils.h>


FoxSttyTaskList::FoxSttyTaskList()
{
	maxSize = 10;
}

FoxSttyTaskList::~FoxSttyTaskList()
{
}

bool FoxSttyTaskList::pushTask(AsyncTask& task)
{
	lock_guard<mutex> guard(this->lock);	
	
	if (this->id2task.size() >= this->maxSize)
	{
		return false;
	}

	// 分配ID
	task.id = UUIDUtils::generateUUID();

	// 标识：新任务和请求时间
	task.status = fox::status_new;
	task.requestTime = ::time(nullptr);

	this->id2task[task.id] = task;
	return true;
}

bool FoxSttyTaskList::processTask(AsyncTask& task)
{
	lock_guard<mutex> guard(this->lock);

	map<string, AsyncTask>::iterator it = this->id2task.begin();
	if (it == this->id2task.end())
	{
		return false;
	}

	// 标识为已经被处理
	it->second.status = fox::status_processing;
	task.respondTime = ::time(nullptr);

	task = it->second;
	return true;
}

bool FoxSttyTaskList::finishTask(AsyncTask& task)
{
	lock_guard<mutex> guard(this->lock);

	map<string, AsyncTask>::iterator it = this->id2task.find(task.id);
	if (it == this->id2task.end())
	{
		return false;
	}

	// 标识:任务完成
	AsyncTask& taskAt = it->second;	
	taskAt.status = fox::status_finish;	
	taskAt.respondTime = ::time(nullptr);
	taskAt.respond = task.respond;

	return true;
}

void FoxSttyTaskList::queryTask(AsyncTask& task)
{
	lock_guard<mutex> guard(this->lock);

	map<string, AsyncTask>::iterator it = this->id2task.find(task.id);
	if (it == this->id2task.end())
	{
		task.status = fox::status_not_exist;
		return;
	}

	AsyncTask& taskAt = it->second;
	if (taskAt.status != fox::status_finish)
	{
		task = taskAt;
		return;
	}

	task = taskAt;
	this->id2task.erase(it);
}

void FoxSttyTaskList::cleanOverdue()
{
	lock_guard<mutex> guard(this->lock);

	for (map<string, AsyncTask>::iterator it = this->id2task.begin(); it != this->id2task.end(); it++) 
	{
		AsyncTask& taskAt = it->second;
		if (taskAt.requestTime + taskAt.lifeCycle < taskAt.respondTime)
		{
			continue;
		}
		
		if (taskAt.status == fox::status_finish)
		{
			this->id2task.erase(it);
		}
	}
}

void FoxSttyTaskList::setMaxSize(int maxSize)
{
	lock_guard<mutex> guard(this->lock);

	this->maxSize = maxSize;
}
