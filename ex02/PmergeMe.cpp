

#include "PmergeMe.hpp"

RPN::RPN(void) {}

RPN::RPN(const RPN& other) : _stack(other._stack) {
}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		_stack = other._stack;
	}
	return *this;
}

RPN::~RPN() {}

#include <iterator>
#include <list>
#include <vector>
#include <algorithm>
#include <stdint.h>

// Helper function to create a group iterator
template<typename Iterator>
struct GroupIterator {
	Iterator it;
	std::size_t group_size;
	GroupIterator(Iterator it, std::size_t group_size) : it(it), group_size(group_size) {}
	GroupIterator& operator++() {
		std::advance(it, group_size);
		return *this;
	}
	GroupIterator operator++(int) {
		GroupIterator tmp(*this);
		operator++();
		return tmp;
	}
	typename std::iterator_traits<Iterator>::reference operator*() {
		return *it;
	}
	bool operator!=(const GroupIterator& other) const {
		return it != other.it;
	}
};

template<typename Iterator>
GroupIterator<Iterator> make_group_iterator(Iterator it, std::size_t group_size) {
	return GroupIterator<Iterator>(it, group_size);
}

// The main sort function
template<typename RandomAccessIterator, typename Compare>
void merge_insertion_sort_impl(RandomAccessIterator first, RandomAccessIterator last, Compare compare) {
	// Cache all the differences between a Jacobsthal number and its predecessor that fit in 64 bits
	static const uint64_t jacobsthal_diff[] = {
		2u, 2u, 6u, 10u, 22u, 42u, 86u, 170u, 342u, 682u, 1366u,
		2730u, 5462u, 10922u, 21846u, 43690u, 87382u, 174762u, 349526u, 699050u,
		1398102u, 2796202u, 5592406u, 11184810u, 22369622u, 44739242u, 89478486u,
		178956970u, 357913942u, 715827882u, 1431655766u, 2863311530u, 5726623062u,
		11453246122u, 22906492246u, 45812984490u, 91625968982u, 183251937962u,
		366503875926u, 733007751850u, 1466015503702u, 2932031007402u, 5864062014806u,
		11728124029610u, 23456248059222u, 46912496118442u, 93824992236886u, 187649984473770u,
		375299968947542u, 750599937895082u, 1501199875790165u, 3002399751580331u,
		6004799503160661u, 12009599006321322u, 24019198012642644u, 48038396025285288u,
		96076792050570576u, 192153584101141152u, 384307168202282304u, 768614336404564608u,
		1537228672809129216u, 3074457345618258432u, 6148914691236516864u
	};

	typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_type;
	typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;

	difference_type size = std::distance(first, last);
	if (size < 2) return;

	bool has_stray = (size % 2 != 0);

	// Group elements by pairs
	RandomAccessIterator end = has_stray ? std::prev(last) : last;
	for (RandomAccessIterator it = first; it != end; it += 2) {
		if (compare(it[1], it[0])) {
			std::iter_swap(it, it + 1);
		}
	}

	// Recursively sort the pairs by max
	merge_insertion_sort_impl(make_group_iterator(first, 2), make_group_iterator(end, 2), compare);

	// Separate main chain and pend elements
	std::list<RandomAccessIterator> chain;
	chain.push_back(first);
	chain.push_back(std::next(first));

	std::vector<typename std::list<RandomAccessIterator>::iterator> pend;
	pend.reserve((size + 1) / 2 - 1);

	for (RandomAccessIterator it = first + 2; it != end; it += 2) {
		typename std::list<RandomAccessIterator>::iterator tmp = chain.insert(chain.end(), std::next(it));
		pend.push_back(tmp);
	}

	if (has_stray) {
		pend.push_back(chain.end());
	}

	// Binary insertion into the main chain
	RandomAccessIterator current_it = first + 2;
	typename std::vector<typename std::list<RandomAccessIterator>::iterator>::iterator current_pend = pend.begin();

	for (int k = 0;; ++k) {
		uint64_t dist = jacobsthal_diff[k];
		if (dist > static_cast<uint64_t>(std::distance(current_pend, pend.end()))) break;

		RandomAccessIterator it = std::next(current_it, dist * 2);
		typename std::vector<typename std::list<RandomAccessIterator>::iterator>::iterator pe = std::next(current_pend, dist);

		do {
			--pe;
			it -= 2;

			typename std::list<RandomAccessIterator>::iterator insertion_point = std::upper_bound(
				chain.begin(), *pe, *it,
				compare
			);
			chain.insert(insertion_point, it);
		} while (pe != current_pend);

		std::advance(current_it, dist * 2);
		std::advance(current_pend, dist);
	}

	// If there are pend elements left, insert them into the main chain
	while (current_pend != pend.end()) {
		typename std::list<RandomAccessIterator>::iterator insertion_point = std::upper_bound(
			chain.begin(), *current_pend, *current_it,
			compare
		);
		chain.insert(insertion_point, current_it);
		current_it += 2;
		++current_pend;
	}

	// Move values in order to a cache then back to origin
	std::vector<value_type> cache;
	cache.reserve(size);

	for (typename std::list<RandomAccessIterator>::iterator it = chain.begin(); it != chain.end(); ++it) {
		RandomAccessIterator begin = *it;
		RandomAccessIterator end = begin + 2;
		std::copy(begin, end, std::back_inserter(cache));
	}
	std::copy(cache.begin(), cache.end(), first);
}























