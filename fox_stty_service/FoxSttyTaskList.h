#pragma once
#include <string>
#include <list>
#include <map>
#include <mutex>

namespace fox
{
	constexpr auto status_new			= "new";
	constexpr auto status_processing	= "donging";
	constexpr auto status_finish		= "finish";
	constexpr auto status_not_exist		= "not_exist";
	constexpr auto status_overload		= "overload";
	constexpr auto status_error			= "error";

	struct AsyncTask
	{
		/*
		* 任务的UUID
		*/
		std::string id;
		/*
		* 请求内容
		*/
		std::string	request;
		/*
		* 响应内容
		*/
		std::string	respond;
		/*
		* 任务状态
		*/
		std::string	status;
		/*
		* 请求时间
		*/
		time_t requestTime = 0;
		/*
		* 响应时间
		*/
		time_t respondTime = 0;
		/*
		* 生命周期：从请求时间开始计算，如果在生命周期范围内都没有被取走，那么这个任务就过期了
		*/
		long lifeCycle = 1000 * 1000;
		
	};
}

using namespace std;
using namespace fox;

class FoxSttyTaskList
{
public:
	FoxSttyTaskList();
	virtual ~FoxSttyTaskList();

public:// 业务流程
	/*
	* 1、（客户端）提交一个任务：状态new/error/overload
	*/
	bool pushTask(AsyncTask& task);


	/*
	* 2、（服务端）取出一个任务：状态status_processing
	*/
	bool processTask(AsyncTask& task);

	/*
	* 3、（服务端）完成一个任务：状态status_finish
	*/
	bool finishTask(AsyncTask& task);

	/*
	* 4、（客户端）查询提交的任务：状态上述状态或者status_not_exist
	*/
	void queryTask(AsyncTask& task);

public:
	/*
	* 设置任务的最大空间
	*/
	void setMaxSize(int maxSize);

	/*
	* 清除过期任务
	*/
	void cleanOverdue();

private:
	mutex					lock;
	map<string,AsyncTask>	id2task;

	/*
	* 最大容量
	*/
	int	maxSize;
};

