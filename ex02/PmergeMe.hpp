/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:47:23 by luserbu           #+#    #+#             */
/*   Updated: 2023/04/24 19:57:54 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <list>
# include <vector>
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

		void					printInfo(int *stack, int lengthSort, std::vector<int> vecSort);

		std::vector<int>		sortVector(std::vector<int> vecSort, int start, int end);
		std::list<int>			sortList(std::list<int> listSort, int *stack, int pointer, int length);

		std::vector<int> 		insert_sort(std::vector<int> vecSort, int start, int end);

	private:

		double generalTime;
		double vectorTime;
		double listTime;

};

#endif /* ******************************************************** PMERGEME_H */