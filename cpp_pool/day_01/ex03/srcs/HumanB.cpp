/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:34:26 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 22:22:06 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string name)
: _name(name), _tool(NULL)
{
	return ;
}

HumanB::~HumanB(void)
{
	return ;
}

void	HumanB::attack(void) const
{
	if (!this->_tool)
		std::cout << this->_name << " just punch with his bare hands" << std::endl;
	else
	{
		std::cout << this->_name << " attacks with their ";
		std::cout << this->_tool->getType() << std::endl;
	}
}

void	HumanB::setWeapon(Weapon& tool)
{
	this->_tool = &tool;
}
