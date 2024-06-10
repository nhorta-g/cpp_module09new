#include "btc.hpp"

BitcoinExchange::BitcoinExchange(const std::string& dbFile) : _dbFile(dbFile) {
	loadDatabase();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _dbFile(other._dbFile), _exchangeRates(other._exchangeRates) {
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		_dbFile = other._dbFile;
		_exchangeRates = other._exchangeRates;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

//getline e guarda o ficheiro data com os pre;os hist]oricos no container mapa
//_exchangeRates: Data (std::string) e hora (float) separados pela virgula
void BitcoinExchange::loadDatabase() {
	std::ifstream db(_dbFile.c_str());
	if (!db) {
		std::cerr << "Error: could not open database file." << std::endl;
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

// trim from left
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
	s.erase(0, s.find_first_not_of(t));
	return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

void BitcoinExchange::processInput(const std::string& inputFile) {
	std::ifstream input(inputFile.c_str());
	if (!input) {
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
//getline e guarda o outro ficheiro input com as datas para ir buscar o preco e o valor a
//multiplicar. date separado por | do multiplicador
	std::string line;
	while (std::getline(input, line)) { //istream& getline(istream& is,string& str, char delim);
		line = ltrim(line);
		line = rtrim(line);
		std::istringstream ss(line);
		std::string date, valueStr;
		if (std::getline(ss, date, '|') && std::getline(ss, valueStr)) {
			date = date.substr(0, date.find_last_not_of(" \t\n\r\f\v") + 1);
			valueStr = valueStr.substr(valueStr.find_first_not_of(" \t\n\r\f\v"));

			if (!isValidDate(date)) {
				printError("bad input => " + date);
				continue;
			}

			if (!isValidValue(valueStr)) {
				printError("not a positive number.");
				continue;
			}

			float value = std::atof(valueStr.c_str());
			if (value > 1000) {
				printError("too large a number.");
				continue;
			}

			std::string closestDate = findClosestDate(date);
			if (_exchangeRates.find(closestDate) != _exchangeRates.end()) {
				float rate = _exchangeRates[closestDate];
				std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
			} else {
				printError("no exchange rate available for date " + date);
			}
		}
	}
	input.close();
}

bool BitcoinExchange::isValidDate(const std::string& date) {
	// Simple validation for format YYYY-MM-DD
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

bool BitcoinExchange::isValidValue(const std::string& value) {
	if (value.empty())
		return false;

	char* end;
	double val = std::strtod(value.c_str(), &end);
	return (*end == '\0' && val >= 0);
}

std::string BitcoinExchange::findClosestDate(const std::string& date) {
	std::map<std::string, float>::iterator it = _exchangeRates.lower_bound(date);
	if (it == _exchangeRates.end() || it->first != date) {
		if (it != _exchangeRates.begin())
			--it;
	}
	return it->first;
}

void BitcoinExchange::printError(const std::string& errorMessage) {
	std::cerr << "Error: " << errorMessage << std::endl;
}