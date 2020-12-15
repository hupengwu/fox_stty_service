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
	* 预处理json
	*/
	virtual string doJson(string& json);

private:
	/*
	* 分派请求
	*/
	virtual string dispatch(const string& method, const string& resource, const string& body);

private:
	virtual string onGetSettings(const string& body);
	virtual string onGetDatas(const string& body);
	virtual string onSendData(const string& body);

private:
	Settings*			settings;
	FoxSttyDataManager* datas;
	FoxSttyService*		service;
};

