/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:51:51 by nuno              #+#    #+#             */
/*   Updated: 2023/07/24 22:33:28 by nuno             ###   ########.fr       */
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
	int				_value;
}	t_log;

class	BitcoinExchange
{
private:
	std::string					_filename;
	std::vector<std::string>	_lines;
	std::map<int, t_log>		_price;
	std::map<int, t_log>		_input;

public:
	BitcoinExchange( std::string filename );
	~BitcoinExchange();

	void	read_input( std::string filename );
	bool	parse_input();
};

#endif
