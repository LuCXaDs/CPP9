/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 20:12:28 by luserbu           #+#    #+#             */
/*   Updated: 2023/04/21 18:57:06 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <cstdlib>
# include <map>
#include <time.h>
# include <limits.h>

#define TRUE 1
#define FALSE 0

#define RED "\033[1;91m"
#define YELLOW "\033[1;93m⚠️ ​"
#define WHITE "\033[0m"

class BitcoinExchange
{

	public:

		BitcoinExchange();
		BitcoinExchange(char* name, char *data);
		BitcoinExchange( BitcoinExchange const & src );
		~BitcoinExchange();

		BitcoinExchange &		operator=( BitcoinExchange const & rhs );

		class Expt : public std::exception
        {
            public:
                virtual const char* what() const throw()
                { return ("EXCEPTION"); }
        };

		void		findValue();
		
		void		fillFile();
		int			checkError(std::string verif, int i);

		void		getData();
		int			checkErrorData(std::string verif, int i);

		int			printError(int error, int print);
		
	protected:

		std::string value;
		std::string year;
		std::string month;
		std::string day;
		std::string YMD; // Year-Month-Day

	private:

		std::ifstream _infile;
		std::ifstream _data;
		std::map<int, double> _mymap;
		std::map<int, double> _csv;
};

#endif /* ************************************************* BITCOINEXCHANGE_H */