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
	return this->settings->toJSon();
}
