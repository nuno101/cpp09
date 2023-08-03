/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:08:13 by nuno              #+#    #+#             */
/*   Updated: 2023/08/03 14:18:28 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

PmergeMe::PmergeMe( const PmergeMe &src )
{
    if ( VERBOSE >= DEBUG )
        std::cout << "Copy called" << std::endl;
    *this = src;
}

PmergeMe & PmergeMe::operator=( const PmergeMe &src )
{
    if ( VERBOSE >= DEBUG )
        std::cout << "Assign called" << std::endl;
    this->_v_pairs = src._v_pairs;
    this->_temp_vector = src._temp_vector;
    this->_sequence = src._sequence;
    this->_q_pairs = src._q_pairs;
    this->_temp_deque = src._temp_deque;
    this->_deque = src._deque;
    return *this ;
}

/*
 * Step 0: store user input in pairs within a vector container
 */
void	PmergeMe::store_input(int argc, char **argv)
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
		_v_pairs.push_back(temp);
		i++;
	}
	if (VERBOSE >= INFO)
		inspect_pairs("Step 0: ");
}

/*
 * Step 1: Group the elements of X into n/2 floor pairs of elements, arbitrarily,
 * leaving one element unpaired if there is an odd number of elements.
 */
void	PmergeMe::vector_sort_pairs()
{
	int	temp;

	for (std::vector<t_pair>::iterator it = _v_pairs.begin(); it != _v_pairs.end(); it++)
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
		inspect_pairs("Step 1: ");
		inspect_vector("Step 2: ");
	}
}

/*
 * Inspect the content of _v_pairs vector of integer pairs
 */
void	PmergeMe::inspect_pairs(std::string prefix)
{
	std::cout << prefix;
	for (std::vector<t_pair>::iterator it = _v_pairs.begin(); it != _v_pairs.end(); it++)
	{
		std::cout << "( " << (*it).first << " , " << (*it).second << " ) ";
	}
	std::cout << std::endl;
}

/*
 * Inspect the content of _sequence vector of integers
 */
void	PmergeMe::inspect_vector(std::string prefix)
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
		inspect_vector("Step 3: ");
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
	for (std::vector<t_pair>::iterator it = _v_pairs.begin(); it != _v_pairs.end(); it++)
	{
		if ((*it).second == second)
			smallest = (*it).first;
	}
	if (smallest > -1)
		push_fwd(smallest, &_sequence);
	if (VERBOSE >= INFO)
		inspect_vector("Step 4: ");
	return (smallest);
}

/*
 * collect elements pending insertion into _temp_vector
 */
int	PmergeMe::collect_pending(int min)
{
	if (VERBOSE >= INFO)
		std::cout << "Elements pending insertion: ";
	for (std::vector<t_pair>::iterator it = _v_pairs.begin(); it != _v_pairs.end(); it++)
	{
		if ((*it).first != min && (*it).first > -1)
		{
			_temp_vector.push_back((*it).first);
			if (VERBOSE >= INFO)
				std::cout << (*it).first << " ";
		}
	}
	if (VERBOSE >= INFO)
		std::cout << "\n";
	return (_temp_vector.size());
}

/*
 * determine optimal order of inserting pending elements when relying 
 * in binary search to find each element's insertion location
 * call insert_pending() to insert the elements in the final sequence
 */
void	PmergeMe::order_and_insert_pending(int size)
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
				if (j - 3 < (int) _temp_vector.size())
					insert_pending(j - 3);
			}
		}
		icount += pow2;
		i++;
	}
}

/*
 * insert element _temp_vector.at(index) in _sequence
 *
 * binary search in sequence for insert position of each pending element
 * binary search from the start and up to but not including x_i to determine where to insert y_i
 */
void	PmergeMe::insert_pending(int index)
{
	int	i, j;
	for (i = 0; i < index + 3; i++)
	{
		if (i == 0 && _sequence.at(0) > _temp_vector.at(index))
		{
			if (VERBOSE >= INFO)
				std::cout << " insert " << _temp_vector.at(index) << " before " << _sequence.at(i);
			push_fwd(_temp_vector.at(index), &_sequence);
			if (VERBOSE >= INFO)
				inspect_vector(" -->  ");
		}
		else if (_sequence.at(i) < _temp_vector.at(index) && _sequence.at(i + 1) > _temp_vector.at(index))
		{
			if (VERBOSE >= INFO)
				std::cout << " insert " << _temp_vector.at(index) << " after " << _sequence.at(i);

			j = (int) _sequence.size();
			_sequence.resize(j + 1);
			while (j > i + 1)
			{
				_sequence.at(j) = _sequence.at(j - 1); 
				j--;
			}
			_sequence.at(j) = _temp_vector.at(index);
			if (VERBOSE >= INFO)
				inspect_vector(" -->  ");
		}
	}
}

/*
 * Step 0: store user input in pairs within a vector container
 */
void	PmergeMe::deque_store_input(int argc, char **argv)
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
		_q_pairs.push_back(temp);
		i++;
	}
	if (VERBOSE >= INFO)
		deque_inspect_pairs("Step 0: ");
}

/*
 * Step 1: Group the elements of X into n/2 floor pairs of elements, arbitrarily,
 * leaving one element unpaired if there is an odd number of elements.
 */
void	PmergeMe::deque_sort_pairs()
{
	int	temp;

	for (std::deque<t_pair>::iterator it = _q_pairs.begin(); it != _q_pairs.end(); it++)
	{
		if ((*it).first > (*it).second)
		{
			temp = (*it).first;
			(*it).first = (*it).second;
			(*it).second = temp;
		}
		_deque.push_back((*it).second);
	}
	if (VERBOSE >= INFO)
	{
		deque_inspect_pairs("Step 1: ");
		inspect_deque("Step 2: ");
	}
}

/*
 * Inspect the content of _q_pairs vector of integer pairs
 */
void	PmergeMe::deque_inspect_pairs(std::string prefix)
{
	std::cout << prefix;
	for (std::deque<t_pair>::iterator it = _q_pairs.begin(); it != _q_pairs.end(); it++)
	{
		std::cout << "( " << (*it).first << " , " << (*it).second << " ) ";
	}
	std::cout << std::endl;
}

/*
 * Inspect the content of _deque deque of integers
 */
void	PmergeMe::inspect_deque(std::string prefix)
{
	std::cout << prefix; 
	if (VERBOSE >= INFO)
		std::cout << "( ";
	for (std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); it++)
	{
		std::cout << *it;
		if ((it + 1) != _deque.end())
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
 * Sort _deque using the insertion-sort algorithm
 *
 * https://en.wikipedia.org/wiki/Insertion_sort
 * https://www.geeksforgeeks.org/cpp-program-for-insertion-sort/
 */
void	PmergeMe::deque_insertion_sort()
{
	int	i, j, temp;

	i = 1;
	while (i < (int)_deque.size())
	{
		temp = _deque.at(i); 
		j = i - 1;
		while ( j >= 0 && (_deque.at(j) > temp) )
		{
			_deque.at(j + 1) = _deque.at(j); 
			j--;
		}
		_deque.at(j + 1) = temp;
		i++;
	}
	if (VERBOSE >= INFO)
		inspect_deque("Step 3: ");
}

/*
 * find pair of smallest
 * add smallest to deque beginning
 */
int	PmergeMe::deque_insert_smallest()
{
	int	smallest, second;

	second = _deque.at(0);
	for (std::deque<t_pair>::iterator it = _q_pairs.begin(); it != _q_pairs.end(); it++)
	{
		if ((*it).second == second)
			smallest = (*it).first;
	}
	if (smallest > -1)
		_deque.push_front(smallest);
	if (VERBOSE >= INFO)
		inspect_deque("Step 4: ");
	return (smallest);
}

/*
 * collect elements pending insertion into _temp_deque
 */
int	PmergeMe::deque_collect_pending(int min)
{
	if (VERBOSE >= INFO)
		std::cout << "Elements pending insertion: ";
	for (std::deque<t_pair>::iterator it = _q_pairs.begin(); it != _q_pairs.end(); it++)
	{
		if ((*it).first != min && (*it).first > -1)
		{
			_temp_deque.push_back((*it).first);
			if (VERBOSE >= INFO)
				std::cout << (*it).first << " ";
		}
	}
	if (VERBOSE >= INFO)
		std::cout << "\n";
	return (_temp_deque.size());
}

/*
 * determine optimal order of inserting pending elements when relying 
 * in binary search to find each element's insertion location
 * call insert_pending() to insert the elements in the final sequence
 */
void	PmergeMe::deque_order_and_insert_pending(int size)
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
				if (j - 3 < (int) _temp_deque.size())
					deque_insert_pending(j - 3);
			}
		}
		icount += pow2;
		i++;
	}
}

/*
 * insert element _temp_vector.at(index) in _deque
 *
 * binary search in sequence for insert position of each pending element
 * binary search from the start and up to but not including x_i to determine where to insert y_i
 */
void	PmergeMe::deque_insert_pending(int index)
{
	int	i, j;
	for (i = 0; i < index + 3; i++)
	{
		if (i == 0 && _deque.at(0) > _temp_vector.at(index))
		{
			if (VERBOSE >= INFO)
				std::cout << " insert " << _temp_vector.at(index) << " before " << _deque.at(i);
			_deque.push_front(_temp_deque.at(index));
			if (VERBOSE >= INFO)
				inspect_deque(" -->  ");
		}
		else if (_deque.at(i) < _temp_deque.at(index) && _deque.at(i + 1) > _temp_deque.at(index))
		{
			if (VERBOSE >= INFO)
				std::cout << " insert " << _temp_deque.at(index) << " after " << _deque.at(i);

			j = (int) _deque.size();
			_deque.resize(j + 1);
			while (j > i + 1)
			{
				_deque.at(j) = _deque.at(j - 1); 
				j--;
			}
			_deque.at(j) = _temp_deque.at(index);
			if (VERBOSE >= INFO)
				inspect_deque(" -->  ");
		}
	}
}
