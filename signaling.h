// josemirm
// 6&

#ifndef __SIGNALING_H__
#define __SIGNALING_H_

#include <atomic>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <typeinfo>
#include <vector>


using namespace std;

#define ConfigSignal(signal, code) signal.setSignal(thread([this] { \
while (signal.waitToTrigger()) { \
	code \
}})) \


class Signal {
public:
	Signal() {}
	~Signal();
	
	inline void setTriggerEnable() {
		triggerEnabled = true;
	}

	inline bool isTriggerEnable() {
		return triggerEnabled;
	}


	inline int getPendingExecutions() {
		return trigCount;
	}

	void trigger();
	bool waitToTrigger();
	void setSignal(thread th);

private:
	thread signal;

	mutex mtx;
	condition_variable condVar;
	
	atomic<bool> triggerEnabled = true;
	atomic<bool> running = true;
	atomic<int> trigCount = 0;
};


#endif