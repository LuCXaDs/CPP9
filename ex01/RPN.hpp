/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:30:36 by luserbu           #+#    #+#             */
/*   Updated: 2023/04/21 18:16:23 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <cstring>
# include <cstdlib>

class RPN
{

	public:

		RPN();
		RPN( RPN const & src );
		~RPN();

		RPN &		operator=( RPN const & rhs );

		class Expt : public std::exception
        {
            public:
                virtual const char* what() const throw()
                { return ("\033[1;91mError\033[0m"); }
        };

		void		polishNotation(char* notation);
		void			easyCheck(char *notation);
		int			arithmetic(int first, int second, char c);

	private:

};

#endif /* ************************************************************* RPN_H */