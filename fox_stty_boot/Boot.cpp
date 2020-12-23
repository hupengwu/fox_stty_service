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
	// <1> 装载全局配置参数
	this->settings.load();

	// <2> 初始化配置
	this->datas.init();

	// <3> 初始化业务对象
	this->services.bind(this->datas, this->tasks);
	this->services.init();

	// <4> 初始化对外服务
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
