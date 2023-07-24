/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:28:39 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 22:04:45 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type)
: _type(type)
{
	return ;
}

Weapon::~Weapon(void)
{
	return ;
}

std::string&	Weapon::getType(void) 
{
	return this->_type;
}

void	Weapon::setType(std::string weapon_type)
{
	this->_type = weapon_type;
}
