#include "Boot.h"

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
	this->services.bind(this->datas);
	this->services.init();

	// <4> 初始化对外服务
	this->server.bind(this->settings, this->datas, this->services);
	this->server.init();



	return true;
}
