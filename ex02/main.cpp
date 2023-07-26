/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:04:07 by nuno              #+#    #+#             */
/*   Updated: 2023/07/26 11:51:40 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <iostream>
#include "PmergeMe.hpp"

/*
 * accept only digits and space as input
 */
bool	validate_input(char *s)
{
	while(*s)
	{
		if (((int)(*s) >= '0' && (int)(*s) <= '9') || *s == ' ')
		{
			if (VERBOSE >= DEBUG)
				std::cout << *s << " OK" << std::endl;
		}
		else
		{
			if (VERBOSE >= DEBUG)
				std::cout << *s << " NOK" << std::endl;
			std::cout << "Error" << std::endl;
			exit(1);
		}
		s++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	struct	timeval stop, start;
	gettimeofday(&start, NULL);

	int	i = 1;

	if (argc < 2)
	{
		std::cout << "Error: call like ./PmergeMe <positive integer(s) sequence>" << std::endl;
		return (1);
	}
	while (i < argc)
	{
		validate_input(argv[i]);
		i++;
	}
	//TODO
	std::cout << "Before: TODO!" << std::endl;
	std::cout << "After: TODO!" << std::endl;

	// Execution time
	gettimeofday(&stop, NULL);
	std::cout << ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec) << " us\n"; 
	return (0);
}
