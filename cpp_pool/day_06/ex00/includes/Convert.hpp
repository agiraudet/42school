/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:22:19 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/26 12:43:00 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
# define CONVERT_HPP

# include <iostream>
# include <iomanip>
# include <sstream>
# include <string>
# include <limits>

class	Convert
{
	public:

		Convert(std::string arg);
		Convert(Convert const & src);
		~Convert(void);
		
		Convert & operator=(Convert const & rhs);

		void	print(std::ostream & o) const;

	private:

		std::string	_str;
		long double	_n;
		bool		_nan;
		int			_inf;
		
		void	_printChar(std::ostream & o) const;
		void	_printInt(std::ostream & o) const;
		void	_printFloat(std::ostream & o) const;
		void	_printDouble(std::ostream & o) const;
};

std::ostream &	operator<<(std::ostream & o, Convert const & rhs);

#endif
