/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:04:31 by nuno              #+#    #+#             */
/*   Updated: 2023/07/25 17:06:17 by nuno             ###   ########.fr       */
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
    return (0);
}