#include <iostream>
#include <chrono>

#include "Algorithms/Algorithms.h"

struct Timer {
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
public:
	Timer() {};
	void startTimer() {
		start = std::chrono::high_resolution_clock::now();
	}

	std::chrono::duration<float> endTimer() {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " ms" << std::endl;
		return duration;
	}
};

template <typename Iter>
void printCointainer(Iter it, Iter end) {
	for (; it != end; ++it) { std::cout << *it << " "; }
	std::cout << std::endl;
}


int main()
{
	std::cout << "Hello World" << std::endl;
	return 1;
}