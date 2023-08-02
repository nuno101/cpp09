/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:09:55 by nuno              #+#    #+#             */
/*   Updated: 2023/08/03 00:27:35 by nuno             ###   ########.fr       */
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
	std::vector<int>	_temp;
	std::vector<int>	_sequence;
	// deque containers 

public:
	PmergeMe();
	~PmergeMe();
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
};

#endif
