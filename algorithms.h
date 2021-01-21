typedef unsigned long long ULL;

namespace alg {

	// Numeric operations


	template< class It, class T = typename std::iterator_traits<It>::value_type >
	///Sums up a range of elements
	_NODISCARD __forceinline T sum(It first, It last) noexcept {
		T val = T{};
		for (auto it = first; it != last; ++it)
			val += *it;
		return val;
	}

	//Sorting operations
	///Sorting a range into ascending order using Bubble Sort algorithm
	template<class It>
	__forceinline void BubbleSort(It first, It last) noexcept {

		ULL counter = 0;
		while ((first + counter) != last) {
			for (auto it = first; (it + counter) != (last-1); ++it) {
				auto it_next = it;
				++it_next;
				if (*it > *(it_next)) {
					const auto it_aux = *it;
					*it = *it_next;
					*it_next = it_aux;
				}
			}
			++counter;
		}
	}

	///Sorting a range into ascending order using Selection Sort algorithm
	template<class It>
	__forceinline void SelectionSort(It first, It last) noexcept {
		while (first != last) {
			auto it_smaller = first;
			for (auto it = first; it != last; ++it) {
				if (*it_smaller > *it) {
					it_smaller = it;
				}
			}
			const auto temp = *first;
			*first = *it_smaller;
			*it_smaller = temp;
			
			++first;
		}
	}

	///Sorting a range into ascending order using Selection Sort algorithm
	///but selecting at the same time the bigger number also
	template<class It>
	__forceinline void SelectionDoubleSort(It first, It last) noexcept {
		while (first != last && first < last) {
			auto it_smaller = first;
			auto it_bigger = first;
			for (auto it = first; it != last; ++it) {
				if (*it_smaller > *it) it_smaller = it;
				if (*it_bigger < *it) it_bigger = it;
			}

			const auto tempS = *first;
			*first = *it_smaller;
			*it_smaller = tempS;

			//If the it_bigger is pointing to the first iteration, it's changed to the 
			//new location where the biggest number is
			if (it_bigger == first) it_bigger = it_smaller;

			const auto tempB = *(last - 1);
			*(last - 1) = *it_bigger;
			*it_bigger = tempB;
			
			++first;
			--last;
		}
	}
	
	///Sorting a range into ascending order using Insertion Sort algorithm
	template<class It>
	__forceinline void InsertionSort(It first, It last) noexcept {
		for (auto it = first; it != (last - 1); ++it) {
			auto it_next = it + 1;
			if (*it > *it_next) {
				for (auto it_ins = it_next; it_ins != first; --it_ins) {
					auto it_prev = it_ins - 1;
					if (*it_prev > *it_ins) {
						const auto temp = *it_prev;
						*it_prev = *it_ins;
						*it_ins = temp;
					}
					else break;
				}
			}
		}
	}

	///Sorting a range into ascending order using Shell Sort algorithm
	template<class It>
	__forceinline void ShellSort(It first, It last) noexcept {
		auto size = std::distance(first, last);
		for (auto interval = size >> 1; interval > 0; interval >>= 1) {
			for (auto i = first + interval; i != last; ++i) {
				auto temp = *i;
				auto j = i;
				for (; j >= (first + interval) && *(j - interval) > temp; j-=interval)
					*j = *(j - interval);
				*j = temp;
			}
		}
	}

}