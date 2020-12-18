#pragma once

#include <FoxSttyDataManager.h>
#include <ILogger.h>
#include <STLAsyncTask.h>

#include "FoxSttyTaskList.h"

class FoxSttyService
{
public:
	FoxSttyService();
	virtual ~FoxSttyService();

public:
	void bind(FoxSttyDataManager& dataMgr);
	bool init();
	bool exit();

public:
	string dispatch(const string& method, const string& resource, const string& body);

private:
	FoxSttyTaskList& getTasks();
	string toJson(const AsyncTask& task);

public:
	bool sendData(const string& name, const STLByteArray& sendData, const long& timeOut, const bool& syncMode, STLByteArray& recvData);

private:
	static ILogger*		logger;
	FoxSttyDataManager* dataMgr;
	FoxSttyTaskList		tasks;
	STLAsyncTask		threads;
};

