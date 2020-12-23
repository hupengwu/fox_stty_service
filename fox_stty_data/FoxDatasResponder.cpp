#include "FoxDatasResponder.h"

FoxDatasResponder::FoxDatasResponder(FoxSttyDataManager* datas)
{
	this->datas = datas;
}

FoxDatasResponder::~FoxDatasResponder()
{

}

std::string FoxDatasResponder::respond(const string& resource, const string& method, const string& body)
{
	string json;
	this->datas->makeItem2JSon(json,false);
	return json;
}
