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
	* ���ڵ��豸����
	*/
	string name;

	/*
	* ������
	*/
	int speed = 9600;

	/*
	* ����λ
	*/
	int databits = 8;

	/*
	* ֹͣλ
	*/
	int stopbits = 1;

	/*
	* У��λ
	*/
	TTYParity parity;

	/*
	* һ�еĽ��ճ�ʱ
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
	* ����
	*/
	FoxSttyItemSettings settings;


	/*
	* ����
	*/
	FoxStty*		stty;
};

