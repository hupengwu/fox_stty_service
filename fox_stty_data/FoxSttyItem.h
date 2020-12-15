#pragma once

#include <string>
#include <mutex>
#include <FoxStty.h>
#include <STLByteArray.h>


using namespace fox;
using namespace std;

struct FoxSttyItemSettings
{
	/*
	* 串口的设备名称
	*/
	string name;

	/*
	* 波特率
	*/
	int speed = 9600;

	/*
	* 数据位
	*/
	int databits = 8;

	/*
	* 停止位
	*/
	int stopbits = 1;

	/*
	* 校验位
	*/
	TTYParity parity;

	/*
	* 一行的接收超时
	*/
	int recv_timeout = 1000 * 1000;
}; 

class FoxSttyItem
{
public:
	FoxSttyItem();
	virtual ~FoxSttyItem();

public:
	FoxSttyItemSettings&	getSettings();
	void setSettings(FoxSttyItemSettings& settings);

	FoxStty* getStty();
	void setStty(FoxStty* stty);

private:
	/*
	* 配置
	*/
	FoxSttyItemSettings settings;


	/*
	* 串口
	*/
	FoxStty*		stty;
};

