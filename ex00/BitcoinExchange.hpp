/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:51:51 by nuno              #+#    #+#             */
/*   Updated: 2023/07/26 23:14:04 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHNAGE_HPP
# define BITCOIN_EXCHNAGE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

#define ERROR 1
#define WARN 2
#define INFO 3
#define DEBUG 4

typedef	struct s_log
{
	std::string	_date;
	float		_value;
}	t_log;

class	BitcoinExchange
{
private:
	std::map<int, t_log>		_prices;

public:
	BitcoinExchange( std::string btc_prices);
	~BitcoinExchange();

	void	read_input(std::string filename);
	bool	parse_data(std::string line);
	float	get_price_at(int date_index);
	bool	process_input(std::string filename);
	void	inspect();
};

#endif
