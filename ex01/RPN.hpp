/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:07:00 by nuno              #+#    #+#             */
/*   Updated: 2023/07/25 17:09:56 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>

#define ERROR 1
#define WARN 2
#define INFO 3
#define DEBUG 4

typedef struct s_log
{
    std::string _date;
    float       _value;
}   t_log;

class	RPN
{
private:

public:
	RPN();
	~RPN();
}; 

#endif
