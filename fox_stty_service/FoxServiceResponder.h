#pragma once

#include <FoxRestfulResponder.h>

#include "FoxSttyService.h"

class FoxServiceResponder : public FoxRestfulResponder
{
public:
	FoxServiceResponder(FoxSttyService* service, FoxRestfulAsyncTasks* tasks, FoxSttyDataManager* datas, STLAsyncTask* threads);
	virtual ~FoxServiceResponder();

public:
	/*
	* œÏ”¶œ˚œ¢
	*/
	virtual string respond(const string& resource, const string& method, const string& body);

private:
	virtual string respondGet(const string& resource,const string& body);
	virtual string respondPost(const string& resource, const string& body);

private:
	FoxSttyService* service;
	FoxRestfulAsyncTasks* tasks;
	FoxSttyDataManager* datas;
	STLAsyncTask*	threads;
};
