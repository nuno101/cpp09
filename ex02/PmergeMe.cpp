/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:08:13 by nuno              #+#    #+#             */
/*   Updated: 2023/07/27 23:00:09 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	//std::cout << "PmergeMe constructor called"<< std::endl;
}

PmergeMe::~PmergeMe()
{
}

/*
 * ingest user input into vector container 
 */
void	PmergeMe::load_vector(int argc, char **argv)
{
	t_pair	temp;
	int	i = 1;

	while (i < argc)
	{
		//std::cout << "argv[i] " << argv[i] << std::endl;
		temp.first = std::stoi(argv[i]);
		i++;
		if (i < argc)
		{
			//std::cout << "argv[i] " << argv[i] << std::endl;
			temp.second = std::stoi(argv[i]);
		}
		else
			temp.second = temp.first;
		_x_pairs.push_back(temp);
		i++;
	}
	//std::cout << "Elements added: " << i - 2 << std::endl;
}

int	PmergeMe::vector_sort_pairs()
{
	int	temp, min;

	min = _x_pairs.begin()->first;
	for (std::vector<t_pair>::iterator it = _x_pairs.begin(); it != _x_pairs.end(); it++)
	{
		if ((*it).first > (*it).second)
		{
			temp = (*it).first;
			(*it).first = (*it).second;
			(*it).second = temp;
		}
		if (min > (*it).first)
			min = (*it).first;
	}
	return (min);
}

void	PmergeMe::inspect_vector()
{
	for (std::vector<t_pair>::iterator it = _x_pairs.begin(); it != _x_pairs.end(); it++)
	{
		std::cout << "( " << (*it).first << " , " << (*it).second << " ) ";
	}
	std::cout << std::endl;
}

void	build_s_vector()
{

}
