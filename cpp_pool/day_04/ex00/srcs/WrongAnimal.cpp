/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:40:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:39:59 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void)
: _type("none")
{
	std::cout << "An WrongAnimal has been created" << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const & src)
{
	*this = src;
	std::cout << "An WrongAnimal has been created by copy" << std::endl;
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << "An WrongAnimal has been destroyed" << std::endl;
}

WrongAnimal & WrongAnimal::operator=(WrongAnimal const & rhs)
{
	this->_type = rhs._type;
	return *this;
}

void	WrongAnimal::setType(std::string type)
{
	this->_type = type;
}

std::string	WrongAnimal::getType(void) const
{
	return this->_type;
}

void	WrongAnimal::makeSound(void) const
{
	std::cout << "*Undefined, somehow wrong, noise*" << std::endl;
}
