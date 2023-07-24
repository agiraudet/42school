/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:53:14 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 20:32:14 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(std::string name, unsigned int gToSign, unsigned int gToExecute)
: _name(name), _signed(false), _gradeToSign(gToSign), _gradeToExecute(gToExecute)
{
	this->_checkGrade(gToSign);
	this->_checkGrade(gToExecute);
}

AForm::AForm(AForm const & src)
: _name(src._name), _gradeToSign(src.getGradeToSign()), _gradeToExecute(src.getGradeToExecute())
{
	*this = src;
}

AForm::~AForm(void)
{
}

AForm & AForm::operator=(AForm const & rhs)
{
	this->_signed = rhs.getSigned();
	return *this;
}

std::ostream &	operator<<(std::ostream & o, AForm const & rhs)
{
	o << "AForm " << rhs.getName() << " (signed:" << rhs.getSigned();
	o << ") need grade " << rhs.getGradeToSign() << " to be signed, ";
	o << rhs.getGradeToExecute() << " to be executed.";
	return o;
}

void	AForm::_checkGrade(unsigned int grade) const
{
	if (grade < 1)
		throw AForm::GradeTooHighException();
	if (grade > 150)
		throw AForm::GradeTooLowException();
}

std::string	AForm::getName(void) const
{
	return this->_name;
}

unsigned int	AForm::getGradeToSign(void) const
{
	return this->_gradeToSign;
}

unsigned int	AForm::getGradeToExecute(void) const
{
	return this->_gradeToExecute;
}

bool	AForm::getSigned(void) const
{
	return this->_signed;
}

void	AForm::beSigned(Bureaucrat const & guy)
{
	if (guy.getGrade() > this->_gradeToSign)
		throw AForm::GradeTooLowException();
	this->_signed = true;
}

void	AForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->_gradeToExecute)
		throw AForm::GradeTooLowException();
	if (!this->_signed)
		throw AForm::NotSignedException();
	this->act();
}

