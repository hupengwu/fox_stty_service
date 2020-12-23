#pragma once

#include <string>
#include <ILogger.h>

using namespace std;

class Settings
{
public:
	Settings();
	virtual ~Settings();

public:
	void load();
	bool save();

public:
	string toJSon();
	bool   fromJSon(const string& json);

public:
	int getServicePort();

private:
	/*
	* ÒµÎñ¶Ë¿Ú
	*/
	int service_port;

	static ILogger* logger;
};

