/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:30:38 by luserbu           #+#    #+#             */
/*   Updated: 2023/04/21 18:36:28 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

RPN::RPN()
{
}

RPN::RPN( const RPN & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

RPN::~RPN()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

RPN &				RPN::operator=( RPN const & rhs )
{
	if ( this != &rhs )
	{
		// this->_value = rhs.getValue();
	}
	return *this;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void			RPN::polishNotation(char* notation) {

	std::stack<int> mystack;

	unsigned int length = strlen(notation);
	char value[length][2];

	easyCheck(notation);
	for (unsigned int i = 0; i < length; i++)
	{
		value[i][0] = notation[i];
		value[i][1] = '\0';
	}
	

	int tmpResult;
	int tmpStack;
	int result;
	for (unsigned int i = 0; i < length; i++)
	{
		if (notation[i] != ' ')
		{
			if (notation[i] >= '0' && notation[i] <= '9')
				mystack.push(atoi(value[i]));
			else
			{
				if (mystack.size() < 2 && i + 1 != length)
					throw (Expt());
				tmpResult = mystack.top();
				mystack.pop();
				tmpStack = mystack.top();
				mystack.pop();
				result = arithmetic(tmpStack, tmpResult, value[i][0]);
				mystack.push(result);
			}
		}
	}
	if (mystack.size() != 1)
		throw (Expt());
	std::cout << mystack.top() << '\n';

}


void		RPN::easyCheck(char *notation) {

	int i = 0;
	int nb = 0;
	int arth = 0;
	int tmp = 0;
	
	while (notation[i])
	{
		tmp = i;
		if (notation[i] >= '0' && notation[i] <= '9')
			nb += ++i;
		if ( notation[i] == '+' || notation[i] == '-' \
		|| notation[i] == '*' || notation[i] == '/')
			arth += ++i;
		if (notation[i] == ' ')
			i++;
		if (tmp == i)
			throw (Expt());
	}
	if (nb < 2 || arth < 1)
		throw (Expt());
}


int		RPN::arithmetic(int first, int second, char c) {

	
	if (c == '*')
		return (first * second);
	if (c == '/')
	{
		if (second == 0)
			throw (Expt());
		return (first / second);
	}
	if (c == '-')
		return (first - second);
	if (c == '+')
		return (first + second);
	throw (Expt());
	return (0);
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */


	// int length = strlen(notation);
	// char value[length][2];
	
	// for (unsigned int i = 0; i < length; i++)
	// {
	// 	value[i][0] = notation[i];
	// 	value[i][1] = '\0';
	// 	std::cout << value[i][0] << std::endl;
	// }
	
	// int result;
	
	// unsigned int i = 0;
	// while (i < length)
	// {
	// 	if (i == 0)
	// 	{
	// 		result = arithmetic(atoi(value[i]), atoi(value[i + 1]), value[i + 2][0]);
	// 		mystack.push(result);
	// 		i += 3;
	// 	}
	// 	else
	// 	{
	// 		result = result = arithmetic(atoi(value[]), atoi(value[i]), value[i + 2][0]);
	// 	}
	// }