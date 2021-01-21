namespace alg {

	// Numeric operations


	template< class It, class T = typename std::iterator_traits<It>::value_type >
	///Sums up a range of elements
	T sum(It first, It last) {
		T val = T{};
		for (auto it = first; it != last; ++it)
			val += *it;
		return val;
	}

	//Sorting operations
	///Sorting a range into ascending order using Bubble Sort algorithm
	template<class It>
	void BubbleSort(It first, It last) {

		unsigned long long counter = 0;
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
	void SelectionSort(It first, It last) {
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
	void SelectionDoubleSort(It first, It last) {
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

			if (*it_bigger == *first) it_bigger = first;

			const auto tempB = *(last - 1);
			*(last - 1) = *it_bigger;
			*it_bigger = tempB;
			
			++first;
			--last;
		}
	}
	
}