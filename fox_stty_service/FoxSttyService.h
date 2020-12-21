#pragma once

#include <FoxSttyDataManager.h>
#include <ILogger.h>
#include <STLAsyncTask.h>

#include <FoxRestfulAsyncTasks.h>

class FoxSttyService
{
public:
	FoxSttyService();
	virtual ~FoxSttyService();

public:
	void bind(FoxSttyDataManager& datas, FoxRestfulAsyncTasks& tasks);
	bool init();
	bool exit();

public:
	FoxRestfulAsyncTasks& getTasks();

private:
	static ILogger*			logger;
	FoxSttyDataManager*		datas;
	FoxRestfulAsyncTasks*	tasks;
};

