/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 16:57:44 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/21 08:58:26 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::_fNbBits = 8;

Fixed::Fixed(void)
: _n(0)
{
	return ;
}

Fixed::Fixed(Fixed const & src)
{
	*this = src;
}

Fixed::Fixed(int const n)
{
	this->_n = n << this->_fNbBits;
}

Fixed::Fixed(float const n)
{
	this->_n = (n * float(1 << this->_fNbBits) + (n >= 0 ? 0.5 : -0.5));
}

Fixed::~Fixed(void)
{
	return ;
}

Fixed &	Fixed::operator=(Fixed const & rhs)
{
	this->setRawBits(rhs.getRawBits());
	return *this;
}

bool	Fixed::operator>(Fixed const & rhs) const
{
	return this->_n > rhs.getRawBits();
}

bool	Fixed::operator>=(Fixed const & rhs) const
{
	return this->_n >= rhs.getRawBits();
}

bool	Fixed::operator<(Fixed const & rhs) const
{
	return this->_n < rhs.getRawBits();
}

bool	Fixed::operator<=(Fixed const & rhs) const
{
	return this->_n <= rhs.getRawBits();
}

bool	Fixed::operator==(Fixed const & rhs) const
{
	return this->_n == rhs.getRawBits();
}

bool	Fixed::operator!=(Fixed const & rhs) const
{
	return this->_n != rhs.getRawBits();
}

Fixed	Fixed::operator+(Fixed const & rhs) const
{
	Fixed	x;

	x.setRawBits(this->_n + rhs.getRawBits());
	return x;
}

Fixed	Fixed::operator-(Fixed const & rhs) const
{
	Fixed	x;
	
	x.setRawBits(this->_n - rhs.getRawBits());
	return x;
}

Fixed	Fixed::operator*(Fixed const & rhs) const
{
	Fixed	x;

	x.setRawBits((long(this->_n) * long(rhs.getRawBits())) >> long(this->_fNbBits));
	return x;
}

Fixed	Fixed::operator/(Fixed const & rhs) const
{
	Fixed	x;

	x.setRawBits((long(this->_n) << long(this->_fNbBits)) / rhs.getRawBits());
	return x;
}

Fixed	Fixed::operator++(int)
{
	Fixed	x(*this);

	this->_n++;
	return x;
}

Fixed 	Fixed::operator++(void)
{
	Fixed	x;

	this->_n++;
	x = *this;
	return x;
}

Fixed	Fixed::operator--(int)
{
	Fixed	x(*this);

	this->_n--;
	return x;
}

Fixed 	Fixed::operator--(void)
{
	Fixed	x;

	this->_n--;
	x = *this;
	return x;
}

Fixed const & Fixed::min(Fixed const & a, Fixed const & b)
{
	return a <= b ? a : b;
}

Fixed & Fixed::min(Fixed & a, Fixed & b)
{
	return a <= b ? a : b;
}

Fixed const & Fixed::max(Fixed const & a, Fixed const & b)
{
	return a >= b ? a : b;
}

Fixed & Fixed::max(Fixed & a, Fixed & b)
{
	return a >= b ? a : b;
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
