/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:50:55 by nuno              #+#    #+#             */
/*   Updated: 2024/06/10 09:49:03 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {
	std::cout << "Default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const std::string &dataBaseFile) : _dataBaseFile(dataBaseFile) {
	std::cout << "Parameter constructor called" << std::endl;
	loadDataBase();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other) : _dataBaseFile(other._dataBaseFile) , _exchangeRates(other._exchangeRates) {
	std::cout << "Copy constructor called" << std::endl;
	loadDataBase();
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other){
	std::cout << "Assignment operator called" << std::endl;
	if (this != &other) {
		this->_dataBaseFile = other._dataBaseFile;
		this->_exchangeRates = other._exchangeRates;
	}
	loadDataBase();
	return *this;
}

BitcoinExchange::~BitcoinExchange(void) {
	std::cout << "Destructor called" << std::endl;
}

/*getline e guarda o ficheiro data com os pre;os hist]oricos no container mapa
	_exchangeRates: Data (std::string) e hora (float) separados pela virgula*/
void BitcoinExchange::loadDataBase(void) {
	std::ifstream db(_dataBaseFile.c_str());
	if (!db) {
		std::cerr << "Error: could not open database file with BTC exchange rates." << std::endl;
		return;
	}

	std::string line;
	while (std::getline(db, line)) {
		std::istringstream ss(line);
		std::string date;
		float rate;
		if (std::getline(ss, date, ',') && ss >> rate) {
			_exchangeRates[date] = rate;
		}
	}
	db.close();
}

void BitcoinExchange::processInput(const std::string& inputFile) {
	std::ifstream input(inputFile.c_str());
	if (!input) {
		printError("could not open input file ", inputFile);
		return;
	}

	std::string line;
	while (std::getline(input, line)) {

		if (!isValidEdgeChar(line)) {
			printError("empty line or wrong character on line's extremities: ", line);
			continue;
		}
		size_t pipeIdx = line.find_first_of("|");
		if (pipeIdx == std::string::npos) {
			printError("wrong character on line's extremities: ", line);
			continue;
		}
		if ((line.at(pipeIdx - 1) != ' ') || line.at(pipeIdx + 1) != ' ') {
			printError("no space before or after pipe '|' : " , line);
			continue;
		}
		if (line.find("|", pipeIdx + 1) != std::string::npos) {
			std::cerr << "line has more than one separator pipe" << std::endl;
			continue;
		}
		std::string date, rate;
		date = line.substr(0, pipeIdx - 1);
		rate = line.substr(pipeIdx + 2, pipeIdx + 2 - line.length());
		std::cout << "pp: " << pipeIdx << " dt: [" << date << "] rt: [" << rate << "]" << std::endl;
	}
}

bool BitcoinExchange::isValidEdgeChar(const std::string& line) {
	char lastChar = line[line.size() - 1]	;
	if (line.empty() || line[0] != '2' || !isdigit(lastChar) || lastChar != 'f')
		return false;
	return true;

}

void BitcoinExchange::printError(const std::string& errorMessage, const std::string& line) {
	std::cerr << RED << "Error: " << RESET << errorMessage << YELLOW << line << RESET << std::endl;
}
