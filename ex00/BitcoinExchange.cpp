/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:50:55 by nuno              #+#    #+#             */
/*   Updated: 2024/06/12 22:50:13 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {
	//std::cout << "Default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const std::string &dataBaseFile) : _dataBaseFile(dataBaseFile) {
	//std::cout << "Parameter constructor called" << std::endl;
	loadDataBase();
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other) : _dataBaseFile(other._dataBaseFile) , _exchangeRates(other._exchangeRates) {
	//std::cout << "Copy constructor called" << std::endl;
	loadDataBase();
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other){
	//std::cout << "Assignment operator called" << std::endl;
	if (this != &other) {
		this->_dataBaseFile = other._dataBaseFile;
		this->_exchangeRates = other._exchangeRates;
	}
	loadDataBase();
	return *this;
}

BitcoinExchange::~BitcoinExchange(void) {
	//std::cout << "Destructor called" << std::endl;
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
/*std::istringstream is an input string stream that allows us to read
from a string as if it were a stream (like reading from std::cin)*/
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
		printError("could not open input file : ", inputFile);
		return;
	}
	int i = 0;
	std::string line;
	while (std::getline(input, line)) {
		i++;
		if (header(line, i))
			continue;
		if (!isValidLine(line))
			continue;

		size_t pipeIdx = line.find_first_of("|");
		if (!isValidLinePipe(line, pipeIdx))
			continue;

		std::string date, rateStr;
		date = line.substr(0, pipeIdx - 1);
		rateStr = line.substr(pipeIdx + 2, pipeIdx + 2 - line.length());

		if (!isValidDate(date)) {
			printError("wrong date value : ", date);
			continue;
		}
		if (!isValidRateStr(rateStr)) {
			printError("wrong rate value : ", rateStr);
			continue;
		}
		float value = std::atof(rateStr.c_str());
		if (value > 1000) {
			printError("rate cant be greater than 1000 : ", rateStr);
			continue;
		}
		std::string closestDate = findClosestDate(date);
		if (_exchangeRates.find(closestDate) != _exchangeRates.end()) {
			float rate = _exchangeRates[closestDate];
			std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
		} else {
			printError("no exchange rate available for date : ", date);
		}

		//std::cout << "[" << date << "][" << rateStr << "]" << std::endl;
	}
	input.close();
}

std::string BitcoinExchange::findClosestDate(const std::string& date) {
/*aponta um iterator para o elemento de exchange rate que corresponda ao valor do date
mas se este nao existir, aponta para o que corresponda ao date imediatamente superior */
	std::map<std::string, float>::iterator it = _exchangeRates.lower_bound(date); /*^^^*/
	if (it == _exchangeRates.end() || it->first != date) {
		if (it != _exchangeRates.begin())
			--it;
	}
	return it->first;
}

//PARSING ERROR MANAGMENT FUNCTIONS

bool BitcoinExchange::header(const std::string& line, int i) {
	if(!line.compare("date | value")) {
		if (i > 1)
			printError("header only allowed at first line : ", line);
		return true;
	}
	return false;
}

bool BitcoinExchange::isValidLine(const std::string& line) {
	if (line.empty()) {
		printError("empty line", line);
		return false;
	}
	if (std::isspace(line[0]) || std::isspace(line[line.size() - 1])) {
		printError("whitepaces at one end of the line : ", line);
		return false;
	}
	return true;
}

bool BitcoinExchange::isValidLinePipe(const std::string& line, const size_t &pipeIdx) {
	if (pipeIdx == std::string::npos) {
		printError("line has no pipe separator : ", line);
		return false;
	}
	if (line.find("|", pipeIdx + 1) != std::string::npos) {
		printError("line has more than one separator pipe :", line);
		return false;
	}
	if ((line.at(pipeIdx - 1) != ' ') || line.at(pipeIdx + 1) != ' ') {
		printError("no space before or after pipe '|' : " , line);
		return false;
	}
	return true;
}

bool BitcoinExchange::isValidDate(std::string const &date) {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	for (size_t i = 0; i < date.size(); ++i) {
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return false;
	}
	return true;
}

bool BitcoinExchange::isValidRateStr(std::string const &rateStr) {
	if (rateStr.empty())
		return false;

	char* end;
	double val = std::strtod(rateStr.c_str(), &end);
	return (*end == '\0' && val >= 0);
}

void BitcoinExchange::printError(const std::string& errMsg, const std::string& line) {
	std::cerr << RED << "Error: " << RESET << errMsg << YELLOW << line << RESET << std::endl;
}
