/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:08:54 by nuno              #+#    #+#             */
/*   Updated: 2023/07/25 23:10:12 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/*
 * trim white space around str
 */
static  std::string trim(const std::string& str)
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
 * RPN constructor - loads the user input in the queue 
 */
RPN::RPN(std::string input)
{
	std::string	temp;
	std::size_t end;
	std::size_t len;

	std::cout << input << std::endl;

	end = 0;
	while (end != std::string::npos)
	{
		input = trim(input);
		len = input.size();
		end = input.find(" ");
		//std::cout << "End: " << end << std::endl;
		//std::cout << "Arg: " << input.substr(0, end) << std::endl;
		_queue.push(input.substr(0, end));
		input = input.substr(end + 1, len);
		//std::cout << "Input: " << input << std::endl;
	}
}

RPN::~RPN()
{
}

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

bool	RPN::validate_input()
{
	// TODO
	return (true);
}

static int	calc(int temp, int temp2, std::string operation)
{
	//std::cout << "temp: " << temp << " temp2: " << temp2 << " op: " << operation << std::endl;
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
		std::cout << "FATAL: Operator: " << operation << " not supported\n";
		exit(1);
	}
}

int	RPN::calculate()
{
	int	temp;
	int	temp2;
	std::string	op;

	temp = std::stoi(_queue.front());
	_queue.pop();
	while (!_queue.empty())
	{
		temp2 = std::stoi(_queue.front());
		_queue.pop();
		temp = calc(temp, temp2, _queue.front());
		_queue.pop();
		std::cout << "result: " << temp << std::endl;
	}
	return (temp);
}
