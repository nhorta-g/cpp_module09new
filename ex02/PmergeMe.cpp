#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) {
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		*this = other;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::sortVector(std::vector<int>& vec) {
	mergeInsertSort(vec.begin(), vec.end());
}

void PmergeMe::sortList(std::list<int>& lst) {
	mergeInsertSort(lst.begin(), lst.end());
}

void PmergeMe::display(const std::vector<int>& vec, const std::list<int>& lst) {
	std::cout << "Before: ";
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::vector<int> sortedVec = vec;
	std::list<int> sortedLst = lst;

	sortVector(sortedVec);
	sortList(sortedLst);

	std::cout << "After: ";
	for (std::vector<int>::const_iterator it = sortedVec.begin(); it != sortedVec.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::measureTime(const std::vector<int>& vec, const std::list<int>& lst) {
	std::vector<int> sortedVec = vec;
	std::list<int> sortedLst = lst;

	clock_t start = clock();
	sortVector(sortedVec);
	clock_t end = clock();
	double timeVec = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	start = clock();
	sortList(sortedLst);
	end = clock();
	double timeLst = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << lst.size() << " elements with std::list: " << timeLst << " us" << std::endl;
}

std::vector<int> PmergeMe::jacobsthalSequence(int n) {
	std::vector<int> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	for (int i = 2; i < n; ++i) {
		jacobsthal.push_back(jacobsthal[i - 1] + 2 * jacobsthal[i - 2]);
	}
	return jacobsthal;
}

template <typename Iterator>
void PmergeMe::mergeInsertSort(Iterator begin, Iterator end) {
	if (std::distance(begin, end) <= 1) return;

	Iterator middle = begin;
	std::advance(middle, std::distance(begin, end) / 2);

	mergeInsertSort(begin, middle);
	mergeInsertSort(middle, end);

	std::inplace_merge(begin, middle, end);
}