/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:08:54 by nuno              #+#    #+#             */
/*   Updated: 2023/08/03 23:22:11 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/*
 * trim white space around str
 */
static	std::string trim(const std::string& str)
{
	if (str.empty())
		return ("");
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	if (first == std::string::npos || last == std::string::npos)
	{
		return ("");
	}
	return (str.substr(first, last - first + 1));
}

/*
 * RPN constructor - load the user input into the queue container
 */
RPN::RPN(std::string input)
{
	std::string	temp;
	std::size_t end;
	std::size_t len;

	if (VERBOSE >= INFO)
		std::cout << input << std::endl;
	end = 0;
	while (end != std::string::npos)
	{
		input = trim(input);
		len = input.size();
		end = input.find(" ");
		//std::cout << "Arg: " << input.substr(0, end) << std::endl;
		_queue.push(input.substr(0, end));
		input = input.substr(end + 1, len);
		//std::cout << "Input: " << input << std::endl;
	}
}

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN( const RPN &src )
{
	if ( VERBOSE >= DEBUG )
		std::cout << "Copy called" << std::endl;
	*this = src;
}

RPN & RPN::operator=( const RPN &src )
{
	if ( VERBOSE >= DEBUG )
		std::cout << "Assign called" << std::endl;
	this->_queue = src._queue;
	return *this ;
}

/*
 * NOTE: inspecting the queue will empty the queue container.
 * Use only for debugging purposes
 */
void	RPN::inspect_queue()
{
	std::cout << "Queue inspector:" << std::endl;
	while (!_queue.empty())
	{
		std::cout << _queue.front() << std::endl;
		_queue.pop();
	}
	std::cout << std::endl;
}

/*
 * perform one operation
 */
static int	calc(int temp, int temp2, std::string operation)
{
	if (VERBOSE >= INFO)
		std::cout << "calc: " << temp << " " << operation << " " << temp2 << std::endl;

	if (operation.compare("+") == 0)
		return (temp + temp2);
	else if (operation.compare("-") == 0)
		return (temp - temp2);
	else if (operation.compare("*") == 0)
		return (temp * temp2);
	else if (operation.compare("/") == 0)
		return (temp / temp2);
	else
	{
		if (VERBOSE >= ERROR)
			std::cout << "FATAL: Operator: " << operation << " not supported\n";
		else
			std::cout << "Error" << std::endl;
		exit(1);
	}
}

/*
 * dequeue the arguments to perform the calculation
 */
int	RPN::calculate()
{
	int	temp;
	int	temp2;
	std::string	op;

	try
	{
		temp = std::stoi(_queue.front());
		_queue.pop();
		while (!_queue.empty())
		{
			temp2 = std::stoi(_queue.front());
			_queue.pop();
			temp = calc(temp, temp2, _queue.front());
			_queue.pop();
			if (VERBOSE >= INFO)
				std::cout << "result: " << temp << std::endl;
		}
		return (temp);
	}
	catch (const std::invalid_argument& ia)
	{
		if (VERBOSE >= ERROR)
			std::cout << "FATAL: invalid argument: " << ia.what() << std::endl;
		else
			std::cout << "Error" << std::endl;
		exit(1);
	}
	catch (const std::length_error le)
	{
		if (VERBOSE >= ERROR)
			std::cout << "FATAL: last operator missing" << std::endl;
		else
			std::cout << "Error" << std::endl;
		exit(1);
	}
}
