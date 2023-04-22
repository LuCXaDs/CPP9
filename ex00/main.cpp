/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:52:11 by luserbu           #+#    #+#             */
/*   Updated: 2023/04/22 17:52:50 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av) {

	if (ac == 3)
	{
		BitcoinExchange btc(av[1], av[2]);
		try
		{
			btc.fillFile();
		}
		catch(std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	else
		std::cerr << RED << "Error: Bad number of argument !" << WHITE << std::endl;
	return (1);
}