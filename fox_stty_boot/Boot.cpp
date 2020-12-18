#include "Boot.h"

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
	this->services.bind(this->datas);
	this->services.init();

	// <4> ��ʼ���������
	this->server.bind(this->settings, this->datas, this->services);
	this->server.init();



	return true;
}
