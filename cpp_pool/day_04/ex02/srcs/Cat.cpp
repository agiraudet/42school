/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:40:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:56:42 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void)
: AAnimal()
{
	std::cout << "An Cat has been created" << std::endl;
	this->_type = "Cat";
	this->_brain = new Brain;
}

Cat::Cat(Cat const & src)
: AAnimal()
{
	std::cout << "An Cat has been created by copy" << std::endl;
	this->_brain = new Brain;
	*this = src;
}

Cat::~Cat(void)
{
	delete this->_brain;
	std::cout << "An Cat has been destroyed" << std::endl;
}

Cat & Cat::operator=(Cat const & rhs)
{
	this->_type = rhs._type;
	for (int i = 0; i < 100; i++)
		this->_brain->setIdea(i, rhs._brain->getIdea(i));
	return *this;
}

void	Cat::makeSound(void) const
{
	std::cout << "*MIAOU*" << std::endl;
}

std::string	Cat::getIdea(int n) const
{
	return this->_brain->getIdea(n);
}

void	Cat::setIdea(int n, std::string idea)
{
	this->_brain->setIdea(n, idea);
}
