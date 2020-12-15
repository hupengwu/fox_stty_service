#include "FoxSttyProxy.h"
#include <FoxJSonObject.h>
#include <algorithm>

FoxSttyProxy::FoxSttyProxy()
{
}

FoxSttyProxy::~FoxSttyProxy()
{
}

void FoxSttyProxy::bind(Settings& settings, FoxSttyDataManager& datas, FoxSttyService& service)
{
	this->settings = &settings;
	this->datas = &datas;
	this->service = &service;
}

string FoxSttyProxy::doJson(string& json)
{
	FoxJSonObject oJson;
	if (!oJson.Parse(json))
	{
		return "json format error!";
	}

	string method;
	if (!oJson.Get("method", method))
	{
		return "not find method attrity";
	}

	string resource;
	if (!oJson.Get("resource", resource))
	{
		return "not find resource attrity";
	}

	string body;
	if (!oJson.Get("body", body))
	{
		return "not find body attrity";
	}

	std::transform(method.begin(), method.end(), method.begin(), ::toupper);

	oJson.Clear();

	return this->dispatch(method, resource, body);
}

string FoxSttyProxy::dispatch(const string& method, const string& resource, const string& body)
{
	if (resource == "\fox_stty_service\settings")
	{
		if (method == "GET")
		{
			return this->onGetSettings(body);
		}
	}
	else if (resource == "\fox_stty_service\datas")
	{
		if (method == "GET")
		{
			return this->onGetDatas(body);
		}
	}
	else if (resource == "\fox_stty_service\services")
	{
		if (method == "POST")
		{
			return this->onSendData(body);
		}
	}

	return "not find on method!";
}

string FoxSttyProxy::onGetSettings(const string& body)
{
	string json = this->settings->toJSon();
	return json;
}

string FoxSttyProxy::onGetDatas(const string& body)
{
	string json;
	this->datas->makeItem2JSon(json);
	return json;
}

string FoxSttyProxy::onSendData(const string& body)
{
	string jsn = "{" + body + "}";
//	this->service;
	return string();
}
