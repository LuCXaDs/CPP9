/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 20:12:32 by luserbu           #+#    #+#             */
/*   Updated: 2023/04/20 22:12:53 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BitcoinExchange::BitcoinExchange() {

}

BitcoinExchange::BitcoinExchange(char* name, char *data) {

	_infile.open(name);
	_data.open(data);
}

BitcoinExchange::BitcoinExchange( const BitcoinExchange & src ) {
	
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

BitcoinExchange::~BitcoinExchange() {

	_infile.close();
	_data.close();
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

BitcoinExchange &				BitcoinExchange::operator=( BitcoinExchange const & rhs )
{
	(void)rhs;
	if ( this != &rhs )
	{
		// this->_infile = rhs._infile;
		// this->_data = rhs._data;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void		BitcoinExchange::findValue() {
	
	std::map<int,double>::iterator it = _mymap.begin();
	std::map<int,double>::iterator itlow = _csv.lower_bound(it->first);
	
	if (itlow->first != it->first)
		if (itlow != _csv.begin())
			itlow--;
	std::cout << year << "-" << month << "-" << day << " => " << value << " = " << itlow->second * it->second << std::endl;

	_mymap.erase (it);
}

void		BitcoinExchange::fillFile() {

	int i = 0;
	int pos = 0;
	int error = 0;

	char *pEnd;
	
	std::string tmp;

	getData();
	if (_infile.is_open() && !_infile.fail())
	{
		while (getline(_infile, tmp))
		{
			error = checkError(tmp, i);
			if (error == 1)
			{
				if (i == 0)
					std::cout << "date | value" << std::endl;
				if (i != 0)
				{
					year = tmp.substr(0, 4);
					month = tmp.substr(5, 2);
					day = tmp.substr(8, 2);
					YMD = year + month + day;
					pos = tmp.find(" | ");
					value = tmp.substr(pos + 3);
					_mymap.insert ( std::pair<int, double>((atoi(YMD.c_str())), strtod(value.c_str(), &pEnd)) );
					findValue();
				}
			}
			else
				printError(error, TRUE);
			i++;
		}
	}
	else
		throw(Expt());
}

int		BitcoinExchange::checkError(std::string verif, int i) {

	if (i == 0)
	{
		if (verif != "date | value")
			return (printError(2, FALSE));
		else
			return (1);
	}
	if (verif.length() < 13)
		return (printError(3, FALSE));
	if (verif[4] != '-' && verif[7] != '-')
		return (printError(4, FALSE));
	if (verif[10] != ' ' && verif[11] != '|' && verif[12] != ' ')
		return (printError(4, FALSE));
	year = verif.substr(0, 4);
	month = verif.substr(5, 2);
	day = verif.substr(8, 2);
	if (!atoi(year.c_str()) || !atoi(month.c_str()) || !atoi(day.c_str()))
		return (printError(5, FALSE));
	if (atoi(year.c_str()) < 0 && atoi(month.c_str()) < 0 && atoi(day.c_str()) < 0)
		return (printError(5, FALSE));
	if (atoi(month.c_str()) > 12 || atoi(month.c_str()) == 0)
		return (printError(6, FALSE));
	if (atoi(day.c_str()) > 31 || atoi(day.c_str()) == 0)
		return (printError(7, FALSE));
	if (atoi(day.c_str()) > 30 && atoi(month.c_str()) % 2 == 0 && atoi(month.c_str()) < 7)
		return (printError(9, FALSE));
	if (atoi(day.c_str()) > 30 && atoi(month.c_str()) % 2 != 0 && atoi(month.c_str()) > 7)
		return (printError(9, FALSE));
	if (atoi(day.c_str()) > 29 && atoi(month.c_str()) == 2)
		return (printError(10, FALSE));
	if (atoi(day.c_str()) == 29 && atoi(month.c_str()) == 2)
	{
		if ((atoi(year.c_str()) % 4 == 0 && atoi(year.c_str()) % 100 != 0) || atoi(year.c_str()) % 400 == 0);
		else
			return (printError(11, FALSE));
	}
	int pos = verif.find(" | ");
	char* pEnd;
	value = verif.substr(pos + 3);
	double val = strtod(value.c_str(), &pEnd);
	if (val > INT_MAX  || val < 0 || *pEnd)
		return (printError(8, FALSE));
	if (val > 1000)
		return (printError(12, FALSE));
	return (1);
}

void		BitcoinExchange::getData() {

	int i = 0;
	int pos = 0;

	char *pEnd;
	
	std::string tmp;

	if (_data.is_open() && !_data.fail())
	{
		while (getline(_data, tmp))
		{
			if (checkErrorData(tmp, i))
			{
				if (i != 0)
				{
					year = tmp.substr(0, 4);
					month = tmp.substr(5, 2);
					day = tmp.substr(8, 2);
					YMD = year + month + day;
					pos = tmp.find(",");
					value = tmp.substr(pos + 1);
					_csv.insert ( std::pair<int, double>((atoi(YMD.c_str())), strtod(value.c_str(), &pEnd)) );
				}	
			}
			i++;
		}
	}
	else
		throw(Expt());
}

int		BitcoinExchange::checkErrorData(std::string verif, int i) {

	if (i == 0)
	{
		if (verif != "date,exchange_rate")
			throw(Expt());
		else
			return (1);
	}
	if (verif.length() < 11)
		throw(Expt());
	if (verif[4] != '-' && verif[7] != '-')
		return (printError(4, FALSE));
	if (verif[10] != ',')
		throw(Expt());
	year = verif.substr(0, 4);
	month = verif.substr(5, 2);
	day = verif.substr(8, 2);
	if (!atoi(year.c_str()) && !atoi(month.c_str()) && !atoi(day.c_str()))
		throw(Expt());
	if (atoi(year.c_str()) < 2009 || atoi(month.c_str()) < 1 || atoi(day.c_str()) < 1)
		throw(Expt());
	if (atoi(year.c_str()) == 2009 && atoi(month.c_str()) == 1 && atoi(day.c_str()) < 3)
		throw(Expt());
	if (atoi(month.c_str()) > 12 || atoi(month.c_str()) == 0)
		throw(Expt());
	if (atoi(day.c_str()) > 31 || atoi(day.c_str()) == 0)
		throw(Expt());
	if (atoi(day.c_str()) > 30 && atoi(month.c_str()) % 2 == 0 && atoi(month.c_str()) < 7)
		throw(Expt());
	if (atoi(day.c_str()) > 30 && atoi(month.c_str()) % 2 != 0 && atoi(month.c_str()) > 7)
		throw(Expt());
	if (atoi(day.c_str()) > 29 && atoi(month.c_str()) == 2)
		throw(Expt());
	if (atoi(day.c_str()) == 29 && atoi(month.c_str()) == 2)
	{
		if ((atoi(year.c_str()) % 4 == 0 && atoi(year.c_str()) % 100 != 0) || atoi(year.c_str()) % 400 == 0);
		else
			throw(Expt());
	}
	int pos = verif.find(",");
	char* pEnd;
	value = verif.substr(pos + 1);
	double val = strtod(value.c_str(), &pEnd);
	if (val > INT_MAX  || val < 0 || *pEnd)
		throw(Expt());
	if (val > 1000)
		return (printError(12, FALSE));
	return (1);
}

int		BitcoinExchange::printError(int error, int print) {
	
	if (print == FALSE)
		return (error);
	if (error == 2)
		std::cerr << YELLOW"Error: " << WHITE << RED"First argument are not \"date | value\"" << WHITE << std::endl;
	if (error == 3)
		std::cerr << YELLOW"Error: " << WHITE << RED"Few arguements" << WHITE << std::endl;
	if (error == 4)
		std::cerr << YELLOW"Error: " << WHITE << RED"Elements are not placed in the right order" << WHITE << std::endl;
	if (error == 5)
		std::cerr << YELLOW"Error: " << WHITE << RED"Year/Month/Day must be positif integer" << WHITE << std::endl;
	if (error == 6)
		std::cerr << YELLOW"Error: " << WHITE << RED"There are max 12 months or min 01 month" << WHITE << std::endl;
	if (error == 7)
		std::cerr << YELLOW"Error: " << WHITE << RED"There are max 31 days or min 01 day" << WHITE << std::endl;
	if (error == 8)
		std::cerr << YELLOW"Error: " << WHITE << RED"Value can't be superior than INT_MAX or can't be inferior" << WHITE << std::endl;
	if (error == 9)
		std::cerr << YELLOW"Error: " << WHITE << RED"This is not month can accept 31 days" << WHITE << std::endl;
	if (error == 10)
		std::cerr << YELLOW"Error: " << WHITE << RED"February can't accept more day than 29" << WHITE << std::endl;
	if (error == 11)
		std::cerr << YELLOW"Error: " << WHITE << RED"This is not leap year" << WHITE << std::endl;
	if (error == 12)
		std::cerr << YELLOW"Error: " << WHITE << RED"Value are superior than 1000" << WHITE << std::endl;
	return (error);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */