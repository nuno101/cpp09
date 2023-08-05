/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nlouro@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:08:54 by nuno              #+#    #+#             */
/*   Updated: 2023/08/05 18:06:32 by nuno             ###   ########.fr       */
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

static	bool is_operator(std::string str)
{
	if (str.compare("+") == 0 || str.compare("-") == 0 || \
		str.compare("*") == 0 || str.compare("/") == 0)
		return (true);
	else
		return (false);
}

/*
 * RPN constructor - load the user input into the list container
 */
RPN::RPN(std::string input)
{
	std::string	temp;
	std::size_t end;
	std::size_t len;
	int	result;

	if (VERBOSE >= INFO)
		std::cout << input << std::endl;
	end = 0;
	while (end != std::string::npos)
	{
		input = trim(input);
		len = input.size();
		end = input.find(" ");
		//std::cout << "Arg: " << input.substr(0, end) << std::endl;
		_list.push_back(input.substr(0, end));
		if (_list.size() > 2 && is_operator(_list.back()))
		{
			//std::cout << "Operator found: " << _list.back() << std::endl;
			result = process_list();
		}
		input = input.substr(end + 1, len);
		//std::cout << "Input: " << input << std::endl;
	}
	if (_list.size() > 1)
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}
	std::cout << result << std::endl;
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
	this->_list = src._list;
	return *this ;
}

/*
 * NOTE: inspecting the list will empty the list container.
 * Use only for debugging purposes
 */
void	RPN::inspect_list()
{
	std::cout << "list inspector:" << std::endl;
	while (!_list.empty())
	{
		std::cout << _list.front() << std::endl;
		_list.pop_front();
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
	{
		if (temp2 == 0)
		{
			std::cout << "Error" << std::endl;
			exit(1);
		}
		else
			return (temp / temp2);
	}
	else
	{
		if (VERBOSE >= ERROR)
			std::cout << "FATAL: Operator: " << operation << " not supported\n";
		else
			std::cout << "Error" << std::endl;
		exit(1);
	}
}

int	RPN::process_list()
{
	int	temp, temp2, result;
	std::string	op;

	try
	{
		op = _list.back();
		_list.pop_back();
		temp2 = std::stoi(_list.back());
		_list.pop_back();
		temp = std::stoi(_list.back());
		_list.pop_back();
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
	result = calc(temp, temp2, op);
	//std::cout << "result: " << result << "\n" << std::endl;
	_list.push_back(std::to_string(result));
	return (result);
}
