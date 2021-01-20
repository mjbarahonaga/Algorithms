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

		unsigned int counter = 0;
		while ((first + counter) != last) {
			for (auto it = first; (it + counter) != (last-1); ++it) {
				auto it_next = it;
				++it_next;
				if (*it > *(it_next)) {
					auto it_aux = *it;
					*it = *it_next;
					*it_next = it_aux;
				}
			}
			++counter;
		}
	}
	
}