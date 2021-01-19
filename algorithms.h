namespace alg {


	// Numeric operations
	template< class It, class T = typename std::iterator_traits<It>::value_type >
	T sum(It first, It last) {
		T val = T{};
		for (auto it = first; it != last; ++it)
			val += *it;
		return val;
	}

}