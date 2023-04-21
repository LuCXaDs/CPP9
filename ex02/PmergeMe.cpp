#include "PmergeMe.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe( const PmergeMe & src )
{
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
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, PmergeMe const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void		PmergeMe::mergeSort(char **sort) {

	int lengthSort = lengthDoubleTab(sort);
	std::vector<int> vecSort;

	for (int i = 0; i < lengthSort; i++)
	{
		vecSort.push_back(atoi(sort[i]));
	}

	std::merge (vecSort.begin());


}

int			PmergeMe::lengthDoubleTab(char **tab) {

	int i = 0;

	while (tab[i])
		i++;
	return (i);
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */