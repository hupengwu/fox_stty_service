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
	* ȫ������
	*/
	Settings					settings;

	/*
	* ȫ�����ݹ���
	*/
	FoxSttyDataManager			datas;

	/*
	* ȫ��ҵ�����
	*/
	FoxSttyService				services;

	/*
	* ȫ��SOCKET����
	*/
	SocketManager				server;

	/*
	* ȫ��Restful��Ϣ��Ӧ��
	*/
	FoxRestfulResponderMapper	mapper;

	/*
	* ��Ϣ����
	*/
	FoxRestfulAsyncTasks		tasks;

	/*
	* ȫ���첽����
	*/
	STLAsyncTask				threads;
};

