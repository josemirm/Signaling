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

#define SignalRoutine(code) (thread([this] { \
while (s.waitToTrigger()) { \
	code \
}})) \

#define ConfigSignal(signal, code) signal.setSignal(thread([this] { \
while (signal.waitToTrigger()) { \
	code \
}})) \

/*
thread([this] {
	while (s.waitToTrigger()) {
		{
			num++;
			printf("n: %i\n", num);
			fflush(stdout);
		}
	}
})
*/
class Signal {
public:
	Signal() {}
	
	~Signal() {
		{
			unique_lock<mutex> ul(mtx);
			triggerEnabled = false;
			running = false;
			condVar.notify_all();

		}
		signal.join();
	}


	void trigger() {
		if (triggerEnabled) {
			{
				unique_lock<mutex> ul(mtx);
				while (!running) {
					condVar.wait(ul);
				}
			}

			trigCount++;
			condVar.notify_one();
		}
	}


	void setTriggerEnable() {
		triggerEnabled = true;
	}
	bool isTriggerEnable() {
		return triggerEnabled;
	}


	int getPendingExecutions() {
		return trigCount;
	}

	bool waitToTrigger() {
		{
			unique_lock<mutex> ul(mtx);
			while (trigCount == 0 && running) {
				condVar.wait(ul);
			}
		}
		
		if (!running && trigCount == 0) return false;

		trigCount--;
		return true;
	}

	void setSignal(thread th) {
		signal = move(th);
		triggerEnabled = true;
		condVar.notify_all();
	}

private:
	thread signal;

	mutex mtx;
	condition_variable condVar;
	
	atomic<bool> triggerEnabled = true;
	atomic<bool> running = true;
	atomic<int> trigCount = 0;
};


#endif