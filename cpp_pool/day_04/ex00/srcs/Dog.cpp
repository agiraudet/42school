/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:40:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:35:39 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void)
: Animal()
{
	std::cout << "An Dog has been created" << std::endl;
	this->setType("Dog");
}

Dog::Dog(Dog const & src)
: Animal()
{
	*this = src;
	std::cout << "An Dog has been created by copy" << std::endl;
}

Dog::~Dog(void)
{
	std::cout << "An Dog has been destroyed" << std::endl;
}

Dog & Dog::operator=(Dog const & rhs)
{
	this->_type = rhs._type;
	return *this;
}

void	Dog::makeSound(void) const
{
	std::cout << "*OUAF OUAF*" << std::endl;
}
