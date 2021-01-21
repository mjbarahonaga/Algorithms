#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <random>
#include <yvals_core.h>
#include <type_traits>

#include "algorithms.h"


struct Timer {
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
public:
	Timer() {};
	__forceinline void startTimer() noexcept{
		start = std::chrono::high_resolution_clock::now();
	}

	__forceinline std::chrono::duration<float> endTimer(const std::string& functionName) noexcept{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << functionName.c_str() << " " 
			<< std::chrono::duration_cast<std::chrono::microseconds>(duration).count() 
			<< " us" << std::endl;
		return duration;
	}
};

template<class It, class T = typename std::iterator_traits<It>::value_type>
__forceinline void fillRandomValues(It first, It last, const unsigned int max_number_digits) noexcept {
	
	const bool type_signed = std::is_signed<T>::value;
	const bool floating_type = std::is_floating_point<T>::value;
	
	const T max_number = (T) pow(10, max_number_digits);
	T min_number = 0;

	if (type_signed) min_number = (-1 * max_number) + 1;

	std::random_device rd;
	std::mt19937 mt(rd());

	if constexpr (floating_type) {
		std::uniform_real_distribution<T> dist((T)min_number, (T)max_number);

		for (; first != last; ++first) {
			const T random_value = dist(mt);
			*first = random_value;
		}
	}
	else {
		std::uniform_int_distribution<T> dist((T)min_number, (T)max_number);

		for (; first != last; ++first) {
			const T random_value = dist(mt);
			*first = random_value;
		}
	}
	
}

template <typename Iter>
__forceinline void printCointainer(Iter it, Iter last) noexcept{
	for (; it != last; ++it) { std::cout << *it << " "; }
	std::cout << std::endl;
}


int main()
{
	Timer timer;
	std::vector<int> vi = { 4,1,0,-10,-5,3,-1,10,15,16,4 };
	std::vector<float> vf = { 4.3f,-1.1f,8.9f,-5.3f };
	std::list<int> li = { 4,1,0,-10,-5,3,-1,10,15,16,4 };
	int arr[] = { 2, 5, 7, 8, 2, 6, 9 };

	// Checking Sum ----------------------------------
	auto resVi = alg::sum(vi.begin(), vi.end());
	auto resLi = alg::sum(li.begin(), li.end());
	auto resVf = alg::sum(vf.begin(), vf.end());
	int size = 7;
	auto resAi = alg::sum(arr, arr + size);
	
	std::cout << "Result = " << resVi << std::endl;
	std::cout << "Result = " << resLi << std::endl;
	std::cout << "Result = " << resVf << std::endl;
	std::cout << "Result = " << resAi << std::endl;
	//--------------------------------------------------
	
	//BubbleSort ---------------------------------------
	printCointainer(vi.begin(), vi.end());
	timer.startTimer();
	alg::BubbleSort(vi.begin(), vi.end());
	timer.endTimer("BubbleSort");
	printCointainer(vi.begin(), vi.end());

	//--------------------------------------------------

	//RandomValues--------------------------------------
	std::cout << std::endl;
	std::cout << " Random Values Float" << std::endl;

	std::vector<float> random(200);
	
	fillRandomValues(random.begin(), random.end(), 2);
	
	printCointainer(random.begin(), random.end());
	
	std::cout << std::endl;
	
	timer.startTimer();
	alg::BubbleSort(random.begin(), random.end());
	timer.endTimer("BubbleSort Float");
	
	printCointainer(random.begin(), random.end());

	std::cout << std::endl;
	std::cout << " Random Values Int" << std::endl;
	std::vector<int> random2(200);
	fillRandomValues(random2.begin(), random2.end(), 2);
	printCointainer(random2.begin(), random2.end());
	std::cout << std::endl;
	timer.startTimer();
	alg::BubbleSort(random2.begin(), random2.end());
	timer.endTimer("BubbleSort Int");
	printCointainer(random2.begin(), random2.end());

	//--------------------------------------------------

	//Comparatives--------------------------------------

	std::vector<int> VBubble(200);

	fillRandomValues(VBubble.begin(), VBubble.end(), 2);

	std::vector<int> VSelection(VBubble);

	std::cout << std::endl;
	std::cout << " Comparatives Int Bubble vs Selection" << std::endl;

	std::cout << std::endl;
	timer.startTimer();
	alg::BubbleSort(VBubble.begin(), VBubble.end());
	timer.endTimer("BubbleSort Int");
	printCointainer(VBubble.begin(), VBubble.end());

	std::cout << std::endl;
	timer.startTimer();
	alg::SelectionSort(VSelection.begin(), VSelection.end());
	timer.endTimer("SelectionSort Int");
	printCointainer(VSelection.begin(), VSelection.end());
	//--------------------------------------------------

	return 1;
}