/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:07:00 by nuno              #+#    #+#             */
/*   Updated: 2023/08/03 14:11:01 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <queue>

#define ERROR 1
#define WARN 2
#define INFO 3
#define DEBUG 4

class	RPN
{
private:
	std::queue<std::string>	_queue;

public:
	RPN(std::string input);
	~RPN();
	RPN( const RPN &src );
	RPN &operator=( const RPN &src );

	void	inspect_queue();
	int		calculate();
}; 

#endif
