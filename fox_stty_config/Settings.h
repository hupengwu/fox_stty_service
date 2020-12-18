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
	void   fromJSon(const string& json);

	string	dispatch(const string& method, const string& resource, const string& body);

public:
	int getServicePort();

private:
	/*
	* ҵ��˿�
	*/
	int service_port;

	static ILogger* logger;
};

