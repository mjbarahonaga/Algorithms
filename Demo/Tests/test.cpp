// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <chrono> //For std::chrono
#include <yvals_core.h>
#include <type_traits>
#include <sstream> //For std::stringstream
#include <fstream> //For std::ofstream
#include <iomanip> //For std::setprecision
#include <vector>

#include "test.hpp"
#include "algorithms.h"

static constexpr size_t g_ITERATIONS = 10;
static constexpr size_t g_ARRAYSIZE = 3; // 1->10, 2->100, 3->1000...
static constexpr size_t g_DIGITSNUMBER = 3; // // 1->9, 2->99, 3->999...
static std::stringstream s_FileBuffer;

struct DataTimes {
	DataTimes(std::chrono::duration<double> b, std::chrono::duration<double> a,
		std::chrono::duration<double> w) : best(b), average(a), worst(w) {}
	std::chrono::duration<double> best;
	std::chrono::duration<double> average;
	std::chrono::duration<double> worst;
};


struct DataSort
{
	DataSort(const size_t& cs, const char* sn, const char* st,
		const bool s, std::chrono::duration<double> b, std::chrono::duration<double> a,
		std::chrono::duration<double> w) : container_size(cs), sort_name(sn), sort_type(st),
		sorted(s), dataTimes(a, b, w) {}

	_NODISCARD INLINE const size_t getContainerSize() noexcept { return container_size; }
	_NODISCARD INLINE const char* getSortName() noexcept { return sort_name; }
	_NODISCARD INLINE const char* getSortType() noexcept { return sort_type; }
	_NODISCARD INLINE const bool isSorted() noexcept { return sorted; }
	_NODISCARD INLINE const std::chrono::duration<double> getBest() noexcept { return dataTimes.best; }
	_NODISCARD INLINE const std::chrono::duration<double> getAverage() noexcept { return dataTimes.average; }
	_NODISCARD INLINE const std::chrono::duration<double> getWorst() noexcept { return dataTimes.worst; }
	INLINE void setSortName(const char* Name) noexcept { sort_name = Name; }
	INLINE void setSortType(const char* Type) noexcept { sort_type = Type; }
	INLINE void setSortType(const bool b) noexcept { sorted = b; }
	INLINE void setContainerSize(const size_t& size) noexcept { container_size = size; }
	INLINE void setBest(const std::chrono::duration<double>& best) noexcept { dataTimes.best = best; }
	INLINE void setAverage(const std::chrono::duration<double>& average) noexcept { dataTimes.average = average; }
	INLINE void setWorst(const std::chrono::duration<double>& worst) noexcept { dataTimes.worst = worst; }
private:
	size_t container_size;
	const char* sort_name;
	const char* sort_type;
	bool sorted;
	DataTimes dataTimes;
};


struct Timer {
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<double> duration;
public:
	Timer() {};
	INLINE void startTimer() noexcept{
		start = std::chrono::high_resolution_clock::now();
	}

	_NODISCARD INLINE std::chrono::duration<float> endTimer() noexcept{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		return duration;
	}
};

template<class It, class Type = typename std::iterator_traits<It>::value_type>
INLINE void FillRandomValues(It first, It last, const unsigned int max_number_digits) noexcept {

	const bool type_signed = std::is_signed<Type>::value;
	const bool floating_type = std::is_floating_point<Type>::value;

	const Type max_number = (Type)pow(10, max_number_digits);
	Type min_number = 0;

	if (type_signed) min_number = (-1 * max_number) + 1;

	std::random_device rd;
	std::mt19937 mt(rd());

	if constexpr (floating_type) {
		std::uniform_real_distribution<Type> dist((Type)min_number, (Type)max_number);

		for (; first != last; ++first) {
			const Type random_value = dist(mt);
			*first = random_value;
		}
	}
	else {
		std::uniform_int_distribution<Type> dist((Type)min_number, (Type)max_number);

		for (; first != last; ++first) {
			const Type random_value = dist(mt);
			*first = random_value;
		}
	}

}

template <typename It>
INLINE void PrintCointainer(It it, It last) noexcept {
	for (; it != last; ++it) { std::cout << *it << " "; }
	std::cout << std::endl;
}

template<class It>
static bool CheckVector(It first, It last, bool ascending = true) noexcept
{
	auto next_iterator = first;
	++next_iterator;
	if (ascending)
	{
		for (auto iterator = first; next_iterator != last; ++iterator, ++next_iterator)
		{
			if (*iterator > *next_iterator) { return false; }
		}
	}
	else
	{
		for (auto iterator = first; next_iterator != last; ++iterator, ++next_iterator)
		{
			if (*iterator < *next_iterator) { return false; }
		}
	}

	return true;
}

void SerializeResults() noexcept
{
	const std::string filename("Sort_Tests.txt");
	std::ofstream file;
	file.open(filename, std::ios::out | std::ios::app);
	file << s_FileBuffer.str();
	file.close();
	s_FileBuffer.clear();
	s_FileBuffer.flush();
	s_FileBuffer.str("");
}

void ClearFile() noexcept
{
	const std::string filename("Sort_Tests.txt");
	std::ofstream file;
	file.open(filename, std::ios::out | std::ios::trunc);
	file.close();
}

void WriteSeparator(const size_t line_size)
{
	for (size_t i = 0; i < line_size; ++i)
	{
		s_FileBuffer << "*";
	}
	s_FileBuffer << std::endl;
}

void WriteSpaceUntilEndOfLine(const size_t spaces)
{
	for (size_t i = 1; i < spaces; ++i)
	{
		s_FileBuffer << " ";
	}
	s_FileBuffer << "*" << std::endl;
}

void WriteResults(DataSort dSort)
{
	size_t elements_size = 0;
	size_t sort_type_size = strlen(dSort.getSortType());
	{
		size_t tmp = dSort.getContainerSize();
		while (tmp != 0)
		{
			++elements_size;
			tmp /= 10;
		}
	}
	const size_t line_size = elements_size > sort_type_size ? 15 + elements_size : 24 + sort_type_size;
	constexpr size_t precision = 20;

	WriteSeparator(line_size);
	size_t tmp = 2 + strlen(dSort.getSortName());
	s_FileBuffer << "* " << dSort.getSortName(); WriteSpaceUntilEndOfLine(line_size - tmp);
	tmp = 13 + strlen(dSort.getSortType());
	s_FileBuffer << "* Sort type: " << dSort.getSortType(); WriteSpaceUntilEndOfLine(line_size - tmp);
	tmp = 22 + elements_size;
	s_FileBuffer << "* Size of the container: " << dSort.getContainerSize(); WriteSpaceUntilEndOfLine(line_size - tmp);
	WriteSeparator(line_size);
	s_FileBuffer << (dSort.isSorted() ? "Sorted succesfully" : "Sorted failed") << std::endl;
	s_FileBuffer << "Best time:          " << std::fixed << std::setprecision(precision) << std::chrono::duration_cast<std::chrono::microseconds>(dSort.getBest()).count() << " microseconds" << std::endl;
	s_FileBuffer << "Worst time:         " << std::fixed << std::setprecision(precision) << std::chrono::duration_cast<std::chrono::microseconds>(dSort.getWorst()).count() << " microseconds" << std::endl;
	s_FileBuffer << "Average time:       " << std::fixed << std::setprecision(precision) << std::chrono::duration_cast<std::chrono::microseconds>(dSort.getAverage()).count() << " microseconds" << std::endl;
	s_FileBuffer << std::endl;
	s_FileBuffer << std::endl;
}


void Test::RunTest() noexcept
{
	ClearFile();
	BubbleSortTest();
	SelectionSortTest();
	SelectionSortDoubleTest();
	InsertionSortTest();
	ShellSortTest();
}



void Test::BubbleSortTest() noexcept{
	for (size_t i = 0; i < g_ARRAYSIZE; ++i) {
		std::vector<int> vi;
		vi.resize((size_t)pow(10, 1 + i));
		BubbleRandomTest(vi.begin(),vi.end(), vi.size(), "Vector int");
		
	}
}

void Test::SelectionSortTest() noexcept
{
	for (size_t i = 0; i < g_ARRAYSIZE; ++i) {
		std::vector<int> vi;
		vi.resize((size_t)pow(10, 1 + i));
		SelectionRandomTest(vi.begin(), vi.end(), vi.size(), "Vector int");
	}
}

void Test::SelectionSortDoubleTest() noexcept
{
	for (size_t i = 0; i < g_ARRAYSIZE; ++i) {
		std::vector<int> vi;
		vi.resize((size_t)pow(10, 1 + i));
		SelectionDoubleRandomTest(vi.begin(), vi.end(), vi.size(), "Vector int");
	}
}

void Test::InsertionSortTest() noexcept
{
	for (size_t i = 0; i < g_ARRAYSIZE; ++i) {
		std::vector<int> vi;
		vi.resize((size_t)pow(10, 1 + i));
		InsertionRandomTest(vi.begin(), vi.end(), vi.size(), "Vector int");
	}
}

void Test::ShellSortTest() noexcept
{
	for (size_t i = 0; i < g_ARRAYSIZE; ++i) {
		std::vector<int> vi;
		vi.resize((size_t)pow(10, 1 + i));
		ShellRandomTest(vi.begin(), vi.end(), vi.size(), "Vector int");
	}
}

template<class It>
void Test::BubbleRandomTest(It first, It last, size_t size, const std::string& Type) noexcept
{

	bool sorted = true;
	std::chrono::duration<double> best = std::chrono::duration<double, std::ratio<1>>(INFINITY);
	std::chrono::duration<double> average = std::chrono::duration<double, std::ratio<1>>(0);;
	std::chrono::duration<double> worst = std::chrono::duration<double, std::ratio<1>>(0);;
	std::cout << "Random Test with size: " << size  << std::endl;
	for (size_t j = 0; j < g_ITERATIONS; ++j)
	{
		std::cout << "\tIteration: " << j << std::endl;
		FillRandomValues(first, last, g_DIGITSNUMBER);
		Timer timer;
		timer.startTimer();
		alg::BubbleSort(first, last);
		std::chrono::duration<double> time = timer.endTimer();;
		average += time;
		if (time < best) { best = time; }
		if (time > worst) { worst = time; }
		if (sorted) { sorted = CheckVector(first,last); }
	}
	average /= g_ITERATIONS;
	std::string type = "Randomized ";
	type += Type;
	DataSort dSort(size, "Bubble Sort", type.c_str(), sorted, best, average, worst);
	WriteResults(dSort);
	SerializeResults();

}

template<class It>
void Test::SelectionRandomTest(It first, It last, size_t size, const std::string& Type) noexcept
{
	bool sorted = true;
	std::chrono::duration<double> best = std::chrono::duration<double, std::ratio<1>>(INFINITY);
	std::chrono::duration<double> average = std::chrono::duration<double, std::ratio<1>>(0);;
	std::chrono::duration<double> worst = std::chrono::duration<double, std::ratio<1>>(0);;
	std::cout << "Random Test with size: " << size << std::endl;
	for (size_t j = 0; j < g_ITERATIONS; ++j)
	{
		std::cout << "\tIteration: " << j << std::endl;
		FillRandomValues(first, last, g_DIGITSNUMBER);
		Timer timer;
		timer.startTimer();
		alg::SelectionSort(first, last);
		std::chrono::duration<double> time = timer.endTimer();;
		average += time;
		if (time < best) { best = time; }
		if (time > worst) { worst = time; }
		if (sorted) { sorted = CheckVector(first, last); }
	}
	average /= g_ITERATIONS;
	std::string type = "Randomized ";
	type += Type;
	DataSort dSort(size, "Selection Sort", type.c_str(), sorted, best, average, worst);
	WriteResults(dSort);
	SerializeResults();
}

template<class It>
void Test::SelectionDoubleRandomTest(It first, It last, size_t size, const std::string & Type) noexcept
{
	bool sorted = true;
	std::chrono::duration<double> best = std::chrono::duration<double, std::ratio<1>>(INFINITY);
	std::chrono::duration<double> average = std::chrono::duration<double, std::ratio<1>>(0);;
	std::chrono::duration<double> worst = std::chrono::duration<double, std::ratio<1>>(0);;
	std::cout << "Random Test with size: " << size << std::endl;
	for (size_t j = 0; j < g_ITERATIONS; ++j)
	{
		std::cout << "\tIteration: " << j << std::endl;
		FillRandomValues(first, last, g_DIGITSNUMBER);
		Timer timer;
		timer.startTimer();
		alg::SelectionDoubleSort(first, last);
		std::chrono::duration<double> time = timer.endTimer();;
		average += time;
		if (time < best) { best = time; }
		if (time > worst) { worst = time; }
		if (sorted) { sorted = CheckVector(first, last); }
	}
	average /= g_ITERATIONS;
	std::string type = "Randomized ";
	type += Type;
	DataSort dSort(size, "Selection Double Sort", type.c_str(), sorted, best, average, worst);
	WriteResults(dSort);
	SerializeResults();
}

template<class It>
void Test::InsertionRandomTest(It first, It last, size_t size, const std::string & Type) noexcept
{
	bool sorted = true;
	std::chrono::duration<double> best = std::chrono::duration<double, std::ratio<1>>(INFINITY);
	std::chrono::duration<double> average = std::chrono::duration<double, std::ratio<1>>(0);;
	std::chrono::duration<double> worst = std::chrono::duration<double, std::ratio<1>>(0);;
	std::cout << "Random Test with size: " << size << std::endl;
	for (size_t j = 0; j < g_ITERATIONS; ++j)
	{
		std::cout << "\tIteration: " << j << std::endl;
		FillRandomValues(first, last, g_DIGITSNUMBER);
		Timer timer;
		timer.startTimer();
		alg::InsertionSort(first, last);
		std::chrono::duration<double> time = timer.endTimer();;
		average += time;
		if (time < best) { best = time; }
		if (time > worst) { worst = time; }
		if (sorted) { sorted = CheckVector(first, last); }
	}
	average /= g_ITERATIONS;
	std::string type = "Randomized ";
	type += Type;
	DataSort dSort(size, "Insertion Sort", type.c_str(), sorted, best, average, worst);
	WriteResults(dSort);
	SerializeResults();
}

template<class It>
void Test::ShellRandomTest(It first, It last, size_t size, const std::string& Type) noexcept
{
	bool sorted = true;
	std::chrono::duration<double> best = std::chrono::duration<double, std::ratio<1>>(INFINITY);
	std::chrono::duration<double> average = std::chrono::duration<double, std::ratio<1>>(0);;
	std::chrono::duration<double> worst = std::chrono::duration<double, std::ratio<1>>(0);;
	std::cout << "Random Test with size: " << size << std::endl;
	for (size_t j = 0; j < g_ITERATIONS; ++j)
	{
		std::cout << "\tIteration: " << j << std::endl;
		FillRandomValues(first, last, g_DIGITSNUMBER);
		Timer timer;
		timer.startTimer();
		alg::ShellSort(first, last);
		std::chrono::duration<double> time = timer.endTimer();;
		average += time;
		if (time < best) { best = time; }
		if (time > worst) { worst = time; }
		if (sorted) { sorted = CheckVector(first, last); }
	}
	average /= g_ITERATIONS;
	std::string type = "Randomized ";
	type += Type;
	DataSort dSort(size, "Shell Sort", type.c_str(), sorted, best, average, worst);
	WriteResults(dSort);
	SerializeResults();
}