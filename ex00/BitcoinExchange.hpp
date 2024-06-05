/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:50:31 by nuno              #+#    #+#             */
/*   Updated: 2024/06/05 12:20:01 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BITCOINEXCHANGE_HPP_
# define _BITCOINEXCHANGE_HPP_

#include <iostream>
#include <string>
#include <map>

class BitcoinExchange {
public:
	BitcoinExchange(void);
	BitcoinExchange(const std::string &dbFile);
	BitcoinExchange(BitcoinExchange const & obj);
	BitcoinExchange & operator=(BitcoinExchange const & obj);

private:
	std::string dbFile;
	std::map<std::string, float> exchangeRates;
};

#endif