/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:55:36 by nuno              #+#    #+#             */
/*   Updated: 2023/07/24 23:12:59 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( std::string btc_prices, std::string user_input ) : _data_file(btc_prices), _input_file(user_input)
{
	std::cout << "BitcoinExchange constructor" << std::endl;
	std::cout << "_data_file: " << _data_file << std::endl;
	std::cout << "_input_file: " << _input_file << std::endl;
	read_input(_data_file, _data_lines);
	read_input(_input_file, _input_lines);
}

BitcoinExchange::~BitcoinExchange()
{
}

/*
 * read a filename into a vector of lines for parsing
 */
void    BitcoinExchange::read_input(std::string filename, std::vector<std::string> &_lines)
{
	std::string file;
	std::string line;

	file.assign(filename);
	if (VERBOSE > 0)
	   std::cout << "Reading: " << file << std::endl;

	std::ifstream input_file(filename);
	if (!input_file.is_open())
	{
		std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
		exit(EXIT_FAILURE);
	}
	while (std::getline(input_file, line))
	{
		_lines.push_back(line);
	   //std::cout << "Read: " << line << std::endl;
	}
	input_file.close();
}

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
 * split string into a string's vector
 * Note: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 */
const std::vector<std::string> split (const std::string &s, const char delim)
{
    std::vector<std::string> result(0);
    std::stringstream ss (s);
    std::string item;

    while (std::getline (ss, item, delim))
    {
        if (item != "")
            result.push_back(item);
    }
    return result;
}

static	float parse_number(std::string word)
{
	double	val;

	val = ::atof(word.c_str());
	if (val < 0.0)
	{
		std::cout << "  Error: not a positive number." << std::endl;
		val = -1.0;
	}
	else if (val > 1000.0)
	{
		std::cout << "  Error: too large a number." << std::endl;
		val = -1.0;
	}
	return (val);
}

/*
 * parse list of dates and values
 * dates like: YYYY-MM-DD
 * value: float or a positive integer between 0 and 1000.
 */
bool	BitcoinExchange::parse_input()
{
	std::string	word;

	std::vector<std::string>::iterator line = _input_lines.begin();
	while(line != _input_lines.end())
	{
		std::cout << "Line: " << trim(*line) << std::endl;
		std::vector<std::string> v = split (*line, '|');
		if (trim(*(v.begin())).compare("date") == 0)
		{
			line++;
			continue;
		}
		for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
		{
			word = trim(*it);
			std::cout << "  Word: " << word << std::endl;
			// parse date
			if (it == v.begin())
			{
				std::vector<std::string> x = split (word, '-');
				std::cout << "  Date: ";
				for (std::vector<std::string>::iterator itd = x.begin(); itd != x.end(); itd++)
				{
					std::cout << trim(*itd) << "+";
				}
				std::cout << std::endl;
			}
			// parse value
			else
			{
				//std::cout << "  Value: " << trim(word) << std::endl;
				if (parse_number(trim(word)) >= 0)
					std::cout << "  Parsed value: " << parse_number(trim(word)) << std::endl;
			}
		}
		line++;
	}
	return (true);
}
