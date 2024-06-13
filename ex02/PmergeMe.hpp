/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:43:44 by nuno              #+#    #+#             */
/*   Updated: 2024/06/13 15:19:22 by nhorta-g         ###   ########.fr       */
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

	void display(const std::vector<int>& vec, const std::list<int>& lst);
	void sortAndMeasureTime(const std::vector<int>& vec, const std::list<int>& lst);

private:
	static const int	_jacobsthal[35];
	static void	jacobsthalInsert(std::list<int>&, std::list<int>&);
	static void	binaryJacobsthalInsert(std::vector<int>&, std::vector<int>&);
	static std::list<int>::iterator	elementAt(std::list<int>& base, int index);
	static std::list<int>::iterator	findIndexOf(std::list<int>& base, int index);

	static void	sortFordJohnson(std::list<int>& list);
	static void	sortFordJohnson(std::vector<int>& array);
};

#endif