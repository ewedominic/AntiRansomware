#pragma once

#include <map>

#include "MessageHandlerWrapper.h"
#include "ProcessAnalyzer.h"
#include "EventTypes.h"

using std::map;

class ProcessesMonitor : public MessageHandlerWrapper
{
private:
	const HoneypotsManager *honeypotsManager;
	map<unsigned int, ProcessAnalyzer *> processAnalyzers;

	void initProcessAnalyzers();
public:
	void addNewProcess(unsigned int processID);
	void checkProcessesLiveness();
	ProcessesMonitor(const HoneypotsManager *honeypotsManager);
	ProcessesMonitor(const HoneypotsManager * honeypotsManager, unsigned int pid); //TODO for debug only
	virtual void report(int pid, LPUWSTR functionName);
	~ProcessesMonitor();
};

class ProcessesMonitorException : public exception {};