#pragma once

#include <FoxRestfulResponder.h>

#include "Settings.h"

class FoxSettingsResponder : public FoxRestfulResponder
{
public:
	FoxSettingsResponder(Settings* settings);
	virtual ~FoxSettingsResponder();

public:
	/*
	* ÏìÓ¦ÏûÏ¢
	*/
	virtual string respond(const string& resource, const string& method, const string& body);

private:
	Settings* settings;
};

