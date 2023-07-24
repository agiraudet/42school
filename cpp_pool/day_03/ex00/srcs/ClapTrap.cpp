/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:36:11 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/19 16:53:24 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name)
: _hitPoint(10), _energyPoint(10), _attackDamage(0)
{
	this->_name = name;
	std::cout << "A new ClapTrap unit has been made. Hello " << name << " !" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const & src)
{
	*this = src;
	std::cout << "A clone of " << this->_name << " has been made !" << std::endl;
}

ClapTrap::~ClapTrap(void)
{
	std::cout << this->_name << " has been sent to the junkyard." << std::endl;
}

ClapTrap & ClapTrap::operator=(ClapTrap const & rhs)
{
	this->_name = rhs._name;
	this->_hitPoint = rhs._hitPoint;
	this->_energyPoint = rhs._energyPoint;
	this->_attackDamage = rhs._attackDamage;
	std::cout << rhs.getName() << " got copied !" << std::endl;
	return *this;
}

std::string	ClapTrap::getName(void) const
{
	return this->_name;
}

void	ClapTrap::attack(const std::string & target)
{
	if (this->_hitPoint <= 0)
	{
		std::cout << this->_name << " cant attack. He's dead you see." << std::endl;
		return ;
	}
	if (this->_energyPoint <= 0)
	{
		std::cout << this->_name << " is to low on energy..." << std::endl;;
		return ;
	}
	std::cout << this->_name << " attacks " << target << " for "
		<< this->_attackDamage << " points of damage !" << std::endl;
	this->_energyPoint--;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << this->_name << " take a hit. ";
	if (this->_hitPoint <= 0)
		std::cout << this->_name << " is already dead ! ";
	else if (this->_hitPoint > (int)amount)
	{
		this->_hitPoint -= amount;
		std::cout << this->_name << " has " << this->_hitPoint << " hp left.";
	}
	else
	{
		this->_hitPoint = 0;
		std::cout << this->_name << " dies from his wounds..";
	}
	std::cout << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_hitPoint <= 0)
	{
		std::cout << this->_name << " cant be repaired. He's dead you see." << std::endl;
		return ;
	}
	if (this->_energyPoint <= 0)
	{
		std::cout << this->_name << " is to low on energy..." << std::endl;;
		return ;
	}
	this->_hitPoint += amount;
	std::cout << this->_name << " got fixed a bit ! He now has " << this->_hitPoint << "hp !" << std::endl;
}
