/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:44:18 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/18 12:34:54 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl(void)
{
	this->_f[0] = &Harl::_debug;
	this->_f[1] = &Harl::_info;
	this->_f[2] = &Harl::_warning;
	this->_f[3] = &Harl::_error;
	return ;
}

Harl::~Harl(void)
{
	return ;
}

void	Harl::complain(std::string level) const
{
	std::string	lst[] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for(int i = 0; i < 4; i++)
	{
		if (lst[i].compare(level) == 0)
			(this->*_f[i])();
	}
}

void	Harl::_debug(void) const
{
	std::cout << "Your  7XL-double-cheese already come with extra heart attack" << std::endl;
}

void	Harl::_info(void) const
{
	std::cout << "You dont need extra beacon John, you need therapy." << std::endl;
}

void	Harl::_warning(void) const
{
	std::cout << "Eating as a coping mechanism is killing you, John." << std::endl;
}

void	Harl::_error(void) const
{
	std::cout << "Also processed meat is killing the planet." << std::endl;
}
