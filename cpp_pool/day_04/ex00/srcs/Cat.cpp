/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:40:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:35:00 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void)
: Animal()
{
	std::cout << "An Cat has been created" << std::endl;
	this->_type = "Cat";
}

Cat::Cat(Cat const & src)
: Animal()
{
	*this =src;
	std::cout << "An Cat has been created by copy" << std::endl;
}

Cat::~Cat(void)
{
	std::cout << "An Cat has been destroyed" << std::endl;
}

Cat & Cat::operator=(Cat const & rhs)
{
	this->_type = rhs._type;
	return *this;
}

void	Cat::makeSound(void) const
{
	std::cout << "*MIAOU*" << std::endl;
}
