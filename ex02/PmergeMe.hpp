/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:09:55 by nuno              #+#    #+#             */
/*   Updated: 2023/08/03 14:16:01 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <cmath>

#define ERROR 1
#define WARN 2
#define INFO 3
#define DEBUG 4

typedef	struct s_pair
{
	int	first;
	int	second;
} t_pair;

class	PmergeMe
{
private:
	// vector containers 
	std::vector<t_pair>	_v_pairs;
	std::vector<int>	_temp_vector;
	std::vector<int>	_sequence;
	// deque containers 
	std::deque<t_pair>	_q_pairs;
	std::deque<int>	_temp_deque;
	std::deque<int>	_deque;

public:
	PmergeMe();
	~PmergeMe();
	PmergeMe( const PmergeMe &src );
	PmergeMe &operator=( const PmergeMe &src );

	// vector container methods
	void	store_input(int argc, char **argv);
	void	vector_sort_pairs();
	void	inspect_pairs(std::string prefix);
	void	inspect_vector(std::string prefix);
	void	insertion_sort();
	int		insert_smallest();
	int		collect_pending(int min);
	void	order_and_insert_pending(int size);
	void	insert_pending(int index);
	// deque container methods
	void	deque_store_input(int argc, char **argv);
	void	deque_sort_pairs();
	void	deque_inspect_pairs(std::string prefix);
	void	inspect_deque(std::string prefix);
	void	deque_insertion_sort();
	int		deque_insert_smallest();
	int		deque_collect_pending(int min);
	void	deque_order_and_insert_pending(int size);
	void	deque_insert_pending(int index);
};

#endif
