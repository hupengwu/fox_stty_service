#include "FoxSttyDataManager.h"
#include "FoxIteratorGetStty.h"

#include <FoxFile.h>
#include <FoxJSonObject.h>
#include <FoxLoggerFactory.h>

ILogger* FoxSttyDataManager::logger = FoxLoggerFactory::getLogger();

FoxSttyDataManager::FoxSttyDataManager()
{
}

FoxSttyDataManager::~FoxSttyDataManager()
{
}

bool FoxSttyDataManager::init()
{
	// �����ݴ��ļ�װ�ص��ڴ�
	this->load();

	logger->info("data manager init success!");
	return true;
}

bool FoxSttyDataManager::exit()
{
	// �����ݱ��浽�ļ�
	this->save();

	// ��kvmaper�������ת�Ƴ���
	map<string, FoxSttyItem*> k2v;
	this->kvmapper.swap(k2v);	

	// ����ڴ�
	for(map<string, FoxSttyItem*>::iterator it = k2v.begin(); it != k2v.end(); it++)
	{
		delete it->second;
	}
	k2v.clear();

	logger->info("data manager exit success!");
	return true;
}

bool FoxSttyDataManager::load()
{	
	// <1> ���ļ��ж�ȡJson�ַ����ı�
	string jsonLoad;
	FoxFile::readTextFile("./data.jsn", jsonLoad);

	// <2> ��Jsonת���ɶ���
	list<FoxSttyItem*> sttyItemList;	
	this->makeJSonItem(jsonLoad, sttyItemList);

	// <3> ����Ҫ��һ������
	if (sttyItemList.empty())
	{
		FoxSttyItem* itme = new FoxSttyItem();
		itme->getSettings().name = "ttyS1";
		sttyItemList.push_back(itme);
	}	

	// <2> ���������ֱ�׼���ķ���
	string jsonSave;
	this->makeItem2JSon(sttyItemList, jsonSave);

	// <3> ��֤���浵�ļ������Ƿ�Ϊ��ʽ��
	if (jsonSave != jsonLoad)
	{
		FoxFile::writeTextFile("./data.jsn", jsonSave);
	}

	// <4> ������װ�������
	map<string, FoxSttyItem*> k2v;
	for (FoxSttyItem* item : sttyItemList)
	{
		FoxSttyItemSettings& settings = item->getSettings();
		k2v[settings.name] = item;
	}
	this->kvmapper.swap(k2v);

	return true;
}

bool FoxSttyDataManager::save()
{
	// ��������
	string jsonTxt;
	this->makeItem2JSon(jsonTxt);
	return FoxFile::writeTextFile("./data.jsn", jsonTxt);
}

bool FoxSttyDataManager::makeItem2JSon(const list<FoxSttyItem*>& sttyItemList, string& jsnTxt)
{
	FoxJSonObject oJson;
	oJson.AddEmptySubArray("datas");
	FoxJSonObject& datas = oJson["datas"];

	for (FoxSttyItem* item : sttyItemList)
	{
		FoxSttyItemSettings settings = item->getSettings();

		FoxJSonObject oJsonSettings;
		oJsonSettings.Add("name", settings.name);
		oJsonSettings.Add("speed", settings.speed);
		oJsonSettings.Add("databits", settings.databits);
		oJsonSettings.Add("stopbits", settings.stopbits);
		oJsonSettings.Add("recv_timeout", settings.recv_timeout);
		switch (settings.parity)
		{
		case fox::TTYParity::N: {
			oJsonSettings.Add("parity", "N");
			break;
		}
		case fox::TTYParity::E: {
			oJsonSettings.Add("parity", "E");
			break;
		}
		case fox::TTYParity::O: {
			oJsonSettings.Add("parity", "O");
			break;
		}
		case fox::TTYParity::S: {
			oJsonSettings.Add("parity", "S");
			break;
		}
		default:
			break;
		}
		datas.Add(oJsonSettings);
	}

	jsnTxt = oJson.ToFormattedString();
	return true;
}

bool FoxSttyDataManager::makeItem2JSon(string& jsnTxt)
{
	// ��ȡ����
	FoxIteratorSttyGetConfig iterator;
	this->kvmapper.foreach(iterator);

	// ��������
	this->makeItem2JSon(iterator.itemList, jsnTxt);
	return true;
}

bool FoxSttyDataManager::makeJSonItem(const string& jsnTxt, list<FoxSttyItem*>& sttyItemList)
{
	FoxJSonObject oJson;
	if (!oJson.Parse(jsnTxt))
	{
		return false;
	}

	FoxJSonObject& datas = oJson["datas"];
	if (!datas.IsArray())
	{
		return false;
	}

	int length = datas.GetArraySize();
	for (int i = 0; i < length; i++)
	{
		FoxSttyItemSettings settings;

		FoxJSonObject& jsonSettings = datas[i];
		jsonSettings.Get("name", settings.name);
		jsonSettings.Get("speed", settings.speed);
		jsonSettings.Get("databits", settings.databits);
		jsonSettings.Get("stopbits", settings.stopbits);
		jsonSettings.Get("recv_timeout", settings.recv_timeout);

		string parity;
		jsonSettings.Get("parity", parity);
		if (parity == "N")
		{
			settings.parity = fox::TTYParity::N;
		}
		if (parity == "E")
		{
			settings.parity = fox::TTYParity::E;
		}
		if (parity == "O")
		{
			settings.parity = fox::TTYParity::O;
		}
		if (parity == "S")
		{
			settings.parity = fox::TTYParity::S;
		}

		FoxSttyItem* item = new FoxSttyItem();
		item->setSettings(settings);

		sttyItemList.push_back(item);
	}

	return true;
}

STLKVMapper<string, FoxSttyItem*>& FoxSttyDataManager::getKVMapper()
{
	return this->kvmapper;
}



