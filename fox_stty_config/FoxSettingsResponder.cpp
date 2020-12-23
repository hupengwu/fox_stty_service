#include "FoxSettingsResponder.h"

FoxSettingsResponder::FoxSettingsResponder(Settings* settings)
{
	this->settings = settings;
}

FoxSettingsResponder::~FoxSettingsResponder()
{

}

std::string FoxSettingsResponder::respond(const string& resource, const string& method, const string& body)
{
	if (method == "GET")
	{
		return this->settings->toJSon();
	}
	if (method == "PUT")
	{
		if (this->settings->fromJSon(body))
		{
			this->settings->save();
		}

		return this->settings->toJSon();
	}
	
	return "";
}
