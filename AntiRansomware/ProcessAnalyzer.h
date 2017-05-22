#pragma once

#include <windows.h>

#include <exception>
#include <map>
#include <functional>
#include <string>

#include "EventTypes.h"
#include "ProcessPolicy.h"
#include "HoneypotsManager.h"

/* includes for hooking */
#include "MessageHandlerWrapper.h"
#include "ProcessHookMonitorWrapper.h"

using std::exception;
using std::map;
using std::wstring;

class ProcessesMonitor;

/* This represent an analyzer for one process in the system */
class ProcessAnalyzer : public FunctionCalledHandlerWrapper
{
private:
	ProcessesMonitor *processesMonitor;
	const HoneypotsManager *honeypotsManager;
	HANDLE processHandle;
	DWORD parentID;
	unsigned int currentScore;
	
	void setHooks(DWORD proccessID);
	DWORD GetParentProcessID(DWORD dwProcessID);

public:
	ProcessAnalyzer(DWORD proccessID, ProcessesMonitor *processesMonitor, const HoneypotsManager *honeypotsManager);
	~ProcessAnalyzer();
	DWORD getProcessID() const;
	DWORD getParentID();
	bool isProcessStillActive() const;
	bool checkIfAlert() const;
	bool updateScore(ProcessPolicy::ProcessOperation processOperation);
	void parseHookNotification(const wstring& functionName, const wstring& param);

	virtual void report(int pid, LPUWSTR functionName, LPUWSTR param);
};

class ProcessAnalyzerException : public exception {};

