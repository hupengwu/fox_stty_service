#include "Boot.h"
#include <FoxSettingsResponder.h>
#include <FoxDatasResponder.h>
#include <FoxServiceResponder.h>

Boot::Boot()
{
}

Boot::~Boot()
{
}

bool Boot::start()
{
	// <1> װ��ȫ�����ò���
	this->settings.load();

	// <2> ��ʼ������
	this->datas.init();

	// <3> ��ʼ��ҵ�����
	this->services.bind(this->datas, this->tasks);
	this->services.init();

	// <4> ��ʼ���������
	this->registResponder();
	this->threads.create(5);
	this->server.bind(this->settings, this->datas,this->mapper);
	this->server.init();


	return true;
}

bool Boot::close()
{
	this->threads.close();
	return true;
}

void Boot::registResponder()
{
	this->mapper.regist("\\fox_stty_service\\settings", "GET", new FoxSettingsResponder(&this->settings));
	this->mapper.regist("\\fox_stty_service\\settings", "PUT", new FoxSettingsResponder(&this->settings));
	this->mapper.regist("\\fox_stty_service\\datas", "GET", new FoxDatasResponder(&this->datas));
	this->mapper.regist("\\fox_stty_service\\services", "POST", new FoxServiceResponder(&this->services,&this->tasks, &this->datas,&this->threads));
	this->mapper.regist("\\fox_stty_service\\services", "GET", new FoxServiceResponder(&this->services, &this->tasks, &this->datas, &this->threads));
}
