#include "RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(const RPN& other) : _stack(other._stack) {
}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		_stack = other._stack;
	}
	return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/';
}

void RPN::performOperation(char op) {
	if (_stack.size() < 2) {
		throw std::runtime_error("Error");
	}

	int b = _stack.back();
	_stack.pop_back();
	int a = _stack.back();
	_stack.pop_back();
	int result;

	switch (op) {
		case '+': result = a + b; break;
		case '-': result = a - b; break;
		case '*': result = a * b; break;
		case '/':
			if (b == 0) {
				throw std::runtime_error("Error: Division by zero");
			}
			result = a / b;
			break;
		default:
			throw std::runtime_error("Error: Invalid operator");
	}

	_stack.push_back(result);
}

int RPN::evaluate(const std::string& expression) {
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token) {
		if (token.size() == 1 && isOperator(token[0])) {
			performOperation(token[0]);
		} else if (token.size() == 1 && std::isdigit(token[0])) {
			int num = token[0] - '0';
			_stack.push_back(num);
		} else
			throw std::runtime_error("Error: Invalid token");
	}
	if (_stack.size() != 1) {
		throw std::runtime_error("Error: not enough operands or operators ");
	}

	return _stack.back();
}