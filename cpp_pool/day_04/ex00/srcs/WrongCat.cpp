/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:40:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:36:47 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(void)
: WrongAnimal()
{
	std::cout << "An WrongCat has been created" << std::endl;
	this->_type = "WrongCat";
}

WrongCat::WrongCat(WrongCat const & src)
: WrongAnimal()
{
	*this =src;
	std::cout << "An WrongCat has been created by copy" << std::endl;
}

WrongCat::~WrongCat(void)
{
	std::cout << "An WrongCat has been destroyed" << std::endl;
}

WrongCat & WrongCat::operator=(WrongCat const & rhs)
{
	this->_type = rhs._type;
	return *this;
}

void	WrongCat::makeSound(void) const
{
	std::cout << "*MIAOU but wrong*" << std::endl;
}
