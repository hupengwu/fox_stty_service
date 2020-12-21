#include "FoxSttyProxy.h"
#include <FoxJSonObject.h>
#include <algorithm>

FoxSttyProxy::FoxSttyProxy()
{
}

FoxSttyProxy::~FoxSttyProxy()
{
}

void FoxSttyProxy::bind(Settings& settings,  FoxRestfulResponderMapper& mapper)
{
	this->settings = &settings;
	this->mapper = &mapper;
}

string FoxSttyProxy::doJson(string& json)
{
	FoxJSonObject jsnRecv;
	if (!jsnRecv.Parse(json))
	{
		return "json format error!";
	}

	string method;
	if (!jsnRecv.Get("method", method))
	{
		return "not find method attributes";
	}

	string resource;
	if (!jsnRecv.Get("resource", resource))
	{
		return "not find resource attributes";
	}

	string body;
	if (!jsnRecv.Get("body", body))
	{
		return "not find body attributes";
	}

	std::transform(method.begin(), method.end(), method.begin(), ::toupper);

	FoxRestfulResponder* responder = this->mapper->getResponder(resource, method);
	if (responder == nullptr)
	{
		return "not find responder for resource and method!";
	}

	return responder->respond(resource, method,body);
}


