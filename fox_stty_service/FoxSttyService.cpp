#include "FoxSttyService.h"
#include "FoxSttyRecvHandler.h"
#include "FoxSttySendRunnable.h"

#include <FoxIteratorGetStty.h>
#include <FoxLoggerFactory.h>
#include <FoxJSonObject.h>


ILogger* FoxSttyService::logger = FoxLoggerFactory::getLogger();

FoxSttyService::FoxSttyService()
{
}

FoxSttyService::~FoxSttyService()
{
}

void FoxSttyService::bind(FoxSttyDataManager& datas, FoxRestfulAsyncTasks& tasks)
{
	this->datas = &datas;
	this->tasks = &tasks;
}

bool FoxSttyService::init()
{
	STLKVMapper<string, FoxSttyItem*>& kvmapper = this->datas->getKVMapper();

	set<string> keys;
	kvmapper.getKeys(keys);
	for (string key : keys)
	{
		// 取出值
		FoxSttyItem* value = nullptr;
		if (!kvmapper.get(key, value))
		{
			continue;
		}

		// 检查：是否已经分配Stty对象
		FoxStty* stty = value->getStty();
		if (stty == nullptr)
		{
			// 因为这个value是指针，所以实际上直接操作的是属性
			stty = new FoxStty();
			stty->bindHandler(new FoxSttyRecvHandler(this->tasks));
			value->setStty(stty);
		}

		if (stty->isOpen())
		{
			continue;
		}

		FoxSttyItemSettings& settings = value->getSettings();
		if (!stty->open(settings.name.c_str()))
		{
			logger->error("open stty failed = %s", key.c_str());
			continue;
		}

		stty->setRcvTimeOut(settings.recv_timeout);

		if (!stty->setParam(settings.speed, settings.databits, settings.stopbits, settings.parity))
		{
			logger->error("set param stty failed = %s", key.c_str());
			continue;
		}

		

		logger->info("open stty sucess = %s", key.c_str());
	}

	logger->info("init service sucess!");
	return true;
}

bool FoxSttyService::exit()
{
	STLKVMapper<string, FoxSttyItem*>& kvmapper = this->datas->getKVMapper();

	set<string> keys;
	kvmapper.getKeys(keys);
	for (string key : keys)
	{
		// 取出值
		FoxSttyItem* value = nullptr;
		if (!kvmapper.get(key, value))
		{
			continue;
		}

		// 检查：是否已经分配Stty对象
		FoxStty* stty = value->getStty();
		if (stty == nullptr)
		{
			continue;
		}

		// 关闭串口
		stty->close();

		// 释放内存
		delete stty;
		value->setStty(nullptr);

		// 删除管理器的数据
		kvmapper.remove_if(key);

		logger->info("open stty sucess = %s", key.c_str());
	}

	logger->info("exit service sucess!");
	return true;
}

FoxRestfulAsyncTasks& FoxSttyService::getTasks()
{
	return *this->tasks;
}


