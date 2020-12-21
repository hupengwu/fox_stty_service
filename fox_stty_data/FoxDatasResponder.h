#pragma once

#include <FoxRestfulResponder.h>

#include "FoxSttyDataManager.h"

class FoxDatasResponder : public FoxRestfulResponder
{
public:
	FoxDatasResponder(FoxSttyDataManager* datas);
	virtual ~FoxDatasResponder();

public:
	/*
	* ÏìÓ¦ÏûÏ¢
	*/
	virtual string respond(const string& resource, const string& method, const string& body);

private:
	FoxSttyDataManager* datas;
};

