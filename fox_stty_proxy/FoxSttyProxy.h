#pragma once

#include <string>
#include <Settings.h>
#include <FoxSttyDataManager.h>
#include <FoxSttyService.h>
#include "IFoxSttyProxy.h"
#include <FoxRestfulResponderMapper.h>

using namespace std;

class FoxSttyProxy : public IFoxSttyProxy
{
public:
	FoxSttyProxy();
	virtual ~FoxSttyProxy();

public:
	void bind(Settings& settings, FoxRestfulResponderMapper& mapper);

public:
	/*
	* ‘§¥¶¿Ìjson
	*/
	virtual string doJson(string& json);

private:
	Settings*					settings;
	FoxRestfulResponderMapper*	mapper;
	
};

