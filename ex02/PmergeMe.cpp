/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:47:20 by luserbu           #+#    #+#             */
/*   Updated: 2023/04/25 21:33:59 by luserbu          ###   ########.fr       */
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
	
	int stack[lengthSort];

	for (int i = 0; i < lengthSort; i++)
		stack[i] = atoi(sort[i + 1]);

	std::deque<int> dequeSort(stack, stack+lengthSort);
	std::vector<int> vecSort(stack, stack+lengthSort);

	parsingTime = time_now();
	
	vectorTime = time_now();
	vecSort = sortVector(vecSort, 0, lengthSort);
	vectorTime = time_now() - vectorTime;
	

	generalTime = start_time();

	dequeTime = time_now() - parsingTime;
	dequeSort = sortDeque(dequeSort, 0, lengthSort);
	dequeTime = time_now() - dequeTime - parsingTime;
	
	printInfo(stack, lengthSort, dequeSort);
}

void			PmergeMe::printInfo(int *stack, int lengthSort, std::deque<int> vecSort) {

    std::cout << "Before:\t";
	for (int i = 0; i < lengthSort; i++)
	{
    	std::cout << stack[i] << " ";
	}
    std::cout << std::endl;

	std::cout << "After:\t";
	for (std::deque<int>::iterator it=vecSort.begin(); it!=vecSort.end(); ++it)
    	std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << lengthSort << " elements with std::vector : " << vectorTime << "μs" << std::endl;
    std::cout << "Time to process a range of " << lengthSort << " elements with std::deque : " << dequeTime << "μs" << std::endl;
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

int 	PmergeMe::findVecIterator(std::vector<int> stack, int nb, int start) {

	int i = start;
	std::vector<int>::iterator it = stack.begin()+start;
	
	while (it != stack.end())
	{
		if (*it == nb)
			return (i);
		it++;
		i++;
	}
	return (i);
}

std::vector<int> 		PmergeMe::insertVecSort(std::vector<int> vecSort, int start, int end) {

	std::vector<int> finalSort;
	
	std::vector<int>::iterator it = vecSort.begin()+start;

	for (int i = start; i < end; i++)
	{
		finalSort.push_back(*it);
		it++;
	}

	it = finalSort.begin();
	std::vector<int>::iterator it1 = finalSort.begin()+1;
	
	std::vector<int>::iterator itTmp;
	std::vector<int>::iterator it1Tmp;
	
	int nb = 0;
	int tmp_start = start;
	while (tmp_start < end)
	{
		if (it1 != finalSort.end() && *it > *it1)
		{
			itTmp = finalSort.begin();
			it1Tmp = it1;
			int i = 0;
			while (*itTmp < *it1Tmp)
			{
				itTmp++;
				i++;
			}
			int tmp = *it1;
			finalSort.erase(finalSort.begin()+findVecIterator(finalSort, tmp, nb));
			finalSort.insert(finalSort.begin()+i, tmp);
		}
		it++, it1++;
		nb++;
		tmp_start++;
	}
	return (finalSort);
}

std::vector<int>		PmergeMe::sortVector(std::vector<int> vecSort, int start, int end) {

	std::vector<int> stackRight;
	std::vector<int> stackLeft;

	int size = end - start;
	int middle = start + size / 2;

	if (size > 50)
	{
		stackLeft = sortVector(vecSort, start, middle);
		stackRight = sortVector(vecSort, middle, end);

		std::vector<int>::iterator itStackLeft = stackLeft.begin();
		std::vector<int>::iterator iteStackLeft = stackLeft.end();

		std::vector<int>::iterator itStackRight = stackRight.begin();
		std::vector<int>::iterator iteStackRight = stackRight.end();
		
		std::vector<int> temp(stackRight.size() + stackLeft.size());
		
		std::merge (itStackLeft, iteStackLeft, itStackRight, iteStackRight, temp.begin());

		return (temp);
	}
	else
		return (insertVecSort(vecSort, start, end));
}

int 	PmergeMe::findDeqIterator(std::deque<int> stack, int nb, int start) {

	int i = start;
	std::deque<int>::iterator it = stack.begin()+start;
	
	while (it != stack.end())
	{
		if (*it == nb)
			return (i);
		it++;
		i++;
	}
	return (i);
}

int 					PmergeMe::checkSort(std::deque<int> finalSort, int length) {

	int i = 0;
	
	while (i < length - 1)
	{
		if (finalSort[i] < finalSort[i + 1])
			i++;
		else
			return (-1);
	}
	return (1);
}

std::deque<int> 		PmergeMe::insertDeqSort(std::deque<int> deqSort, int start, int end) {

	std::deque<int> finalSort(end - start);
	
	std::deque<int>::iterator it = deqSort.begin()+start;

	int j = 0;
	for (int i = start; i < end; i++)
	{
		finalSort[j] = *it;
		it++;
		j++;
	}

	it = finalSort.begin();
	std::deque<int>::iterator it1 = finalSort.begin()+1;
	
	std::deque<int>::iterator itTmp;
	
	while (it1 != finalSort.end())
	{
		if (it1 != finalSort.end() && *it > *it1)
		{
			itTmp = finalSort.begin();
			int i = 0;
			while (*itTmp < *it1 && itTmp != finalSort.end())
			{
				itTmp++;
				i++;
			}
			int tmp = *it1;
			finalSort.erase(it1);
			finalSort.insert(finalSort.begin()+i, tmp);
		}
		else
			it++, it1++;
	}
	return (finalSort);
}

std::deque<int>		PmergeMe::sortDeque(std::deque<int> deqSort, int start, int end) {

	std::deque<int> stackRight;
	std::deque<int> stackLeft;

	int size = end - start;
	int middle = start + size / 2;

	if (size > 50)
	{
		stackLeft = sortDeque(deqSort, start, middle);
		stackRight = sortDeque(deqSort, middle, end);

		std::deque<int>::iterator itStackLeft = stackLeft.begin();
		std::deque<int>::iterator iteStackLeft = stackLeft.end();

		std::deque<int>::iterator itStackRight = stackRight.begin();
		std::deque<int>::iterator iteStackRight = stackRight.end();
		
		std::deque<int> temp(stackRight.size() + stackLeft.size());
		
		std::merge (itStackLeft, iteStackLeft, itStackRight, iteStackRight, temp.begin());

		return (temp);
	}
	else
		return (insertDeqSort(deqSort, start, end));
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