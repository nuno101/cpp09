/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:09:55 by nuno              #+#    #+#             */
/*   Updated: 2023/08/01 16:07:22 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

#include <iostream>
#include <vector>
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
	std::vector<t_pair>	_x_pairs;
	std::vector<int>	_sequence;

public:
	PmergeMe();
	~PmergeMe();

	void	load_vector(int argc, char **argv);
	void	vector_sort_pairs();
	void	inspect_vector();
	void	inspect_seq(std::string prefix);
	void	insertion_sort();
	int		insert_smallest();
	void	prepare_user_seq(int min);
	void	powerless_two(int size);
};

#endif
