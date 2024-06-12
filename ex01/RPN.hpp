/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:44:02 by nuno              #+#    #+#             */
/*   Updated: 2024/06/12 13:44:03 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <deque>
#include <stdexcept>
#include <map>

class RPN {
public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	int evaluate(const std::string& expression);

private:
	std::deque<int> _stack;

	bool isOperator(char c);
	void performOperation(char op);
};

#endif