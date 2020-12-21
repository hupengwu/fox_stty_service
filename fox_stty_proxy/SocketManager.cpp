#include "SocketManager.h"
#include "FoxTcpServerSttyHandler.h"
#include "FoxSttyProxy.h"
#include <FoxLoggerFactory.h>

ILogger* SocketManager::logger = FoxLoggerFactory::getLogger();

SocketManager::SocketManager()
{
	this->settings = nullptr;
	this->datas = nullptr;
	this->mapper = nullptr;
}

SocketManager::~SocketManager()
{
}

bool SocketManager::bind(Settings& settings, FoxSttyDataManager& datas, FoxRestfulResponderMapper& mapper)
{
	this->settings = &settings;
	this->datas = &datas;
	this->mapper = &mapper;
	return true;
}

bool SocketManager::init()
{
	FoxSttyProxy* proxy = new FoxSttyProxy();
	proxy->bind(*this->settings, *this->mapper);

	FoxTcpServerSttyHandler* handler = new FoxTcpServerSttyHandler(proxy);
	this->serverSocket.bindHandler(handler);

	if (!this->serverSocket.create(this->settings->getServicePort()))
	{
		logger->error("create server socket port = %d failed!", this->settings->getServicePort());
		return false;
	}

	int serverPort = this->settings->getServicePort();
	logger->info("create server socket port = %d success!", serverPort);
	return true;
}

bool SocketManager::exit()
{
	this->serverSocket.close();

	return true;
}
