/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:48:38 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 15:37:25 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void)
: AForm("PresidentialPardonForm", 25, 5)
{
	this->_target = "notarget";
}

PresidentialPardonForm::PresidentialPardonForm(std::string target)
: AForm("PresidentialPardonForm", 25, 5)
{
	this->_target = target;
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const & src)
: AForm("PresidentialPardonForm", 25, 5)
{
	*this = src;
}

PresidentialPardonForm::~PresidentialPardonForm(void)
{
	return ;
}

PresidentialPardonForm & PresidentialPardonForm::operator=(PresidentialPardonForm const & rhs)
{
	this->_target = rhs._target;
	return *this;
}

void	PresidentialPardonForm::act(void) const
{
	std::cout << this->_target << " have been pardonned by Zaphod Beeblebrox himself !"
		<< std::endl;
	return;
}
