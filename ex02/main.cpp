/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:04:07 by nuno              #+#    #+#             */
/*   Updated: 2023/07/26 11:12:51 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: call like ./PmergeMe \"<positive integer sequence>\"" << std::endl;
		return (1);
	}
	std::cout << argv[1] << std::endl;
	return (0);
}
