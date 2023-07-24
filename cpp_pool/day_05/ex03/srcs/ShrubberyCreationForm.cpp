/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:48:38 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 15:37:52 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include <iostream>
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(void)
: AForm("ShrubberyCreationForm", 145, 137)
{
	this->_target = "notarget";
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
: AForm("ShrubberyCreationForm", 145, 137)
{
	this->_target = target;
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const & src)
: AForm("ShrubberyCreationForm", 145, 137)
{
	*this = src;
}

ShrubberyCreationForm::~ShrubberyCreationForm(void)
{
	return ;
}

ShrubberyCreationForm & ShrubberyCreationForm::operator=(ShrubberyCreationForm const & rhs)
{
	this->_target = rhs._target;
	return *this;
}

void	ShrubberyCreationForm::act(void) const
{
	std::ofstream	ofs;

	ofs.open((this->_target + "_shrubbery").c_str());
	if (ofs.is_open())
	{
		ofs << "               ,@@@@@@@," << std::endl;
		ofs << "       ,,,.   ,@@@@@@/@@,  .oo8888o." << std::endl;
		ofs << "    ,&\%%&%&&%,@@@@@/@@@@@@,8888\\88/8o" << std::endl;
		ofs << "   ,%&\%&&%&&%,@@@\\@@@/@@@88\\88888/88'" << std::endl;
		ofs << "   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'" << std::endl;
		ofs << "   %&&%/ %&\%%&&@@\\ V /@@' `88\\8 `/88'" << std::endl;
		ofs << "   `&%\\ ` /%&'    |.|        \\ '|8'" << std::endl;
		ofs << "       |o|        | |         | |" << std::endl;
		ofs << "       |.|        | |         | |" << std::endl;
		ofs << "    \\\\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/_" << std::endl;
		ofs.close();
	}
	return;
}
