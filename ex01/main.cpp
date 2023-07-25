/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:04:31 by nuno              #+#    #+#             */
/*   Updated: 2023/07/25 23:12:11 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    if (argc != 2)
    {
        std::cout << "Error: call like ./RPN \"<inverted Polish mathematical expression>\"" << std::endl;
        return (1);
    }
	RPN rpn(argv[1]);
	//calc.inspect_queue();
	if (rpn.validate_input())
		std::cout << rpn.calculate() << std::endl;
	else
		std::cout << "Error" << std::endl;
    return (0);
}
