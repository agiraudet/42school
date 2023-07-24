/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:36:06 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 17:24:33 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include <iostream>
#include <iomanip>

Contact::Contact(void)
{
	return;
}	

Contact::~Contact(void)
{
	return;
}

void	Contact::fillContactAuto(std::string fn, std::string ln, std::string nn, std::string pn, std::string ds)
{
	this->_firstName = fn;
	this->_lastName = ln;
	this->_nickName = nn;
	this->_phoneNumber = pn;
	this->_darkestSecret = ds;
}

void	Contact::fillContact(void)
{
	std::cout << "First Name.....: ";
	this->_getStr(&this->_firstName);
	std::cout << "Last Name......: ";
	this->_getStr(&this->_lastName);
	std::cout << "Nick Name......: ";
	this->_getStr(&this->_nickName);
	std::cout << "Phone Number...: ";
	this->_getStr(&this->_phoneNumber);
	std::cout << "Darkest Secret.: ";
	this->_getStr(&this->_darkestSecret);
}

void	Contact::printContact(void) const
{
	std::cout << "First Name.....: " << this->_firstName << std::endl;
	std::cout << "Last Name......: " << this->_lastName << std::endl;
	std::cout << "Nick Name......: " << this->_nickName << std::endl;
	std::cout << "Phone Number...: " << this->_phoneNumber << std::endl;
	std::cout << "Darkest Secret.: " << this->_darkestSecret << std::endl;
}

void	Contact::printSearchInfo(int id) const
{
	std::cout << std::setfill(' ') << std::setw(10) << id;
	std::cout << '|';
	this->_printStr(this->_firstName);
	std::cout << '|';
	this->_printStr(this->_lastName);
	std::cout << '|';
	this->_printStr(this->_nickName);
	std::cout << std::endl;
}

void	Contact::_getStr(std::string *str)
{
	std::string	tmp;

	while (!tmp.size())
		std::getline(std::cin >> std::ws, tmp);
	*str = tmp;
}

void	Contact::_printStr(std::string str) const
{

	if (str.size() <= 10)
		std::cout << std::setfill(' ') << std::setw(10) << str;
	else
	{
		for (int i = 0; i < 9; i++)
			std::cout << str[i];
		std::cout << '.';
	}
}
