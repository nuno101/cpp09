/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:08:13 by nuno              #+#    #+#             */
/*   Updated: 2023/08/01 23:15:10 by nuno             ###   ########.fr       */
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
		else // handle odd nr of elements
			temp.second = -1;
			//temp.second = temp.first;
		_x_pairs.push_back(temp);
		i++;
	}
	//std::cout << "Elements added: " << i - 2 << std::endl;
}

void	PmergeMe::vector_sort_pairs()
{
	int	temp;

	for (std::vector<t_pair>::iterator it = _x_pairs.begin(); it != _x_pairs.end(); it++)
	{
		if ((*it).first > (*it).second)
		{
			temp = (*it).first;
			(*it).first = (*it).second;
			(*it).second = temp;
		}
		_sequence.push_back((*it).second);
	}
}

void	PmergeMe::inspect_vector()
{
	for (std::vector<t_pair>::iterator it = _x_pairs.begin(); it != _x_pairs.end(); it++)
	{
		std::cout << "( " << (*it).first << " , " << (*it).second << " ) ";
	}
	std::cout << std::endl;
}

void	PmergeMe::inspect_seq(std::string prefix)
{
	std::cout << prefix << "Sequence: (";
	for (std::vector<int>::iterator it = _sequence.begin(); it != _sequence.end(); it++)
	{
		std::cout << *it;
		if ((it + 1) != _sequence.end())
			std::cout << " , ";
	}
	std::cout << " )" << std::endl;
}
/*
https://en.wikipedia.org/wiki/Insertion_sort
https://www.geeksforgeeks.org/cpp-program-for-insertion-sort/
*/
void	PmergeMe::insertion_sort()
{
	int	i, j, temp;

	i = 1;
	while (i < (int)_sequence.size())
	{
		temp = _sequence.at(i); 
		j = i - 1;
		while ( j >= 0 && (_sequence.at(j) > temp) )
		{
			_sequence.at(j + 1) = _sequence.at(j); 
			j--;
		}
		_sequence.at(j + 1) = temp;
		i++;
	}
}

/*
 * find pair of smallest
 * resize _sequence vector and add smallest to it's beginning
 */
int	PmergeMe::insert_smallest()
{
	int	i, smallest, second;

	second = _sequence.at(0);
	for (std::vector<t_pair>::iterator it = _x_pairs.begin(); it != _x_pairs.end(); it++)
	{
		if ((*it).second == second)
		{
			smallest = (*it).first;
		}
	}
	if (smallest == -1)
		return (smallest);
	i = (int) _sequence.size();
	_sequence.resize(i + 1);
	while (i > 0)
	{
		_sequence.at(i) = _sequence.at(i - 1); 
		i--;
	}
	_sequence.at(0) = smallest;
	return (smallest);
}

/*
 * prepare user input in correct order of insertion
 */
int	PmergeMe::prepare_user_seq(int min)
{
	// collect elements pending insertion
	std::cout << "To insert: ";
	for (std::vector<t_pair>::iterator it = _x_pairs.begin(); it != _x_pairs.end(); it++)
	{
		if ((*it).first != min)// && (*it).first >= 0)
		{
			_temp.push_back((*it).first);
			std::cout << (*it).first << " ";
		}
	}
	std::cout << "\n";
	return (_temp.size());
}

/*
 * one less than a power of two
 */
void	PmergeMe::powerless_two(int size)
{
	int	pow2, i;

	i = 1;
	pow2 = 0;
	int icount = 0;

	//while(i < (size + 2))
	while(icount < size + 2)
	{
		pow2 = pow(2, i) - pow2;
		std::cout << "i " << i << " group of " << pow2 << "\n";
		if (icount >= 2)
		{
			std::cout << "insert index: ";
			for (int j = icount + pow2; j > icount; j--)
			{
				std::cout << j << " " ;
				insert_pending(j - 3);
			}
			std::cout << "\n";
		}
		icount += pow2;
		//std::cout << "icount " << icount << "\n";
		i++;
	}
}

void	PmergeMe::insert_pending(int index)
{
	if (index < (int) _temp.size())
		_sequence.push_back(_temp.at(index));
}
