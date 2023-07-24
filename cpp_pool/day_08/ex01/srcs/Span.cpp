/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:18:21 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/28 10:17:42 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

Span::Span(void)
: _N(0)
{
	return ;
}

Span::Span(unsigned int N)
: _N(N)
{
	return ;
}

Span::Span(Span const & src)
{
	*this = src;
}

Span::~Span(void)
{
	return ;
}

Span & Span::operator=(Span const & rhs)
{
	this->_N = rhs._N;
	this->_lst = std::list<int>(rhs._lst);
	return *this;
}

void	Span::addNumber(int n)
{
	if (this->_lst.size() >= this->_N)
		throw Span::NoRoomException();
	this->_lst.push_back(n);
}

int		Span::shortestSpan(void) 
{
	int sSpan = -1;

	if (this->_lst.size() <= 1)
		throw Span::NoElemException();
	this->_lst.sort();
	std::list<int>::const_iterator ita = this->_lst.begin();
	std::list<int>::const_iterator itb = this->_lst.begin();
	ita++;
	while (ita != this->_lst.end())
	{
		if (sSpan == -1 || *ita - *itb < sSpan)
			sSpan = *ita - *itb;
		itb++;
		ita++;
	}
	return sSpan;
}

int	Span::longestSpan(void) 
{
	if (this->_lst.size() <= 1)
		throw Span::NoElemException();
	return *std::max_element(this->_lst.begin(), this->_lst.end())
		- *std::min_element(this->_lst.begin(), this->_lst.end());
}

void	Span::printLst(void) const
{
	std::list<int>::const_iterator	it;

	for (it=this->_lst.begin(); it!=this->_lst.end(); ++it)
	    std::cout << ' ' << *it;
	std::cout << std::endl;
}

void	Span::addNumberRange(int from, int to, int step)
{
	if (from > to)
		std::swap(from, to);
	for (; from <= to; from += step)
		this->addNumber(from);
}

void	Span::addNumberRand(int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		this->addNumber(rand());
}
