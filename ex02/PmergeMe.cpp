/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:08:13 by nuno              #+#    #+#             */
/*   Updated: 2023/08/03 00:06:32 by nuno             ###   ########.fr       */
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
 * Step 0: store user input in pairs within a vector container
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
	if (VERBOSE >= INFO)
		inspect_vector("Step 0: ");
}

/*
 * Step 1: Group the elements of X into n/2 floor pairs of elements, arbitrarily,
 * leaving one element unpaired if there is an odd number of elements.
 */
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
	if (VERBOSE >= INFO)
	{
		inspect_vector("Step 1: ");
		inspect_seq("Step 2: ");
	}
}

/*
 * Inspect the content of _x_pairs vector of integer pairs
 */
void	PmergeMe::inspect_vector(std::string prefix)
{
	std::cout << prefix;
	for (std::vector<t_pair>::iterator it = _x_pairs.begin(); it != _x_pairs.end(); it++)
	{
		std::cout << "( " << (*it).first << " , " << (*it).second << " ) ";
	}
	std::cout << std::endl;
}

/*
 * Inspect the content of _sequence vector of integers
 */
void	PmergeMe::inspect_seq(std::string prefix)
{
	std::cout << prefix; 
	if (VERBOSE >= INFO)
		std::cout << "( ";
	for (std::vector<int>::iterator it = _sequence.begin(); it != _sequence.end(); it++)
	{
		std::cout << *it;
		if ((it + 1) != _sequence.end())
		{
			if (VERBOSE >= INFO)
				std::cout << " , ";
			else
				std::cout << " ";
		}
	}
	if (VERBOSE >= INFO)
		std::cout << " )";
	std::cout << std::endl;
}

/*
 * Sort _sequence using the insertion-sort algorithm
 *
 * https://en.wikipedia.org/wiki/Insertion_sort
 * https://www.geeksforgeeks.org/cpp-program-for-insertion-sort/
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
	if (VERBOSE >= INFO)
		inspect_seq("Step 3: ");
}

/*
 * resize _sequence vector and add smallest to it's beginning
 */
static	void push_fwd(int smallest, std::vector<int> *list)
{
	int	i = (int) list->size();
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
	if (VERBOSE >= INFO)
		inspect_seq("Step 4: ");
	return (smallest);
}

/*
 * collect elements pending insertion into _temp
 */
int	PmergeMe::prepare_user_seq(int min)
{
	if (VERBOSE >= INFO)
		std::cout << "Elements pending insertion: ";
	for (std::vector<t_pair>::iterator it = _x_pairs.begin(); it != _x_pairs.end(); it++)
	{
		if ((*it).first != min && (*it).first > -1)
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
 * determine optimal order of inserting pending elements when relying 
 * in binary search to find each element's insertion location
 * call insert_pending() to insert the elements in the final sequence
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
				if (j - 3 < (int) _temp.size())
					insert_pending(j - 3);
			}
		}
		icount += pow2;
		i++;
	}
}

/*
 * insert element _temp.at(index) in _sequence
 *
 * binary search in sequence for insert position of each pending element
 * binary search from the start and up to but not including x_i to determine where to insert y_i
 */
void	PmergeMe::insert_pending(int index)
{
	int	i, j;
	for (i = 0; i < index + 3; i++)
	{
		if (i == 0 && _sequence.at(0) > _temp.at(index))
		{
			if (VERBOSE >= INFO)
				std::cout << " insert " << _temp.at(index) << " before " << _sequence.at(i);
			push_fwd(_temp.at(index), &_sequence);
			if (VERBOSE >= INFO)
				inspect_seq(" -->  ");
		}
		else if (_sequence.at(i) < _temp.at(index) && _sequence.at(i + 1) > _temp.at(index))
		{
			if (VERBOSE >= INFO)
				std::cout << " insert " << _temp.at(index) << " after " << _sequence.at(i);

			j = (int) _sequence.size();
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
