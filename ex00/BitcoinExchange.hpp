/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:50:31 by nuno              #+#    #+#             */
/*   Updated: 2024/06/10 09:37:16 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BITCOINEXCHANGE_HPP_
# define _BITCOINEXCHANGE_HPP_

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <cctype>

#define RED "\033[1m\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[1;32m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

class BitcoinExchange {
public:
	BitcoinExchange(void);
	BitcoinExchange(const std::string &dbFile);
	BitcoinExchange(BitcoinExchange const & other);
	BitcoinExchange & operator=(BitcoinExchange const & other);
	~BitcoinExchange(void);

	void processInput(const std::string& inputFile);

private:
	std::string _dataBaseFile;
	std::map<std::string, float> _exchangeRates;

	void loadDataBase(void);
	bool isValidEdgeChar(const std::string& date);
	void printError(const std::string& errorMessage, const std::string& line);
};

#endif