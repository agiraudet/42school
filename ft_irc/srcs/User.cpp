/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:24:47 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/17 10:13:42 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "mode.hpp"
#include "utils.hpp"

User::User(void)
: _id(-1), _nick("guest"), _mode(0), _registered(false), _passwd(false), _bufIn(""), _awaitingPong(false)
{
	time(&this->_lastRcv);
}

User::User(int id)
: _id(id), _nick("guest"), _mode(0), _registered(false), _passwd(false), _bufIn(""), _awaitingPong(false)
{
	time(&this->_lastRcv);
}

User::User(User const & src)
: _id(src.getId())
{
	*this = src;
}

User::~User(void)
{
}

User & User::operator=(User const & rhs)
{
	this->_mode = rhs._mode;
	this->_nick = rhs._nick;
	this->_realName = rhs._realName;
	this->_registered = rhs._registered;
	this->_passwd = rhs._passwd;
	this->_msgIn = rhs._msgIn;
	this->_msgOut = rhs._msgOut;
	this->_bufIn = rhs._bufIn;
	this->_lastRcv = rhs._lastRcv;
	this->_lastPing = rhs._lastPing;
	this->_awaitingPong = rhs._awaitingPong;
	return *this;
}

std::string	User::getSource(void) const
{
	return ":" + this->_nick + "!" + this->_username + "@" + this->_domain;
}

short	User::getMode(void) const
{
	return this->_mode;
}

std::string User::getStrMode(void) const
{
	std::string	ret = "";

	if (this->_mode & USMD_i)
		ret += 'i';
	if (this->_mode & USMD_o)
		ret += 'o';
	if (this->_mode & USMD_O)
		ret += 'O';
	if (this->_mode & USMD_w)
		ret += 'w';
	return ret;
}

void	User::setMode(short mode)
{
	this->_mode = mode;
}

void	User::addMode(short mode)
{
	modeAdd(this->_mode, mode);
}

void	User::delMode(short mode)
{
	modeDel(this->_mode, mode);
}

std::string	User::getNick(void) const
{
	return this->_nick;
}

void	User::setNick(std::string nick)
{
	if (nick.size() > 9)
		this->_nick = nick.substr(0, 9);
	else
		this->_nick = nick;
}

std::string	User::getRealName(void) const
{
	return this->_realName;
}

void	User::setRealName(std::string realName)
{
	this->_realName = realName;
}

std::string	User::getDomain(void) const
{
	return this->_domain;
}

void	User::setDomain(std::string domain)
{
	this->_domain = domain;
}

std::string	User::getUsername(void) const
{
	return this->_username;
}

void	User::setUsername(std::string username)
{
	this->_username = username;
}

int	User::getId(void) const
{
	return this->_id;
}

bool	User::getReg(void) const
{
	return this->_registered;
}

void	User::setReg(bool val)
{
	this->_registered = val;
}

bool	User::getPasswd(void) const
{
	return this->_passwd;
}

void	User::setPasswd(bool val)
{
	this->_passwd = val;
}

void	User::recvMsg(const char * msg, int nbytes)
{
	static std::string const	sep = "\x0d\x0a";

	this->_bufIn += std::string(msg, nbytes);
	for (size_t pos = this->_bufIn.find(sep); pos != std::string::npos; pos = this->_bufIn.find(sep))
	{
		this->_msgIn.push(this->_bufIn.substr(0, pos));
		pos += sep.size();
		this->_bufIn = this->_bufIn.substr(pos);
	}
	time(&this->_lastRcv);
}

void	User::addToSendMsg(std::string msg)
{
	this->_msgOut.push(std::string(msg));
}

std::string	User::getMsg(short dir)
{
	std::queue<std::string> * msgQueue = &this->_msgOut;
	std::string	msg = "";

	if (dir == IN)
		msgQueue = &this->_msgIn;
	if (msgQueue->size() != 0)
	{
		msg = msgQueue->front();
		msgQueue->pop();
	}
	return msg;
}

std::string	User::getMsgOut(void)
{
	static std::string	leftOver = "";
	std::string msg = "";
	std::string	tmp;

	if (leftOver.size() > 0)
	{
		msg += leftOver.substr(0, 510);
		leftOver.erase(0, msg.size());
		if (leftOver.size() == 0)
			msg += "\x0d\x0a";
	}
	while (this->_msgOut.size() > 0 && msg.size() < 510)
	{
		tmp = this->_msgOut.front();
		this->_msgOut.pop();
		if (msg.size() + tmp.size() < 510)
		{
			msg += tmp;
			msg += "\x0d\x0a";
		}
		else
		{
			std::string partial = tmp.substr(0, 510 - msg.size());
			msg += partial;
			leftOver = tmp.substr(partial.size());
			break ;
		}
	}
	return msg;
}

int	User::getNbMsg(short dir)
{
	std::queue<std::string> * msgQueue = &this->_msgOut;

	if (dir == IN)
		msgQueue = &this->_msgIn;
	return msgQueue->size();
}

bool	User::getAwaitingPong(void) const
{
	return this->_awaitingPong;
}

void	User::setAwaitingPong(bool awaiting)
{
	this->_awaitingPong = awaiting;
}

time_t	User::getLastPing(void) const
{
	return this->_lastPing;
}

void	User::setLastPing(time_t ping)
{
	this->_lastPing = ping;
}

time_t	User::getLastRcv(void) const
{
	return this->_lastRcv;
}
