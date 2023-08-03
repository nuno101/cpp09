/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:55:36 by nuno              #+#    #+#             */
/*   Updated: 2023/08/03 14:04:49 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( std::string btc_prices )
{
	std::cout << "BitcoinExchange constructor" << std::endl;
	read_input(btc_prices);
	if (VERBOSE >= DEBUG)
		inspect();
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange &src )
{
    if ( VERBOSE >= DEBUG )
        std::cout << "Copy called" << std::endl;
    *this = src;
}

BitcoinExchange & BitcoinExchange::operator=( const BitcoinExchange &src )
{
    if ( VERBOSE >= DEBUG )
        std::cout << "Assign called" << std::endl;
    this->_prices = src._prices;
    return *this ;
}

/*
 * read a file line by line and call parse_data on it 
 */
void    BitcoinExchange::read_input(std::string filename)
{
	std::string file;
	std::string line;

	file.assign(filename);
	if (VERBOSE >= INFO)
	   std::cout << "Reading: " << file << std::endl;

	std::ifstream input_file(filename);
	if (!input_file.is_open())
	{
		std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (std::getline(input_file, line))
	{
		if (filename.compare("data.csv") == 0)
			parse_btc_data(line);
		else
			process_input(line);
	}
	input_file.close();
}

/*
 * trim white space around str
 */
static	std::string trim(const std::string& str)
{
	if (str.empty())
		return ("");
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	if (first == std::string::npos || last == std::string::npos)
	{
		return ("");
	}
	return (str.substr(first, last - first + 1));
}

/*
 * parse a string and return a float
 * max defines the maximum float to be returned
 * return -1 in case of error
 */
static	float parse_number(std::string word, double max)
{
	double	val;

	val = ::atof(word.c_str());
	if (val < 0.0)
	{
		if (VERBOSE >= WARN)
			std::cout << "WARN: not a positive number." << std::endl;
		val = -1.0;
	}
	else if (val > max)
	{
		if (VERBOSE >= WARN)
			std::cout << "WARN: too large a number." << std::endl;
		val = -2.0;
	}
	return ((float) val);
}

/*
 * validate date and return an indexable date-like integer
 */
static	int parse_date(std::string word)
{
	std::string	first, second, third;
	int			pos;
	int			year, month, day;
	bool		input_error = false;

	pos = word.find("-");
	first = word.substr(0, pos);
	word = word.substr(pos + 1, word.size());
	pos = word.find("-");
	second = word.substr(0, pos);
	third = word.substr(pos + 1, word.size());
	if (VERBOSE >= DEBUG)
	{
		std::cout << "YYYY: " << first << std::endl;
		std::cout << "MM: " << second << std::endl;
		std::cout << "DD: " << second << std::endl;
	}
	year = std::stoi(first);
	if (year < 2009 || year > 2023)
		input_error = true;

	month = std::stoi(second);
	if (month < 1 || month > 12)
		input_error = true;

	day = std::stoi(third);
	if (day < 1 || day > 31)
		input_error = true;

	if (input_error == true)
	{
		if (VERBOSE >= DEBUG)
			std::cout << "DEBUG: bad input => " << word << std::endl;
		return (-1);
	}
	//std::cout << "  Parsed date: " << year << "." << month << "." << day << std::endl;
	return (year *10000 + month * 100 + day);
}

/*
 * parse a data.csv line containing the Bitcoin day closing prices
 * format is: "date, value"
 * store the prices in _prices
 */
void	BitcoinExchange::parse_btc_data(std::string line)
{
	std::string	first, second;
	int			pos;
	int			date_index;
	float		price;
	t_log		date_and_price;
	std::pair<std::map<int, t_log>::iterator,bool> ret;

	if (VERBOSE >= DEBUG)
		std::cout << "Line: " << trim(line) << std::endl;
	pos = line.find(",");
	first = trim(line.substr(0, pos));
	if (first.compare("date") == 0)
		return ;
	second = trim(line.substr(pos + 1, line.size()));
	if (VERBOSE >= DEBUG)
	{
		std::cout << "Date: " << first << std::endl;
		std::cout << "Price: " << second << std::endl;
	}
	// parse date
	date_index = parse_date(first);
	if (VERBOSE >= DEBUG)
		std::cout << "  Parsed date: " << date_index << std::endl;
	if (date_index != -1)
		date_and_price._date = first;
	else
		return ;
	// parse value
	price = parse_number(second, 1000000.0);
	date_and_price._value = price;
	if (price >= 0.0)
	{
		if (VERBOSE >= DEBUG)
			std::cout << "  Parsed value: " << parse_number(second, 1000000.0) << std::endl;
		ret = _prices.insert( std::pair<int, t_log>(date_index, date_and_price) );
		if (ret.second == false) {
			std::cout << "element " << date_index << " exists!\n";
			//std::cout << " with a value of " << ret.first->second << '\n';
		}
	}
	else
		std::cout << "  Error in parse_data(): " << price << std::endl;
}

/*
 * inspect std::map<int, t_log>
 */
void	BitcoinExchange::inspect()
{
	std::cout << "Inspect _prices map:" << std::endl;
	for (std::map<int, t_log>::iterator it = _prices.begin(); it != _prices.end(); it++)
	{
		std::cout << it->first << " => { label: "<< it->second._date;
		std::cout << ", price: " << it->second._value << " }" << std::endl;
	}
}

float	BitcoinExchange::get_price_at(int date_index)
{
	float	result;
	int		index;

	try
	{
		result = _prices.at(date_index)._value;
	}
	catch (const std::out_of_range& oor)
	{
		for (std::map<int, t_log>::iterator it = _prices.begin(); it != _prices.end(); it++)
		{
			index = it->first;
			if (index > date_index)
			{
				result = _prices.at(index)._value;
				break;
			}
		}
	}
	return (result);
}

/*
 * parse list of dates and values
 * dates like: YYYY-MM-DD
 * value: float or a positive integer between 0 and 1000.
 */
void	BitcoinExchange::process_input(std::string line)
{
	std::string	first, second;
	int			pos;
	int			date_index;
	std::string	message;
	float		result;

	if (VERBOSE >= DEBUG)
		std::cout << "Line: " << trim(line) << std::endl;

	pos = line.find("|");
	first = trim(line.substr(0, pos));
	if (first.compare("date") == 0)
		return ;
	second = trim(line.substr(pos + 1, line.size()));
	if (VERBOSE >= DEBUG)
	{
		std::cout << "Date: " << first << std::endl;
		std::cout << "Value: " << second << std::endl;
	}
	// parse date
	date_index = parse_date(first);
	if (date_index == -1)
		message = "Error: bad input => " + first;
	else
		message = first;
	// parse value
	result = parse_number(second, 1000.0);
	if (result >= 0)
		message += " => " + second + " = " + std::to_string(result * get_price_at(date_index)); 
	else if (result == -1.0)
		message = "Error: not a positive number.";
	else if (result == -2.0)
		message = "Error: too large of a number.";
	else
		message = "Error: unsupported result!";

	std::cout << message << std::endl;
}
