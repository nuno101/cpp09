/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:04:31 by nuno              #+#    #+#             */
/*   Updated: 2023/07/26 11:08:23 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

/*
 * accept only digits, + - * / operators and space as input
 */
bool    validate_input(char *s)
{
	while(*s)
	{
		if (((int)(*s) >= '0' && (int)(*s) <= '9') || *s == ' ' || \
			*s == '+' || *s == '-' || *s == '*' || *s == '/')
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

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error: call like ./RPN \"<inverted Polish mathematical expression>\"" << std::endl;
        return (1);
    }
	if (validate_input(argv[1]))
	{
		RPN rpn(argv[1]);
		//calc.inspect_queue();
		std::cout << rpn.calculate() << std::endl;
	}
	else
		std::cout << "Error" << std::endl;
    return (0);
}
