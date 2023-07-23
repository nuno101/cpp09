/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:55:36 by nuno              #+#    #+#             */
/*   Updated: 2023/07/23 18:49:47 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( std::string filename ) : _filename(filename)
{
	std::cout << "BitcoinExchange constructor" << std::endl;
	std::cout << "_filename: " << _filename << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
}

/*
 * read the user filename
 */
void    BitcoinExchange::read_input(std::string filename)
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
		//_lines.push_back(trim(line));
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

bool	BitcoinExchange::parse_input()
{
	std::string	word;

	std::vector<std::string>::iterator line = _lines.begin();
	while(line != _lines.end())
	{
		std::cout << "Line: " << trim(*line) << std::endl;
		std::vector<std::string> v = split (*line, '|');
		for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
		{
			word = *it;
			std::cout << "  Word: " << trim(word) << std::endl;
		}
		line++;
	}
	return (true);
}
