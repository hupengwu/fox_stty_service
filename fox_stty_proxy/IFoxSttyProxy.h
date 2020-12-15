#pragma once

#include <string>

using namespace std;

class IFoxSttyProxy
{
public:
	IFoxSttyProxy() {};
	virtual ~IFoxSttyProxy() {};

public:
	virtual string doJson(string& json) = 0;
};

