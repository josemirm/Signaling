// josemirm
// 6&

#include <cstdio>
#include "signaling.h"

using namespace std;

class ExampleClass
{
public:
	ExampleClass() {
		ConfigSignal(sig, {
			printf("n: %i\n", num++);
			fflush(stdout);
		});
	};

	void trigger() {
		sig.trigger();
	}
private:
	int num = 3;
	Signal sig;
};


int main() {
	ExampleClass obj;

	obj.trigger();

	return 0;
}
