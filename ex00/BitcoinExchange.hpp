/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:51:51 by nuno              #+#    #+#             */
/*   Updated: 2023/07/23 18:50:46 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHNAGE_HPP
# define BITCOIN_EXCHNAGE_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

class	BitcoinExchange
{
private:
	std::string					_filename;
	std::vector<std::string>	_lines;

public:
	BitcoinExchange( std::string filename );
	~BitcoinExchange();

	void	read_input( std::string filename );
	bool	parse_input();
};

#endif
