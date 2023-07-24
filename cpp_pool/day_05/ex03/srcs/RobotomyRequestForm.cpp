/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:48:38 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 15:37:40 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void)
: AForm("RobotomyRequestForm", 72, 45)
{
	this->_target = "notarget";
}

RobotomyRequestForm::RobotomyRequestForm(std::string target)
: AForm("RobotomyRequestForm", 72, 45)
{
	this->_target = target;
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const & src)
: AForm("RobotomyRequestForm", 72, 45)
{
	*this = src;
}

RobotomyRequestForm::~RobotomyRequestForm(void)
{
	return ;
}

RobotomyRequestForm & RobotomyRequestForm::operator=(RobotomyRequestForm const & rhs)
{
	this->_target = rhs._target;
	return *this;
}

void	RobotomyRequestForm::act(void) const
{
	static unsigned int	r = 0;

	std::cout << "*BZZZZZZ* ... *BZZ* *BZZ*" << std::endl;
	std::cout << "About " << this->_target << "... ";
	if (r == 0)
		std::cout << "The operation failed." << std::endl;
	else
		std::cout << "The operation was a success !" << std::endl;
	r ^= 1;
	return;
}
