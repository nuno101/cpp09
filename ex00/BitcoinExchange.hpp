/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:51:51 by nuno              #+#    #+#             */
/*   Updated: 2023/07/25 12:18:15 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHNAGE_HPP
# define BITCOIN_EXCHNAGE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

typedef	struct s_log
{
	std::string	_date;
	//unsigned int	_btc_date; // days since 2000
	float		_value;
}	t_log;

class	BitcoinExchange
{
private:
	std::string					_data_file;
	std::vector<std::string>	_data_lines;
	std::string					_input_file;
	std::vector<std::string>	_input_lines;
	std::map<int, t_log>		_price;
	std::map<int, t_log>		_input;

public:
	BitcoinExchange( std::string btc_prices, std::string user_input );
	~BitcoinExchange();

	void	read_input(std::string filename, std::vector<std::string> &_lines);
	bool	parse_data();
	bool	parse_input();
	void	inspect();
};

#endif
