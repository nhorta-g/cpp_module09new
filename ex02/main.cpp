/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:43:22 by nuno              #+#    #+#             */
/*   Updated: 2024/06/12 23:32:49 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <cstdlib>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Error: No arguments provided." << std::endl;
		return 1;
	}

	std::vector<int> vec;
	std::list<int> lst;

	for (int i = 1; i < argc; ++i) {
		int num = std::atoi(argv[i]);
		if (num <= 0) {
			std::cerr << "Error: Invalid input. Only positive integers are allowed." << std::endl;
			return 1;
		}
		vec.push_back(num);
		lst.push_back(num);
	}

	PmergeMe pmerge;
	pmerge.display(vec, lst);
	pmerge.sortAndMeasureTime(vec, lst);

	return 0;
}