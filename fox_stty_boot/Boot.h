#pragma once

#include <Settings.h>
#include <FoxSttyDataManager.h>
#include <FoxSttyService.h>
#include <SocketManager.h>
#include <FoxRestfulResponderMapper.h>
#include <STLAsyncTask.h>

class Boot
{
public:
	Boot();
	virtual ~Boot();

public:
	bool	start();
	bool	close();

private:
	void	registResponder();

private:
	/*
	* 全局配置
	*/
	Settings					settings;

	/*
	* 全局数据管理
	*/
	FoxSttyDataManager			datas;

	/*
	* 全局业务管理
	*/
	FoxSttyService				services;

	/*
	* 全局SOCKET接入
	*/
	SocketManager				server;

	/*
	* 全局Restful消息响应表
	*/
	FoxRestfulResponderMapper	mapper;

	/*
	* 消息队列
	*/
	FoxRestfulAsyncTasks		tasks;

	/*
	* 全局异步任务
	*/
	STLAsyncTask				threads;
};

