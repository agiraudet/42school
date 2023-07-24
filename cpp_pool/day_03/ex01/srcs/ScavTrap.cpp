/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:24:22 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/20 15:00:24 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name)
: ClapTrap(name)
{
	this->_hitPoint = 100;
	this->_energyPoint = 50;
	this->_attackDamage = 20;
	std::cout << "A new [ScavTrap] unit has been made. Hello " << name << " !" << std::endl;
}

ScavTrap::ScavTrap(ScavTrap const & src)
: ClapTrap(src)
{
	*this = src;
	std::cout << "[SCAVTRAP] ";
	std::cout << "A clone of " << this->_name << " has been made !" << std::endl;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "[SCAVTRAP] ";
	std::cout << this->_name << " has been sent to the junkyard." << std::endl;
}

ScavTrap & ScavTrap::operator=(ScavTrap const & rhs)
{
	this->_name = rhs._name;
	this->_hitPoint = rhs._hitPoint;
	this->_energyPoint = rhs._energyPoint;
	this->_attackDamage = rhs._attackDamage;
	std::cout << "[SCAVTRAP] ";
	std::cout << rhs.getName() << " got copied !" << std::endl;
	return *this;
}

void	ScavTrap::attack(const std::string & target)
{
	if (this->_hitPoint <= 0)
	{
		std::cout << "[SCAVTRAP] ";
		std::cout << this->_name << " cant attack. He's dead you see." << std::endl;
		return ;
	}
	if (this->_energyPoint <= 0)
	{
		std::cout << "[SCAVTRAP] ";
		std::cout << this->_name << " is to low on energy..." << std::endl;;
		return ;
	}
		std::cout << "[SCAVTRAP] ";
	std::cout << this->_name << " attacks " << target << " for "
		<< this->_attackDamage << " points of damage !" << std::endl;
	this->_energyPoint--;
}

void	ScavTrap::guardGate(void) const
{
	if (this->_hitPoint <= 0)
	{
		std::cout << "[SCAVTRAP] ";
		std::cout << this->_name << " cant guard anything dead." << std::endl;
		return ;
	}
	std::cout << "[SCAVTRAP] ";
	std::cout << this->_name << " enter GuardGate stance." << std::endl;
}
