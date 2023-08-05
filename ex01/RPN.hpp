/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:07:00 by nuno              #+#    #+#             */
/*   Updated: 2023/08/05 12:38:15 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <list>

#define ERROR 1
#define WARN 2
#define INFO 3
#define DEBUG 4

class	RPN
{
private:
	std::list<std::string>	_list;

public:
	RPN(std::string input);
	RPN();
	~RPN();
	RPN( const RPN &src );
	RPN &operator=( const RPN &src );

	void	inspect_list();
	int		process_list();
}; 

#endif
