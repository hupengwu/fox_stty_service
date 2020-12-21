#pragma once

#include <FoxTcpServerSocket.h>
#include <Settings.h>
#include <FoxSttyDataManager.h>
#include <FoxSttyService.h>
#include <FoxRestfulResponderMapper.h>

class SocketManager
{
public:
	SocketManager();
	virtual ~SocketManager();

public:
	bool bind(Settings& settings, FoxSttyDataManager& datas, FoxRestfulResponderMapper& mapper);
	bool init();
	bool exit();

private:
	FoxTcpServerSocket	serverSocket;
	Settings* settings;
	FoxRestfulResponderMapper* mapper;
	FoxSttyDataManager* datas;
	static ILogger*		logger;
};

