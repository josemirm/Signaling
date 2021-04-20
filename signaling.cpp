#include "signaling.h"

Signal::~Signal() {
	{
		unique_lock<mutex> ul(mtx);
		triggerEnabled = false;
		running = false;
		condVar.notify_all();

	}
	signal.join();
}

void Signal::trigger() {
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

bool Signal::waitToTrigger() {
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

void Signal::setSignal(thread th) {
	signal = move(th);
	triggerEnabled = true;
	condVar.notify_all();
}


