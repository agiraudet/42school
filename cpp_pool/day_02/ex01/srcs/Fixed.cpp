/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 16:57:44 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/19 12:13:45 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::_fNbBits = 8;

Fixed::Fixed(void)
: _n(0)
{
	std::cout << "Default constructor called" << std::endl;
	return ;
}

Fixed::Fixed(Fixed const & src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

Fixed::Fixed(int const n)
{
	std::cout << "Int constructor called" << std::endl;
	this->_n = n << this->_fNbBits;
}

Fixed::Fixed(float const n)
{
	std::cout << "Float constructor called" << std::endl;
	this->_n = (n * float(1 << this->_fNbBits) + (n >= 0 ? 0.5 : -0.5));
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
	return ;
}

Fixed &	Fixed::operator=(Fixed const & rhs)
{
	std::cout << "Copy assignement operator called" << std::endl;
	this->setRawBits(rhs.getRawBits());
	return *this;
}

std::ostream &	operator<<(std::ostream & o, Fixed const & rhs)
{
	o << rhs.toFloat();
	return o;
}

int	Fixed::getRawBits(void) const
{
	return this->_n;
}

void	Fixed::setRawBits(int const raw)
{
	this->_n = raw;
}

int	Fixed::toInt(void) const
{
	return this->_n >> this->_fNbBits;
}

float	Fixed::toFloat(void) const
{
	return float(this->_n) / float(1 << this->_fNbBits);
}
