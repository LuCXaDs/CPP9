#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <list>
# include <vector>
# include <cstring>
# include <cstdlib>
#include <algorithm>

class PmergeMe
{

	public:

		PmergeMe();
		PmergeMe( PmergeMe const & src );
		~PmergeMe();

		PmergeMe &		operator=( PmergeMe const & rhs );

		class Expt : public std::exception
        {
            public:
                virtual const char* what() const throw()
                { return ("\033[1;91mError\033[0m"); }
        };

		void		mergeSort(char **sort);
		int			lengthDoubleTab(char **tab);

	private:

};

std::ostream &			operator<<( std::ostream & o, PmergeMe const & i );

#endif /* ******************************************************** PMERGEME_H */