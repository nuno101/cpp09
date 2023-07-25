/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 22:45:50 by nuno              #+#    #+#             */
/*   Updated: 2023/07/25 16:54:23 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	if (argc != 2)
	{
		std::cout << "Error: call like ./btc <filename>" << std::endl;
		return (1);
	}
	BitcoinExchange bx("data.csv");
	bx.process_input(argv[1]);
	return (0);
}
