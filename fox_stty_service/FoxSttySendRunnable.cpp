#include "FoxSttySendRunnable.h"
#include <FoxJSonObject.h>
#include <STLStringUtils.h>

FoxSttySendRunnable::FoxSttySendRunnable(FoxSttyDataManager* dataMgr, FoxSttyTaskList* tasks, AsyncTask& task)
{
	this->dataMgr = dataMgr;
	this->task = task;
	this->tasks = tasks;
}

FoxSttySendRunnable::~FoxSttySendRunnable()
{
}

void FoxSttySendRunnable::run()
{
	this->sendData();
}

bool FoxSttySendRunnable::sendData()
{
	string body = this->task.request;

	FoxJSonObject oJson;
	if (!oJson.Parse(body))
	{
		return false;
	}

	string name;
	if (!oJson.Get("name", name))
	{
		return false;
	}

	string data;
	if (!oJson.Get("data", data))
	{
		return false;
	}
	STLByteArray sendData;
	if (!STLStringUtils::str2bytes(data, sendData))
	{
		return false;
	}

	int time_out;
	if (!oJson.Get("time_out", time_out))
	{
		return false;
	}


	STLKVMapper<string, FoxSttyItem*>& kvmapper = this->dataMgr->getKVMapper();

	FoxSttyItem* value = nullptr;
	if (!kvmapper.get(name, value))
	{
		return false;
	}

	FoxStty* stty = value->getStty();
	if (stty == nullptr)
	{
		return false;
	}

	// 设置最大接收超时
	stty->setRcvTimeOut(time_out * 1000);

	int length = 0;
	if (!stty->sendData((const char*)sendData.getData(), sendData.getSize(), length))
	{
		return false;
	}

	// 更新任务状态
	this->tasks->finishTask(task);

	return true;
}
