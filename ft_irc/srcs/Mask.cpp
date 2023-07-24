/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mask.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:52:49 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/23 12:46:24 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mask.hpp"

Mask::Mask(void)
: _nick(""), _user(""), _host("")
{
}

Mask::Mask(std::string mask)
: _nick(""), _user(""), _host("")
{
	std::string *	field = &this->_nick;

	for (int i = 0; mask[i] != 0; i++)
	{
		if (mask[i] == '!')
			field = &this->_user;
		else if (mask[i] == '@')
			field = &this->_host;
		else
			*field += mask[i];
	}
}

Mask::Mask(Mask const & src)
{
	*this = src;
}

Mask::~Mask(void)
{
}

Mask & Mask::operator=(Mask const & rhs)
{
	this->_nick = rhs._nick;
	this->_user = rhs._user;
	this->_host = rhs._host;
	return *this;
}

std::string & Mask::getNick(void)
{
	return this->_nick;
}

std::string & Mask::getUser(void)
{
	return this->_user;
}

std::string & Mask::getHost(void)
{
	return this->_host;
}

bool	Mask::_fieldMatch(std::string const & in, std::string const & field)
{
	int	i = 0;
	int	ii = 0;

	while (in[i] && field[ii])
	{
		while (field[ii] == '?' && in[i])
		{
			ii++;
			i++;
		}
		if (field[ii] == '*' && in[i])
		{
			ii++;
			while (in[i] && in[i] != field[ii])
				i++;
		}
		if (field[ii] && in[i] && field[ii] == in[i])
		{
			i++;
			ii++;
		}
		else
			break;
	}

	if (in[i] != field[ii])
		return false;
	return true;
}

bool	Mask::match(std::string const & in)
{
	Mask	inMask(in);

	return this->match(inMask);
}

bool	Mask::match(Mask & inMask)
{
	if (this->_nick.size() > 0)
	{
		if (!(this->_fieldMatch(inMask.getNick(), this->_nick)))
			return false;
	}
	if (this->_user.size() > 0)
	{
		if (!(this->_fieldMatch(inMask.getUser(), this->_user)))
			return false;
	}
	if (this->_host.size() > 0)
	{
		if (!(this->_fieldMatch(inMask.getHost(), this->_host)))
			return false;
	}
	return true;
}

bool maskMatch(Mask & in, Mask & mask)
{
	return mask.match(in);
}

bool maskMatch(std::string in, Mask & mask)
{
	return mask.match(in);
}

bool maskMatch(Mask & in, std::string mask)
{
	Mask	mMask(mask);

	return mMask.match(in);
}

bool maskMatch(std::string in, std::string mask)
{
	Mask	mMask(mask);

	return mMask.match(in);
}
