#pragma once

#include <STLRunnable.h>
#include <FoxSttyDataManager.h>
#include <FoxRestfulAsyncTasks.h>


class FoxSttySendRunnable : public STLRunnable
{
public:
	FoxSttySendRunnable(FoxSttyDataManager* datas, FoxRestfulAsyncTasks* tasks,FoxRestfulAsyncTask& task);
	~FoxSttySendRunnable();

public:// �麯���ӿ�
	virtual void run();

private:
	bool sendData();

private:
	FoxRestfulAsyncTask			task;
	FoxSttyDataManager*			datas;
	FoxRestfulAsyncTasks*		tasks;
};

