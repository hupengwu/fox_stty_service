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

void FoxSttyService::bind(FoxSttyDataManager& dataMgr)
{
	this->dataMgr = &dataMgr;
}

bool FoxSttyService::init()
{
	STLKVMapper<string, FoxSttyItem*>& kvmapper = this->dataMgr->getKVMapper();

	set<string> keys;
	kvmapper.getKeys(keys);
	for (string key : keys)
	{
		// ȡ��ֵ
		FoxSttyItem* value = nullptr;
		if (!kvmapper.get(key, value))
		{
			continue;
		}

		// ��飺�Ƿ��Ѿ�����Stty����
		FoxStty* stty = value->getStty();
		if (stty == nullptr)
		{
			// ��Ϊ���value��ָ�룬����ʵ����ֱ�Ӳ�����������
			stty = new FoxStty();
			stty->bindHandler(new FoxSttyRecvHandler(&this->tasks));
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

	// �����̳߳�
	this->threads.create(3);

	logger->info("init service sucess!");
	return true;
}

bool FoxSttyService::exit()
{
	// �ر��̳߳�
	this->threads.close();

	STLKVMapper<string, FoxSttyItem*>& kvmapper = this->dataMgr->getKVMapper();

	set<string> keys;
	kvmapper.getKeys(keys);
	for (string key : keys)
	{
		// ȡ��ֵ
		FoxSttyItem* value = nullptr;
		if (!kvmapper.get(key, value))
		{
			continue;
		}

		// ��飺�Ƿ��Ѿ�����Stty����
		FoxStty* stty = value->getStty();
		if (stty == nullptr)
		{
			continue;
		}

		// �رմ���
		stty->close();

		// �ͷ��ڴ�
		delete stty;
		value->setStty(nullptr);

		// ɾ��������������
		kvmapper.remove(key);

		logger->info("open stty sucess = %s", key.c_str());
	}

	logger->info("exit service sucess!");
	return true;
}

FoxSttyTaskList& FoxSttyService::getTasks()
{
	return this->tasks;
}

string FoxSttyService::toJson(const AsyncTask& task)
{
	FoxJSonObject oJsn;
	oJsn.Add("id", task.id);
	oJsn.Add("request", task.request);
	oJsn.Add("respond", task.respond);
	oJsn.Add("request", task.request);
	oJsn.Add("status", task.status);
	oJsn.Add("request_time", (uint64)task.requestTime);
	oJsn.Add("respond_time", (uint64)task.respondTime);
	oJsn.Add("life_cycle", (uint64)task.lifeCycle);

	return oJsn.ToFormattedString();
}

string FoxSttyService::dispatch(const string& method, const string& resource, const string& body)
{
	FoxJSonObject oJson;
	if (!oJson.Parse(body))
	{
		return "json format error!";
	}

	string name;
	if (!oJson.Get("name", name))
	{
		return "not find name attrity";
	}

	string data;
	if (!oJson.Get("data", data))
	{
		return "not find data attrity";
	}

	int time_out;
	if (!oJson.Get("time_out", time_out))
	{
		return "not find time_out attrity";
	}

	// ��¼����
	AsyncTask task;
	task.request = body;
	tasks.pushTask(task);	
	this->tasks.processTask(task);

	// �������ύ���첽����ȥ����
	FoxSttySendRunnable* runnable = new FoxSttySendRunnable(this->dataMgr, &this->tasks,task);
	this->threads.execute(runnable);

	return this->toJson(task);
}

bool FoxSttyService::sendData(const string& name, const STLByteArray& sendData, const long& timeOut, const bool& syncMode, STLByteArray& recvData)
{
	STLKVMapper<string, FoxSttyItem*>& kvmapper = this->dataMgr->getKVMapper();

	FoxSttyItem* value = nullptr;
	if (!kvmapper.get(name, value))
	{
		return false;
	}

	FoxStty* stty = value->getStty();
	if (stty == nullptr)
	{
		return false;
	}

	// ���������ճ�ʱ
	stty->setRcvTimeOut(timeOut * 1000);

	int length = 0;
	if (!stty->sendData((const char*)sendData.getData(), sendData.getSize(), length))
	{
		return false;
	}
		

	return true;
}
