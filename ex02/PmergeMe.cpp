/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:47:20 by luserbu           #+#    #+#             */
/*   Updated: 2023/04/22 17:47:54 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*
** --------------------------------- METHODS ----------------------------------
*/

void		PmergeMe::mergeSort(char **sort) {

	generalTime = start_time();

	easyFindError(sort);

	int lengthSort = lengthDoubleTab(sort);
	std::vector<int> vecSort(lengthSort);
	std::list<int> listSort(lengthSort);
	int stack[lengthSort];

	for (int i = 0; i < lengthSort; i++)
		stack[i] = atoi(sort[i + 1]);
	
	int pointer = 0;
	vectorTime = time_now();
	while (pointer < lengthSort)
	{
		vecSort = sortVector(vecSort, stack, pointer, lengthSort);
		pointer += 6;
	}
	vectorTime = time_now() - vectorTime;
	pointer = 0;
	listTime = time_now();
	while (pointer < lengthSort)
	{
		listSort = sortList(listSort, stack, pointer, lengthSort);
		pointer += 6;
	}
	listTime = time_now() - listTime - vectorTime;
	printInfo(stack, lengthSort, vecSort);
}

void			PmergeMe::printInfo(int *stack, int lengthSort, std::vector<int> vecSort) {

    std::cout << "Before:\t";
	for (int i = 0; i < lengthSort; i++)
	{
    	std::cout << stack[i] << " ";
	}
    std::cout << std::endl;

	std::cout << "After:\t";
	for (std::vector<int>::iterator it=vecSort.begin(); it!=vecSort.end(); ++it)
    	std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << lengthSort << " elements with std::[..] : " << vectorTime << "μs" << std::endl;
    std::cout << "Time to process a range of " << lengthSort << " elements with std::[..] : " << listTime << "μs" << std::endl;

}


void			PmergeMe::easyFindError(char **tab) {

	int i = 1;
	char *pEnd;

	while (tab[i])
	{
		for (int nan = 0; tab[i][nan]; nan++)
		{
			if (tab[i][nan] >= '0' && tab[i][nan] <= '9');
			else
				throw (Expt());
		}
		if (tab[i] == NULL)
			throw (Expt());
		if (!strtod(tab[i], &pEnd) && strlen(tab[i]) < 1)
			throw (Expt());
		if (strtod(tab[i], &pEnd) > INT_MAX || strtod(tab[i], &pEnd) < 0)
			throw (Expt());
		i++;
	}
}

std::vector<int>		PmergeMe::sortVector(std::vector<int> vecSort, int *stack, int pointer, int length) {

	int i = 0;
	std::vector<int> stackRight;
	std::vector<int> stackLeft;

	int begin_pointer = pointer;
	int diff = length - pointer;

	while (i < begin_pointer + 6)
	{
		if (pointer < length)
		{
			if (i < 3 && begin_pointer == 0 && diff >= 3)
				stackLeft.push_back(stack[pointer++]);
			else
				stackRight.push_back(stack[pointer++]);
		}
		else if (i < begin_pointer + diff)
			stackLeft.push_back(vecSort[i - diff]);
		i++;
	}

	std::vector<int>::iterator itStackLeft = stackLeft.begin();
	std::vector<int>::iterator iteStackLeft = stackLeft.end();

	std::vector<int>::iterator itStackRight = stackRight.begin();
	std::vector<int>::iterator iteStackRight = stackRight.end();

	std::sort(itStackLeft, iteStackLeft);
	std::sort(itStackRight, iteStackRight);
	std::merge (itStackLeft, iteStackLeft, itStackRight, iteStackRight, vecSort.begin());

	for (int len = 0; len < begin_pointer + 3; len++)
	{
		if (stackLeft.size() > 0)
			stackLeft.pop_back();
		if (stackRight.size() > 0)
			stackRight.pop_back();
	}
	return (vecSort);
}

std::list<int>		PmergeMe::sortList(std::list<int> listSort, int *stack, int pointer, int length) {

	int i = 0;
	std::list<int> stackRight;
	std::list<int> stackLeft;

	int begin_pointer = pointer;
	int diff = length - pointer;

	std::list<int>::iterator itListSort = listSort.begin();

	for (int len = 0; len < begin_pointer + 3; len++)
	{
		if (stackLeft.size() > 0)
			stackLeft.pop_back();
		if (stackRight.size() > 0)
			stackRight.pop_back();
	}

	while (i < begin_pointer + 6)
	{
		if (pointer < length)
		{
			if (i < 3 && begin_pointer == 0 && diff >= 3)
				stackLeft.push_back(stack[pointer++]);
			else
				stackRight.push_back(stack[pointer++]);
		}
		else if (i < begin_pointer + diff)
		{
			int tmp = *itListSort;
			stackLeft.push_back(tmp);
			itListSort++;
		}
		i++;
	}

	stackRight.sort();
	stackLeft.sort();

	stackRight.merge(stackLeft);

	return (stackRight);
}

int			PmergeMe::lengthDoubleTab(char **tab) {

	int i = 1;

	while (tab[i])
		i++;
	return (i - 1);
}

double	PmergeMe::start_time(void) {

	struct timeval	time_current;
	double	time;

	gettimeofday(&time_current, NULL);
	time = ((time_current.tv_usec + \
	(time_current.tv_sec * 1000000)));
	return (time);
}

double	PmergeMe::time_now(void)
{
	struct timeval	time_current;
	double	time;

	gettimeofday(&time_current, NULL);
	time = ((time_current.tv_usec + \
	(time_current.tv_sec * 1000000))) - \
	generalTime;
	return (time);
}

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe( const PmergeMe & src )
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

PmergeMe::~PmergeMe()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

PmergeMe &				PmergeMe::operator=( PmergeMe const & rhs )
{
	if ( this != &rhs )
	{
		// this->_value = rhs.getValue();
	}
	return *this;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */