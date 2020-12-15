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
	// ���ļ��ж�ȡJson�ַ����ı�
	string jsonLoad;
	FoxFile::readTextFile("./settings.jsn", jsonLoad);

	// ��Json�ַ���ȡ�����ݣ�����ļ���ʽ������Ҫ�󣬻����Ĭ�����õ�json�ַ���
	this->fromJSon(jsonLoad);

	// ��飺�����ļ��Ƿ���ڸ�ʽ������Ҫ��
	string jsonSave = this->toJSon();
	if (jsonSave != jsonLoad)
	{
		// ���±���Json�ı�
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
