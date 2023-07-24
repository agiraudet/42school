/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:24:44 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/26 13:04:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

Convert::Convert(std::string arg)
: _str(arg), _nan(false), _inf(0)
{	
	std::stringstream	ss(arg);
	ss >> this->_n;
	if (arg.compare("nan") == 0 || arg.compare("nanf") == 0)
		this->_nan = true;
	if (arg.compare("+inf") == 0 || arg.compare("+inff") == 0)
		this->_inf = 1;
	if (arg.compare("-inf") == 0 || arg.compare("-inff") == 0)
		this->_inf = -1;
}

Convert::Convert(Convert const & src)
{
	*this = src;
}

Convert::~Convert(void)
{
}

Convert & Convert::operator=(Convert const & rhs)
{
	this->_str = rhs._str;
	this->_n = rhs._n;
	this->_nan = rhs._nan;
	this->_inf = rhs._inf;
	return *this;
}

void	Convert::_printChar(std::ostream & o) const
{
	char	c = static_cast<char>(this->_n);

	o << "Char: ";
	if (this->_nan || this->_inf != 0 || this->_n < std::numeric_limits<char>::min() || this->_n > std::numeric_limits<char>::max())
		o << "impossible";
	else if (this->_n <= 8 || this->_n >= 127)
		o << "Non displayble";
	else
		o << "'" << c << "'";
}

void	Convert::_printInt(std::ostream & o) const
{
	int	i = static_cast<int>(this->_n);

	o << "Int: ";
	if (this->_nan || this->_inf != 0 || this->_n < std::numeric_limits<int>::min() || this->_n > std::numeric_limits<int>::max())
		o << "impossible";
	else
		o << i;
}

void	Convert::_printFloat(std::ostream & o) const
{
	float	f = static_cast<float>(this->_n);

	o << "Float: ";
	if (this->_nan)
		o << "nanf";
	else if (this->_inf != 0)
		o << (this->_inf < 0 ? '-' : '+') << "inff";
	else if (this->_n < -std::numeric_limits<float>::max()|| this->_n > std::numeric_limits<float>::max())
		o << "Impossible";
	else
		o << std::setprecision(1) << std::fixed << f << "f";
}

void	Convert::_printDouble(std::ostream & o) const
{
	double	d = static_cast<float>(this->_n);

	o << "Double: ";
	if (this->_nan)
		o << "nan";
	else if (this->_inf != 0)
		o << (this->_inf < 0 ? '-' : '+') << "inf";
	else if (this->_n < -std::numeric_limits<double>::max()|| this->_n > std::numeric_limits<double>::max())
		o << "Impossible";
	else
		o << std::setprecision(1) << std::fixed << d;
}

void	Convert::print(std::ostream & o) const
{
	this->_printChar(o);
	o << std::endl;
	this->_printInt(o);
	o << std::endl;
	this->_printFloat(o);
	o << std::endl;
	this->_printDouble(o);
}

std::ostream &	operator<<(std::ostream & o, Convert const & rhs)
{
	rhs.print(o);
	return o;
}
