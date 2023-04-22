/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:52:11 by luserbu           #+#    #+#             */
/*   Updated: 2023/04/22 16:51:58 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av) {

	if (ac > 1)
	{
		try
		{
			PmergeMe pmerge;

			pmerge.mergeSort(av);

		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}
	else
		std::cout << "Error: Bad number of argument !" <<  std::endl;
	return (1);
}