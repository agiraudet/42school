/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:43:02 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/20 12:55:00 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

int main( void )
{
	{
		Fixed a;

		std::cout << "incrementation:" << std::endl;
		std::cout << "  a is " << a << std::endl;
		std::cout << "++a is " << ++a << std::endl;
		std::cout << "  a is " << a << std::endl;
		std::cout << "a++ is " << a++ << std::endl;
		std::cout << "  a is " << a << std::endl;
		std::cout << "decrementation:" << std::endl;
		std::cout << "  a is " << a << std::endl;
		std::cout << "--a is " << --a << std::endl;
		std::cout << "  a is " << a << std::endl;
		std::cout << "a-- is " << a-- << std::endl;
		std::cout << "  a is " << a << std::endl << std::endl;
	}
	{
		Fixed		a(1.3f);
		Fixed		b(3.7f);
		Fixed		c(1.3f);
		Fixed const	x(2.5f);
		Fixed const y(3.4f);
		Fixed const z(3.4f);

		std::cout << "min/max:" << std::endl;
		std::cout << "a is " << a << std::endl;
		std::cout << "b is " << b << std::endl;
		std::cout << "c is " << c << std::endl;
		std::cout << "min(a, b) is " << Fixed::min(a, b) << std::endl;
		std::cout << "max(a, b) is " << Fixed::max(a, b) << std::endl;
		std::cout << "max(a, c) is " << Fixed::max(a, c) << std::endl;
		std::cout << "x (const) is " << x << std::endl;
		std::cout << "y (const) is " << y << std::endl;
		std::cout << "z (const) is " << z << std::endl;
		std::cout << "min(x, y) is " << Fixed::min(x, y) << std::endl;
		std::cout << "max(x, y) is " << Fixed::max(x, y) << std::endl;
		std::cout << "max(x, z) is " << Fixed::max(x, z) << std::endl << std::endl;
	}
	{
		Fixed	a(5.6f);
		Fixed	b(2.7f);

		std::cout << "calcul and compare:" << std::endl;
		std::cout << "a as float is " << a << std::endl;
		std::cout << "b as float is " << b << std::endl << std::endl;
		std::cout << "a + b is " << a + b << std::endl;
		std::cout << "a - b is " << a - b << std::endl;
		std::cout << "a * b is " << a * b << std::endl;
		std::cout << "a / b is " << a / b << std::endl;
		std::cout << "a > b is " << (a > b) << std::endl;
		std::cout << "a >= b is " << (a >= b) << std::endl;
		std::cout << "a >= a is " << (a >= a) << std::endl;
		std::cout << "a < b is " << (a < b) << std::endl;
		std::cout << "b <= b is " << (b <= b) << std::endl;
		std::cout << "b == b is " << (b == b) << std::endl;
		std::cout << "b != b is " << (b != b) << std::endl;
		std::cout << "a == b is " << (a == b) << std::endl;
		std::cout << "a != b is " << (a != b) << std::endl << std::endl;
	}
	{
		Fixed a(19519.1f);
		Fixed b(8.19922f);

		std::cout << "check overflow:" << std::endl;
		std::cout << "a as float is " << a << std::endl;
		std::cout << "b as float is " << b << std::endl;
		std::cout << "a * b is " << a * b << std::endl;
		std::cout << "(should be : " << float(19519.1f * 8.19922f) << " )" << std::endl << std::endl;
	}
	{
		Fixed a;
		Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

		std::cout << "Subject Demo: " << std::endl;
		std::cout << a << std::endl;
		std::cout << ++a << std::endl;
		std::cout << a << std::endl;
		std::cout << a++ << std::endl;
		std::cout << a << std::endl;

		std::cout << b << std::endl;

		std::cout << Fixed::max( a, b ) << std::endl;
	}

	return 0;
}
