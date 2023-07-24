/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:40:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:42:37 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void)
: Animal()
{
	std::cout << "An Dog has been created" << std::endl;
	this->setType("Dog");
	this->_brain = new Brain;
}

Dog::Dog(Dog const & src)
: Animal()
{
	std::cout << "An Dog has been created by copy" << std::endl;
	this->_brain = new Brain;
	*this = src;
}

Dog::~Dog(void)
{
	delete this->_brain;
	std::cout << "An Dog has been destroyed" << std::endl;
}

Dog & Dog::operator=(Dog const & rhs)
{
	this->_type = rhs._type;
	*(this->_brain) = *(rhs._brain);
	return *this;
}

void	Dog::makeSound(void) const
{
	std::cout << "*OUAF OUAF*" << std::endl;
}

std::string	Dog::getIdea(int n) const
{
	return this->_brain->getIdea(n);
}

void	Dog::setIdea(int n, std::string idea)
{
	this->_brain->setIdea(n, idea);
}
