/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:19:43 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 20:03:38 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat(void)
: _name("noname"), _grade(150)
{
	return ;
}

Bureaucrat::Bureaucrat(std::string name, unsigned int grade)
: _name(name), _grade(grade)
{
	if (this->_grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if (this->_grade > 150)
			throw Bureaucrat::GradeTooLowException();
	std::cout << "Constructed Bureaucrat \"" << name << "\" (grade ";
	std::cout << grade << ")" << std::endl;
}

Bureaucrat::Bureaucrat(Bureaucrat const & src)
: _name(src._name)
{
	*this = src;
	std::cout << "Constructed Bureaucrat \"" << this->_name << "\" (grade ";
	std::cout << this->_grade << ") by copy." << std::endl;
}

Bureaucrat::~Bureaucrat(void)
{
	std::cout << "Destroyed " << this->_name << std::endl;
}

Bureaucrat & Bureaucrat::operator=(Bureaucrat const & rhs)
{
	this->_grade = rhs.getGrade();
	return *this;
}

std::string	Bureaucrat::getName(void) const
{
	return this->_name;
}

unsigned int	Bureaucrat::getGrade(void) const
{
	return this->_grade;
}

void	Bureaucrat::incGrade(void)
{
	if (this->_grade <= 1)
		throw Bureaucrat::GradeTooHighException();
	else
		this->_grade--;
}

void	Bureaucrat::decGrade(void)
{
	if (this->_grade >= 150)
			throw Bureaucrat::GradeTooLowException();
	else
		this->_grade++;
}

void	Bureaucrat::signForm(Form & form) const
{
	std::cout << this->_name;
	try
	{
		form.beSigned(*this);
		std::cout << " signed " << form.getName() << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << " couldn't sign " << form.getName() << ": " << e.what() << std::endl;
	}
}


std::ostream &	operator<<(std::ostream & o, Bureaucrat const & rhs)
{
	o << rhs.getName() << " bureaucrat grade " << rhs.getGrade();
	return o;
}
