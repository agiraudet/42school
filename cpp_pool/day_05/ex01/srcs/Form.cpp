/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:53:14 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 20:26:51 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form(void)
: _name("noname"), _signed(false), _gradeToSign(1), _gradeToExecute(1)
{
	return;
}

Form::Form(std::string name, unsigned int gToSign, unsigned int gToExecute)
: _name(name), _signed(false), _gradeToSign(gToSign), _gradeToExecute(gToExecute)
{
	this->_checkGrade(gToSign);
	this->_checkGrade(gToExecute);
	std::cout << "Form " << name << " has been created" << std::endl;
}

Form::Form(Form const & src)
: _name(src._name), _gradeToSign(src.getGradeToSign()), _gradeToExecute(src.getGradeToExecute())
{
	*this = src;
	std::cout << "Form " << this->_name << " has been created by copy" << std::endl;
}

Form::~Form(void)
{
	std::cout << "Form " << this->_name << " has been destroyed" << std::endl;
}

Form & Form::operator=(Form const & rhs)
{
	this->_signed = rhs.getSigned();
	return *this;
}

std::ostream &	operator<<(std::ostream & o, Form const & rhs)
{
	o << "Form " << rhs.getName() << " (signed:" << rhs.getSigned();
	o << ") need grade " << rhs.getGradeToSign() << " to be signed, ";
	o << rhs.getGradeToExecute() << " to be executed.";
	return o;
}

void	Form::_checkGrade(unsigned int grade) const
{
	if (grade < 1)
		throw Form::GradeTooHighException();
	if (grade > 150)
		throw Form::GradeTooLowException();
}

std::string	Form::getName(void) const
{
	return this->_name;
}

unsigned int	Form::getGradeToSign(void) const
{
	return this->_gradeToSign;
}

unsigned int	Form::getGradeToExecute(void) const
{
	return this->_gradeToExecute;
}

bool	Form::getSigned(void) const
{
	return this->_signed;
}

void	Form::beSigned(Bureaucrat const & guy)
{
	if (guy.getGrade() > this->_gradeToSign)
		throw Form::GradeTooLowException();
	this->_signed = true;
}
