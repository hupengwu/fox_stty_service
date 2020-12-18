#pragma once

#include <STLRunnable.h>
#include <FoxSttyDataManager.h>
#include "FoxSttyTaskList.h"


class FoxSttySendRunnable : public STLRunnable
{
public:
	FoxSttySendRunnable(FoxSttyDataManager* dataMgr, FoxSttyTaskList* tasks,AsyncTask& task);
	~FoxSttySendRunnable();

public:// Ðéº¯Êý½Ó¿Ú
	virtual void run();

private:
	bool sendData();

private:
	AsyncTask			task;
	FoxSttyDataManager* dataMgr;
	FoxSttyTaskList*	tasks;
};

