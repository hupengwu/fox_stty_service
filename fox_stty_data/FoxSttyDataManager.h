#pragma once

#include <list>
#include <STLKVMapper.h>
#include <ILogger.h>
#include "FoxSttyItem.h"

using namespace std;

class FoxSttyDataManager
{
public:
	FoxSttyDataManager();
	virtual ~FoxSttyDataManager();

public:
	bool	init();
	bool	exit();
	bool	load();
	bool	save();

	bool	makeItem2JSon(const list<FoxSttyItem*>& sttyItemList, string& jsnTxt);
	bool	makeItem2JSon(string& jsnTxt);
	bool	makeJSonItem(const string& jsnTxt, list<FoxSttyItem*>& sttyItemList);

	string	dispatch(const string& method, const string& resource, const string& body);

public:
	STLKVMapper<string, FoxSttyItem*>& getKVMapper();

private:
	STLKVMapper<string, FoxSttyItem*> kvmapper;
	static	ILogger*				  logger;
	
};

