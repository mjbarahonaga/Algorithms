#pragma once

#ifdef _WIN64
#define PLATFORM_WINDOWS 1
#define ARCHITECTURE_64 1
#elif _WIN32
#define PLATFORM_WINDOWS 1
#define ARCHITECTURE_86 1
#elif linux
#define PLATFORM_LINUX 1
#elif APPLE
#define PLATFORM_APPLE 1
#else
#error "Platform not supported!"
#endif

#ifdef PLATFORM_WINDOWS
#define INLINE __forceinline
#define NOINLINE _declspec(noinline)
#endif
#ifdef PLATFORM_LINUX
#define INLINE inline
#define NOINLINE
#endif
#ifdef PLATFORM_APPLE
#define INLINE inline
#define NOINLINE
#endif

#include <iostream> //For std::cout
#include <random> //For fill containers


class Test
{
public:
	static void RunTest() noexcept;
	static void BubbleSortTest() noexcept;
	static void SelectionSortTest() noexcept;
	static void SelectionSortDoubleTest() noexcept;
	static void InsertionSortTest() noexcept;
	static void ShellSortTest() noexcept;

	

private:
	
	
	template<class It> static void BubbleRandomTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void BubbleAlmostSortedFrontTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void BubbleAlmostSortedMiddleTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void BubbleAlmostSortedBackTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void BubbleReverseTest(It first, It last, size_t size, const std::string& Type) noexcept;

	template<class It> static void SelectionRandomTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void SelectionAlmostSortedFrontTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void SelectionAlmostSortedMiddleTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void SelectionAlmostSortedBackTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void SelectionReverseTest(It first, It last, size_t size, const std::string& Type) noexcept;

	template<class It> static void SelectionDoubleRandomTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void SelectionDoubleAlmostSortedFrontTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void SelectionDoubleAlmostSortedMiddleTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void SelectionDoubleAlmostSortedBackTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void SelectionDoubleReverseTest(It first, It last, size_t size, const std::string& Type) noexcept;

	template<class It> static void InsertionRandomTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void InsertionAlmostSortedFrontTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void InsertionAlmostSortedMiddleTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void InsertionAlmostSortedBackTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void InsertionReverseTest(It first, It last, size_t size, const std::string& Type) noexcept;
	 
	template<class It> static void ShellRandomTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void ShellAlmostSortedFrontTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void ShellAlmostSortedMiddleTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void ShellAlmostSortedBackTest(It first, It last, size_t size, const std::string& Type) noexcept;
	template<class It> static void ShellReverseTest(It first, It last, size_t size, const std::string& Type) noexcept;
};


