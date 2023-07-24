/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:25:32 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 20:35:00 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"

Intern::Intern(void)
{
	this->_f[0] = &Intern::_SCForm;
	this->_f[1] = &Intern::_PPForm;
	this->_f[2] = &Intern::_RRForm;
}

Intern::Intern(Intern const & src)
{
	*this = src;
}

Intern::~Intern(void)
{
	return ;
}

Intern & Intern::operator=(Intern const & rhs)
{
	std::copy(rhs._f, rhs._f + 3, this->_f);
	return *this;
}

AForm*	Intern::makeForm(std::string name, std::string target) const
{
	std::string	options[] = {"shruberry", "presidential", "robotomy"};
	AForm*		newForm;

	for (int i = 0; i < 3; i++)
	{
		if (name.find(options[i]) != std::string::npos)
		{
			newForm = (this->*_f[i])(target);
			std::cout << "Intern create " << *newForm << std::endl;
			return newForm;
		}
	}
	std::cout << "Intern could not find a form called " << name << std::endl;
	return 0;
}

AForm*	Intern::_SCForm(std::string target) const
{
	AForm*	form = new ShrubberyCreationForm(target);
	return form;
}

AForm*	Intern::_PPForm(std::string target) const
{
	AForm*	form = new PresidentialPardonForm(target);
	return form;
}
AForm*	Intern::_RRForm(std::string target) const
{
	AForm*	form = new RobotomyRequestForm(target);
	return form;
}
