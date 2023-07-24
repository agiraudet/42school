/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:40:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:39:37 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void)
: _type("none")
{
	std::cout << "An animal has been created" << std::endl;
}

Animal::Animal(Animal const & src)
{
	*this = src;
	std::cout << "An animal has been created by copy" << std::endl;
}

Animal::~Animal(void)
{
	std::cout << "An animal has been destroyed" << std::endl;
}

Animal & Animal::operator=(Animal const & rhs)
{
	this->_type = rhs._type;
	return *this;
}

void	Animal::setType(std::string type)
{
	this->_type = type;
}

std::string	Animal::getType(void) const
{
	return this->_type;
}

void	Animal::makeSound(void) const
{
	std::cout << "*Undefined noise*" << std::endl;
}
