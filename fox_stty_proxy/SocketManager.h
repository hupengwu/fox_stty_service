#pragma once

#include <FoxTcpServerSocket.h>
#include <Settings.h>
#include <FoxSttyDataManager.h>
#include <FoxSttyService.h>

class SocketManager
{
public:
	SocketManager();
	virtual ~SocketManager();

public:
	bool bind(Settings& settings, FoxSttyDataManager& datas, FoxSttyService& service);
	bool init();
	bool exit();

private:
	FoxTcpServerSocket	serverSocket;
	Settings*			settings;
	FoxSttyDataManager* datas;
	FoxSttyService*		service;
	static ILogger*		logger;
};

