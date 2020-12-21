#include "FoxServiceResponder.h"
#include <FoxJSonObject.h>
#include "FoxSttySendRunnable.h"

FoxServiceResponder::FoxServiceResponder(FoxSttyService* service, FoxRestfulAsyncTasks* tasks, FoxSttyDataManager* datas, STLAsyncTask* threads)
{
	this->service = service;
	this->tasks = tasks;
	this->datas = datas;
	this->threads = threads;
}

FoxServiceResponder::~FoxServiceResponder()
{

}

std::string FoxServiceResponder::respond(const string& resource, const string& method, const string& body)
{
	if (method == "GET")
	{
		return this->respondGet(resource, body);
	}
	if (method == "POST")
	{
		return this->respondPost(resource, body);
	}

	return "";
}

std::string FoxServiceResponder::respondGet(const string& resource, const string& body)
{
	FoxRestfulAsyncTask taskErr;
	taskErr.status = fox::status_error;

	FoxJSonObject oJson;
	if (!oJson.Parse(body))
	{
		taskErr.respond = "json format error!";
		return FoxRestfulAsyncTasks::toJson(taskErr);
	}

	string task_id;
	if (!oJson.Get("task_id", task_id))
	{
		taskErr.respond = "not find task_id attrity";
		return FoxRestfulAsyncTasks::toJson(taskErr);
	}
	

	// 清空过期不取的数据
	this->tasks->cleanOverdue();

	// 检查：该串口是否还在处理前面的任务
	FoxRestfulAsyncTask taskAt;
	taskAt.taskId = task_id;
	this->tasks->removeTask(taskAt);

	return FoxRestfulAsyncTasks::toJson(taskAt);	
}

std::string FoxServiceResponder::respondPost(const string& resource, const string& body)
{
	FoxRestfulAsyncTask taskErr;
	taskErr.status = fox::status_error;

	FoxJSonObject oJson;
	if (!oJson.Parse(body))
	{
		taskErr.respond = "json format error!";
		return FoxRestfulAsyncTasks::toJson(taskErr);
	}

	string name;
	if (!oJson.Get("name", name))
	{
		taskErr.respond = "not find name attrity";
		return FoxRestfulAsyncTasks::toJson(taskErr);
	}

	string data;
	if (!oJson.Get("data", data))
	{
		taskErr.respond = "not find data attrity";
		return FoxRestfulAsyncTasks::toJson(taskErr);
	}

	int time_out;
	if (!oJson.Get("time_out", time_out))
	{
		taskErr.respond = "not find time_out attrity";
		return FoxRestfulAsyncTasks::toJson(taskErr);
	}

	int life_cycle;
	if (!oJson.Get("life_cycle", life_cycle))
	{
		taskErr.respond = "not find life_cycle attrity";
		return FoxRestfulAsyncTasks::toJson(taskErr);
	}

	// 清空过期不取的数据
	this->tasks->cleanOverdue();

	// 检查：该串口是否还在处理前面的任务
	list<FoxRestfulAsyncTask> tasks4obj;
	this->tasks->queryTasksByObjectId(name, tasks4obj);
	if (!tasks4obj.empty())
	{
		taskErr = tasks4obj.front();
		taskErr.status = fox::status_error;
		taskErr.respond = "stty is bussy!";

		return FoxRestfulAsyncTasks::toJson(tasks4obj.front());
	}

	// 记录任务
	FoxRestfulAsyncTask task;
	task.request = body;
	task.objectId = name;
	task.lifeCycle = life_cycle;
	this->tasks->pushTask(task);
	this->tasks->processTask(task);


	// 将任务提交给异步任务去处理
	FoxSttySendRunnable* runnable = new FoxSttySendRunnable(this->datas, this->tasks, task);
	this->threads->execute(runnable);

	return FoxRestfulAsyncTasks::toJson(task);
}

