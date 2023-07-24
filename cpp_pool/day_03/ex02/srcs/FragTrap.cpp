/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:24:22 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/20 15:01:05 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name)
: ClapTrap(name)
{
	this->_hitPoint = 100;
	this->_energyPoint = 100;
	this->_attackDamage = 30;
	std::cout << "A new [FragTrap] unit has been made. Hello " << name << " !" << std::endl;
}

FragTrap::FragTrap(FragTrap const & src)
: ClapTrap(src)
{
	*this = src;
	std::cout << "[FragTrap] ";
	std::cout << "A clone of " << this->_name << " has been made !" << std::endl;
}

FragTrap::~FragTrap(void)
{
	std::cout << "[FragTrap] ";
	std::cout << this->_name << " has been sent to the junkyard." << std::endl;
}

FragTrap & FragTrap::operator=(FragTrap const & rhs)
{
	this->_name = rhs._name;
	this->_hitPoint = rhs._hitPoint;
	this->_energyPoint = rhs._energyPoint;
	this->_attackDamage = rhs._attackDamage;
	std::cout << "[FragTrap] ";
	std::cout << rhs.getName() << " got copied !" << std::endl;
	return *this;
}

void	FragTrap::attack(const std::string & target)
{
	if (this->_hitPoint <= 0)
	{
		std::cout << "[FragTrap] ";
		std::cout << this->_name << " cant attack. He's dead you see." << std::endl;
		return ;
	}
	if (this->_energyPoint <= 0)
	{
		std::cout << "[FragTrap] ";
		std::cout << this->_name << " is to low on energy..." << std::endl;;
		return ;
	}
		std::cout << "[FragTrap] ";
	std::cout << this->_name << " attacks " << target << " for "
		<< this->_attackDamage << " points of damage !" << std::endl;
	this->_energyPoint--;
}

void	FragTrap::highFivesGuys(void) const
{
	if (this->_hitPoint <= 0)
	{
		std::cout << "[FragTrap] ";
		std::cout << this->_name << " cant highfive from the grave." << std::endl;
		return ;
	}
	std::cout << "[FragTrap] ";
	std::cout << this->_name << " says \"Can I get a high fives guys ??\"" << std::endl;
}
