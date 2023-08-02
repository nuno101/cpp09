/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:08:13 by nuno              #+#    #+#             */
/*   Updated: 2023/08/02 18:18:36 by nuno             ###   ########.fr       */
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
		temp.first = std::stoi(argv[i]);
		i++;
		if (i < argc)
		{
			temp.second = std::stoi(argv[i]);
		}
		else // handle odd nr of elements
			temp.second = -1;
		_x_pairs.push_back(temp);
		i++;
	}
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

void	PmergeMe::inspect_vector(std::string prefix)
{
	std::cout << prefix;
	for (std::vector<t_pair>::iterator it = _x_pairs.begin(); it != _x_pairs.end(); it++)
	{
		std::cout << "( " << (*it).first << " , " << (*it).second << " ) ";
	}
	std::cout << std::endl;
}

void	PmergeMe::inspect_seq(std::string prefix)
{
	std::cout << prefix; 
	if (VERBOSE >= INFO)
		std::cout << "( ";
	for (std::vector<int>::iterator it = _sequence.begin(); it != _sequence.end(); it++)
	{
		std::cout << *it;
		if ((it + 1) != _sequence.end())
			std::cout << " , ";
	}
	if (VERBOSE >= INFO)
		std::cout << " )";
	std::cout << std::endl;
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
 * resize _sequence vector and add smallest to it's beginning
 */
static	void push_fwd(int smallest, std::vector<int> *list)
{
	int i = (int) list->size();
	list->resize(i + 1);
	while (i > 0)
	{
		list->at(i) = list->at(i - 1); 
		i--;
	}
	list->at(0) = smallest;
}

/*
 * find pair of smallest
 * resize _sequence vector and add smallest to it's beginning
 */
int	PmergeMe::insert_smallest()
{
	int	smallest, second;

	second = _sequence.at(0);
	for (std::vector<t_pair>::iterator it = _x_pairs.begin(); it != _x_pairs.end(); it++)
	{
		if ((*it).second == second)
			smallest = (*it).first;
	}
	if (smallest > -1)
		push_fwd(smallest, &_sequence);
	return (smallest);
}

/*
 * prepare user input in correct order of insertion
 */
int	PmergeMe::prepare_user_seq(int min)
{
	// collect elements pending insertion into _temp 
	if (VERBOSE >= INFO)
		std::cout << "Pending insertion: ";
	for (std::vector<t_pair>::iterator it = _x_pairs.begin(); it != _x_pairs.end(); it++)
	{
		if ((*it).first != min)
		{
			_temp.push_back((*it).first);
			if (VERBOSE >= INFO)
				std::cout << (*it).first << " ";
		}
	}
	if (VERBOSE >= INFO)
		std::cout << "\n";
	return (_temp.size());
}

/*
 * one less than a power of two
 */
void	PmergeMe::powerless_two(int size)
{
	int	pow2, i, icount;

	i = 1;
	icount = 0;
	pow2 = 0;

	while(icount < size + 2)
	{
		pow2 = pow(2, i) - pow2;
		if (icount >= 2)
		{
			if (VERBOSE >= DEBUG)
				std::cout << "pow(2," << i << ") - pow(2," << i-1 << ") -->  group size: " << pow2 << "\n";
			for (int j = icount + pow2; j > icount; j--)
			{
				insert_pending(j - 3);
			}
		}
		icount += pow2;
		i++;
	}
}

/*
 * binary search in sequence for insert position of each pending element
 * binary search from the start and up to but not including x_i to determine where to insert y_i
 */
void	PmergeMe::insert_pending(int index)
{
	if (index < (int) _temp.size())
	{
		for (int i = 0; i < index + 3; i++)
		{
			if (i == 0 && _sequence.at(0) > _temp.at(index))
			{
				if (VERBOSE >= INFO)
					std::cout << " insert " << _temp.at(index) << " before " << _sequence.at(i);
				push_fwd(_temp.at(index), &_sequence);
				inspect_seq(" -->  ");
			}
			else if (_sequence.at(i) < _temp.at(index) && _sequence.at(i + 1) > _temp.at(index))
			{
				if (VERBOSE >= INFO)
					std::cout << " insert " << _temp.at(index) << " after " << _sequence.at(i);

				int j = (int) _sequence.size();
				_sequence.resize(j + 1);
				while (j > i + 1)
				{
					_sequence.at(j) = _sequence.at(j - 1); 
					j--;
				}
				_sequence.at(j) = _temp.at(index);
				if (VERBOSE >= INFO)
					inspect_seq(" -->  ");
			}
		}
	}
}
