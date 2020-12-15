#include "Settings.h"
#include <FoxFile.h>
#include <FoxJSonObject.h>
#include <FoxLoggerFactory.h>

ILogger* Settings::logger = FoxLoggerFactory::getLogger();

Settings::Settings()
{
}

Settings::~Settings()
{
}

void Settings::load()
{
	// 从文件中读取Json字符串文本
	string jsonLoad;
	FoxFile::readTextFile("./settings.jsn", jsonLoad);

	// 从Json字符串取出数据：如果文件格式不符合要求，会产生默认配置的json字符串
	this->fromJSon(jsonLoad);

	// 检查：配置文件是否存在格式不符合要求
	string jsonSave = this->toJSon();
	if (jsonSave != jsonLoad)
	{
		// 重新保存Json文本
		this->save();
	}	

	logger->info("load settings sucess!");
}

bool Settings::save()
{
	string jsonTxt = this->toJSon();
	if (!FoxFile::writeTextFile("./settings.jsn", jsonTxt))
	{
		logger->error("save settings failed!");
	}

	logger->info("save settings sucess!");
}

string Settings::toJSon()
{
	FoxJSonObject oJson;
	oJson.AddEmptySubObject("settings");
	FoxJSonObject& settings = oJson["settings"];
	settings.Add("service_port", this->service_port);

	return oJson.ToFormattedString();
}

void Settings::fromJSon(const string& json)
{
	FoxJSonObject oJson;
	oJson.Parse(json);

	if (!oJson["settings"].Get("service_port", this->service_port))
	{
		this->service_port = 5100;
	}

}

int Settings::getServicePort()
{
	return this->service_port;
}
