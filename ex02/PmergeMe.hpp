/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:43:44 by nuno              #+#    #+#             */
/*   Updated: 2024/06/12 22:07:18 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>
#include <ctime>
#include <iterator>
#include <algorithm>

class PmergeMe {
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();
	
	void sortVector(std::vector<int>& vec);
	void sortList(std::list<int>& lst);
	void display(const std::vector<int>& vec, const std::list<int>& lst);
	void measureTime(const std::vector<int>& vec, const std::list<int>& lst);

private:
	std::vector<int> jacobsthalSequence(int n);

	template <typename Iterator>
	void mergeInsertSort(Iterator begin, Iterator end);
};

#endif