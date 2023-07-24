/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 16:43:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/19 12:06:37 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class	Fixed
{
	public:

		Fixed(void);
		Fixed(Fixed const & src );
		Fixed(int const n);
		Fixed(float const n);
		~Fixed(void);

		Fixed &	operator=(Fixed const & rhs);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;
		
	private:

		int	_n;
		int const static _fNbBits;

};

std::ostream &	operator<<(std::ostream & o, Fixed const & rhs);

#endif
