/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:40:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:52:00 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal(void)
{
	std::cout << "An AAnimal has been created" << std::endl;
}

AAnimal::AAnimal(AAnimal const & src)
{
	*this = src;
	std::cout << "An AAnimal has been created by copy" << std::endl;
}

AAnimal::~AAnimal(void)
{
	std::cout << "An AAnimal has been destroyed" << std::endl;
}

AAnimal & AAnimal::operator=(AAnimal const & rhs)
{
	this->_type = rhs._type;
	return *this;
}

void	AAnimal::setType(std::string type)
{
	this->_type = type;
}

std::string	AAnimal::getType(void) const
{
	return this->_type;
}
