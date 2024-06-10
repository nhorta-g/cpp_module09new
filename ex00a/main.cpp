/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:43:22 by nuno              #+#    #+#             */
/*   Updated: 2024/06/06 13:47:47 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btc.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Can't open file. Usage: ""./btc input.txt"" " << std::endl;
		return 1;
	}
	BitcoinExchange btcExchange("data.csv");
	btcExchange.processInput(av[1]);

	return 0;
}