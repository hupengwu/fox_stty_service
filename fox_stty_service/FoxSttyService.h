#pragma once

#include <FoxSttyDataManager.h>
#include <ILogger.h>

class FoxSttyService
{
public:
	FoxSttyService();
	virtual ~FoxSttyService();

public:
	void bind(FoxSttyDataManager& dataMgr);
	bool init();
	bool exit();

public:
	bool sendData(const string& name, const STLByteArray& sendData, const long& timeOut, const bool& syncMode, STLByteArray& recvData);

private:
	FoxSttyDataManager* dataMgr;

	static ILogger*		logger;
	

};

