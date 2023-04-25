/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:47:23 by luserbu           #+#    #+#             */
/*   Updated: 2023/04/25 20:51:41 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <list>
# include <vector>
# include <deque>
# include <cstring>
# include <cstdlib>
# include <algorithm>
# include <limits.h>
# include <sys/time.h>

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

		void					mergeSort(char **sort);
		int						lengthDoubleTab(char **tab);
		void					easyFindError(char **tab);
		double					start_time(void);
		double					time_now(void);

		void					printInfo(int *stack, int lengthSort, std::deque<int> vecSort);

		// std::list<int>			sortList(std::list<int> listSort, int start, int end);
		// std::list<int> 			insertListSort(std::list<int> listSort, int start, int end);
		// int 					findListIterator(std::list<int> stack, int nb, int start);


		std::vector<int>		sortVector(std::vector<int> vecSort, int start, int end);
		std::vector<int> 		insertVecSort(std::vector<int> vecSort, int start, int end);
		int 					findVecIterator(std::vector<int> stack, int nb, int start);

		std::deque<int>			sortDeque(std::deque<int> deqSort, int start, int end);
		std::deque<int> 		insertDeqSort(std::deque<int> deqSort, int start, int end);
		int 					findDeqIterator(std::deque<int> stack, int nb, int start);

		int 					checkSort(std::deque<int> finalSort, int length);
		
	private:

		double generalTime;
		double parsingTime;
		double vectorTime;
		double dequeTime;

};

#endif /* ******************************************************** PMERGEME_H */