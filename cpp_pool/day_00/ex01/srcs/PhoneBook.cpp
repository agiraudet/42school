/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:25:08 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 17:39:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook(void)
: _nbContact(0), _cursor(0)
{
	return;
}

PhoneBook::~PhoneBook(void)
{
	return;
}

int	PhoneBook::getNbContact(void) const
{
	return this->_nbContact;
}

void	PhoneBook::addContact(void)
{
	this->_lstContact[this->_cursor].fillContact();
	this->_cursor++;
	if (this->_cursor >= 8)
		this->_cursor = 0;
	if (this->_nbContact < 8)
		_nbContact++;
}

void	PhoneBook::addContactAuto(std::string fn, std::string ln, std::string nn, std::string pn, std::string ds)
{
	this->_lstContact[this->_cursor].fillContactAuto(fn, ln, nn, pn, ds);
	this->_cursor++;
	if (this->_cursor >= 8)
		this->_cursor = 0;
	if (this->_nbContact < 8)
		_nbContact++;
}

void	PhoneBook::search(void)
{
	for (int i = 0; i < this->_nbContact; i++)
		this->_lstContact[i].printSearchInfo(i);
}

void	PhoneBook::selectContact(int i)
{
	if (i < this->_nbContact)
		this->_lstContact[i].printContact();
}
