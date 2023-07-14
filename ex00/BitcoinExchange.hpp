/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:51:51 by nuno              #+#    #+#             */
/*   Updated: 2023/07/14 23:03:04 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHNAGE_HPP
# define BITCOIN_EXCHNAGE_HPP

#include <iostream>

class	BitcoinExchange
{
	private:
		std::string	_filename;

	public:
		BitcoinExchange( std::string filename );
		~BitcoinExchange();
};

#endif
