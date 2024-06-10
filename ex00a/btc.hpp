#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <map>

class BitcoinExchange {
public:
	BitcoinExchange(const std::string& dbFile);
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void processInput(const std::string& inputFile);

private:
	std::string _dbFile;
	std::map<std::string, float> _exchangeRates;

	void loadDatabase();
	bool isValidDate(const std::string& date);
	bool isValidValue(const std::string& value);
	std::string findClosestDate(const std::string& date);
	void printError(const std::string& errorMessage);
};

#endif // BITCOINEXCHANGE_HPP