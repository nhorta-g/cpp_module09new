/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:11:22 by nhorta-g          #+#    #+#             */
/*   Updated: 2024/06/13 15:20:57 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
std::vector<int> PmergeMe::jacobsthalSequence(int n) {
	std::vector<int> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	for (int i = 2; i < n; ++i) {
		jacobsthal.push_back(jacobsthal[i - 1] + 2 * jacobsthal[i - 2]);
	}
	return jacobsthal;
}*/

PmergeMe::~PmergeMe() {}

const int PmergeMe::_jacobsthal[35] = {
	-1, 0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923,
	21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405,
	11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883,
	1431655765
};

void PmergeMe::display(const std::vector<int>& vec, const std::list<int>& lst) {
	std::cout << "Before: ";
	for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	std::vector<int> sortedVec = vec;
	std::list<int> sortedLst = lst;

	sortFordJohnson(sortedVec);
	sortFordJohnson(sortedLst);

	std::cout << "After: ";
	for (std::vector<int>::const_iterator it = sortedVec.begin(); it != sortedVec.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::sortAndMeasureTime(const std::vector<int>& vec, const std::list<int>& lst) {
	std::vector<int> sortedVec = vec;
	std::list<int> sortedLst = lst;

	clock_t start = clock();
	sortFordJohnson(sortedVec);
	clock_t end = clock();
	double timeVec = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	start = clock();
	sortFordJohnson(sortedLst);
	end = clock();
	double timeLst = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << lst.size() << " elements with std::list: " << timeLst << " us" << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////

std::list<int>::iterator	PmergeMe::elementAt(std::list<int>& base, int index) {
	std::list<int>::iterator	it = base.begin();
	int	find;

	find = 0;
	while (it != base.end() && find != index) {
		it++;
		find++;
	}
	return (it);
}

std::list<int>::iterator	PmergeMe::findIndexOf(std::list<int>& base, int find) {
	std::list<int>::iterator	it = base.begin();

	while (it != base.end() && find > *it) {
		it++;
	}
	return (it);
}

void	PmergeMe::jacobsthalInsert(std::list<int>& base, std::list<int>& merge) {

	int	index, pos;
	std::list<int>::iterator	where, what;

	index = 0;
	do {
		index++;
		pos = (_jacobsthal[index] < (int)merge.size() ? _jacobsthal[index] : merge.size() - 1);
		while (pos > _jacobsthal[index - 1]) {
			what = elementAt(merge, pos);
			where = findIndexOf(base, *what);
			base.insert(where, *what);
			pos--;
		}
	} while (_jacobsthal[index] < (int)merge.size());
}

void	PmergeMe::binaryJacobsthalInsert(std::vector<int>& base, std::vector<int>& merge) {

	std::vector<int>::iterator	where;
	int	index, current;

	index = 0;
	do {
		index++;
		current = (_jacobsthal[index] < (int)merge.size() ? _jacobsthal[index] : merge.size() - 1);
		while (current > _jacobsthal[index - 1]) {
			where = std::lower_bound(base.begin(), base.end(), merge[current]);
			base.insert(where, merge[current]);
			current--;
		}
	} while (_jacobsthal[index] < (int)merge.size());
}

//SORT LIST
void	PmergeMe::sortFordJohnson(std::list<int>& numbers) {

	std::list<int>::iterator	first, second, move;
	std::list<int>				smaller;

	if (numbers.size() < 2)
		return ;
	first = second = numbers.begin();
	second++;
	while(first != numbers.end() && second != numbers.end()) {
		move = (*first < *second ? first : second);
		std::advance(first, 2);
		std::advance(second, 2);
		smaller.splice(smaller.end(), numbers, move);
	}
	sortFordJohnson(numbers);
	jacobsthalInsert(numbers, smaller);
}

//SORT VECTOR
void	PmergeMe::sortFordJohnson(std::vector<int>& numbers) {
	std::vector<int>	copy, smaller;
	int	size = numbers.size() - 1;
	int	i = 0;

	if (numbers.size() < 2)
		return ;
	copy = numbers;
	numbers.clear();
	while (i < size)
	{
		if (copy[i] > copy[i + 1]) {
			numbers.push_back(copy[i]);
			smaller.push_back(copy[i + 1]);
		}
		else {
			numbers.push_back(copy[i + 1]);
			smaller.push_back(copy[i]);
		}
		i += 2;
	}
	if (copy.size() % 2)
		numbers.push_back(copy[i]);
	sortFordJohnson(numbers);
	binaryJacobsthalInsert(numbers, smaller);
}