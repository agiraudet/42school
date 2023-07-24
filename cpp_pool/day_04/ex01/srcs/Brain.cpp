/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:11:19 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/21 13:29:05 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(void)
{
	std::cout << "An Brain has been created" << std::endl;
}

Brain::Brain(Brain const & src)
{
	*this = src;
	std::cout << "An Brain has been created by copy" << std::endl;
}

Brain::~Brain(void)
{
	std::cout << "An Brain has been destroyed" << std::endl;
}

Brain & Brain::operator=(Brain const & rhs)
{
	std::copy(rhs._ideas, rhs._ideas + 100, this->_ideas);
	return *this;
}

std::string	Brain::getIdea(int n) const
{
	if (n < 0 || n >= 100)
		return NULL;
	return this->_ideas[n];
}

void	Brain::setIdea(int n, std::string idea)
{
	if (n < 0 || n >= 100)
		return ;
	this->_ideas[n] = idea;
}
