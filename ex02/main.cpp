/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:04:07 by nuno              #+#    #+#             */
/*   Updated: 2023/08/02 23:47:28 by nuno             ###   ########.fr       */
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

/*
 * Merge-insertion sort algorigthm implementations
 * 1. using a vector container
 * 2. using a dequeue container
 *
 * See also: https://en.wikipedia.org/wiki/Merge-insertion_sort
 */
int	main(int argc, char **argv)
{
	struct	timeval stop, start;
	int	i, min, duration;
	std::string	argv_str;

	gettimeofday(&start, NULL);
	i = 1;
	if (argc < 2)
	{
		std::cout << "Error: call like ./PmergeMe <positive integer(s) sequence>" << std::endl;
		return (1);
	}
	while (i < argc)
	{
		validate_input(argv[i]);
		argv_str += std::string(argv[i]) + " ";
		i++;
	}

	std::cout << "Before: " << argv_str << std::endl;
	PmergeMe pm;
	pm.load_vector(argc, argv);
	pm.vector_sort_pairs();
	pm.insertion_sort();
	min = pm.insert_smallest();
	int temp_size = pm.prepare_user_seq(min);
	pm.powerless_two(temp_size);
	pm.inspect_seq("After: ");

	// Execution time
	// See also: https://stackoverflow.com/questions/10192903/time-in-milliseconds-in-c
	gettimeofday(&stop, NULL);
 	duration = ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	std::cout << "Time to process a range of " << argc - 1 << " elements with std::vector : " << duration << " us\n"; 
	return (0);
}
