#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include "algorithms.h"

using namespace std;

struct Timer {
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
public:
	Timer() {};
	void startTimer() {
		start = std::chrono::high_resolution_clock::now();
	}

	std::chrono::duration<float> endTimer(string functionName) {
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << functionName.c_str() << " " 
			<< std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() 
			<< " ms" << std::endl;
		return duration;
	}
};

template <typename Iter>
void printCointainer(Iter it, Iter last) {
	for (; it != last; ++it) { std::cout << *it << " "; }
	std::cout << std::endl;
}


int main()
{
	Timer timer;
	vector<int> vi = { 4,1,0,-10,-5,3,-1,10,15,16,4 };
	vector<float> vf = { 4.3f,-1.1f,8.9f,-5.3 };
	list<int> li = { 4,1,0,-10,-5,3,-1,10,15,16,4 };
	int arr[] = { 2, 5, 7, 8, 2, 6, 9 };

	// Checking Sum ----------------------------------
	auto resVi = alg::sum(vi.begin(), vi.end());
	auto resLi = alg::sum(li.begin(), li.end());
	auto resVf = alg::sum(vf.begin(), vf.end());
	int size = 7;
	auto resAi = alg::sum(arr, arr + size);
	
	cout << "Result = " << resVi << endl;
	cout << "Result = " << resLi << endl;
	cout << "Result = " << resVf << endl;
	cout << "Result = " << resAi << endl;
	//--------------------------------------------------
	
	//BubbleSort ---------------------------------------
	printCointainer(vi.begin(), vi.end());
	timer.startTimer();
	alg::BubbleSort(vi.begin(), vi.end());
	timer.endTimer("BubbleSort");
	printCointainer(vi.begin(), vi.end());

	//--------------------------------------------------

	return 1;
}