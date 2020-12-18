#pragma once

#include <string>
#include <Settings.h>
#include <FoxSttyDataManager.h>
#include <FoxSttyService.h>
#include "IFoxSttyProxy.h"

using namespace std;

class FoxSttyProxy : public IFoxSttyProxy
{
public:
	FoxSttyProxy();
	virtual ~FoxSttyProxy();

public:
	void bind(Settings& settings, FoxSttyDataManager& datas, FoxSttyService& service);

public:
	/*
	* Ԥ����json
	*/
	virtual string doJson(string& json);

private:
	/*
	* ��������
	*/
	virtual string dispatch(const string& method, const string& resource, const string& body);

private:
	Settings*			settings;
	FoxSttyDataManager* datas;
	FoxSttyService*		service;
};

