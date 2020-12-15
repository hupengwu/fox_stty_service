#pragma once

#include <Settings.h>
#include <FoxSttyDataManager.h>
#include <FoxSttyService.h>
#include <SocketManager.h>

class Boot
{
public:
	Boot();
	virtual ~Boot();

public:
	bool	start();

private:
	Settings			settings;
	FoxSttyDataManager	datas;
	FoxSttyService		services;
	SocketManager		server;

};

