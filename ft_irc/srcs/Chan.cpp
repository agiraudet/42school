/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chan.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:13:45 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/26 06:43:24 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chan.hpp"
#include "utils.hpp"
#include "mode.hpp"
#include "Mask.hpp"
#include "Logger.hpp"
#include <sstream>

Chan::Chan(void)
: _userLimit(99), _key(""), _topic(""), _name("noname") , _status('='), _mode(CHMD_n)
{
	logger.log(WARN) << "[Chan] " << "Channel created";
	logger.nl();
}

Chan::Chan(std::string name)
: _userLimit(99), _key(""), _topic(""), _name(name), _status('='), _mode(CHMD_n)
{
	logger.log(WARN) << "[Chan] " << "Channel " << name << " created";
	logger.nl();
}

Chan::Chan(Chan const & src)
: _userLimit(99), _key(""), _topic(""), _name("noname") , _status('='), _mode(CHMD_n)
{
	*this = src;
}

Chan::~Chan(void)
{
}

Chan & Chan::operator=(Chan const & rhs)
{
	this->_name = rhs._name;
	this->_userLimit = rhs._userLimit;
	this->_key = rhs._key;
	this->_topic = rhs._topic;
	this->_userMap = rhs._userMap;
	this->_banLst = rhs._banLst;
	this->_invLst = rhs._invLst;
	this->_status = rhs._status;
	this->_mode = rhs._mode;
	return *this;
}

std::string		Chan::getName(void) const
{
	return this->_name;
}

void	Chan::setName(std::string name)
{
	this->_name = name;
}

short	Chan::getMode(void) const
{
	return this->_mode;
}

std::string	Chan::getModeStr(void) const
{
	std::stringstream	ss;

	ss << "+";
	if (this->_mode & CHMD_p)
		ss << "p";
	if (this->_mode & CHMD_s)
		ss << "s";
	if (this->_mode & CHMD_i)
		ss << "i";
	if (this->_mode & CHMD_t)
		ss << "t";
	if (this->_mode & CHMD_n)
		ss << "n";
	if (this->_mode & CHMD_m)
		ss << "m";
	if (this->_mode & CHMD_k)
		ss << "k";
	if (this->_mode & CHMD_l)
		ss << "l " << this->_userLimit;
	return ss.str();
}

void	Chan::addMode(short mode)
{
	modeAdd(this->_mode, mode);
}

void	Chan::delMode(short mode)
{
	modeDel(this->_mode, mode);
}

void	Chan::chgMode(char sign, short mode)
{
	if (sign == '+')
		modeAdd(this->_mode, mode);
	else if (sign == '-')
		modeDel(this->_mode, mode);
}

char	Chan::_getPfx(short mode) const
{
	if (mode & PFX_Q)
		return '~';
	if (mode & PFX_A)
		return '&';
	if (mode & PFX_O)
		return '@';
	if (mode & PFX_H)
		return '%';
	if (mode & PFX_V)
		return '+';
	return 0;
}

void	Chan::chgUserPfx(int userId, char sign, short pfx)
{
	std::map<int, short>::iterator	it = this->_userMap.find(userId);
	if (it != this->_userMap.end())
	{
		if (sign == '-')
			modeDel(it->second, pfx);
		else if (sign == '+')
			modeAdd(it->second, pfx);
	}
}

char	Chan::getUserPfx(int userId) const
{
	std::map<int, short>::const_iterator	it = this->_userMap.find(userId);
	if (it != this->_userMap.end())
		return this->_getPfx(it->second);
	return 0;
}

short	Chan::getUserMode(int userId) const
{
	std::map<int, short>::const_iterator	it = this->_userMap.find(userId);
	if (it != this->_userMap.end())
	{
		if (it->first == userId)
			return it->second;
	}
	return 0;
}

bool	Chan::userIsOp(int userId) const
{
	std::map<int, short>::const_iterator	it = this->_userMap.find(userId);
	if (it != this->_userMap.end())
	{
		if (it->second & PFX_O)
			return true;
	}
	return false;
}

bool	Chan::userIsHalfOp(int userId) const
{	std::map<int, short>::const_iterator	it = this->_userMap.find(userId);
	if (it != this->_userMap.end())
	{
		if (it->second & PFX_O || it->second & PFX_H)
			return true;
	}
	return false;
}

std::string	Chan::getUserLst(std::map<int, User> & servUserMap) const
{
	std::stringstream				ss;
	std::map<int, short>::const_iterator	it = this->_userMap.begin();
	std::map<int, short>::const_iterator	ite = this->_userMap.end();

	for (; it != ite; it++)
	{
		char pfx = this->_getPfx((*it).second);
		if (pfx != 0)
			ss << pfx;
		ss << servUserMap[(*it).first].getNick();
		it++;
		if (it != ite)
			ss << " ";
		it--;
	}
	return ss.str();
}

std::string	Chan::getTopic(void) const
{
	return this->_topic;
}

void	Chan::setTopic(std::string topic)
{
	this->_topic = topic;
}

char 	Chan::getStatus(void) const
{
	return this->_status;
}

void	Chan::setStatus(char status)
{
	this->_status = status;
}

bool	Chan::userIsBan(User & user) const
{
	std::string userSrc = user.getSource();

	if (userSrc[0] == ':')
		userSrc.erase(0, 1);
	for (size_t i = 0; i < this->_banLst.size(); i++)
	{
		if (maskMatch(userSrc, this->_banLst[i]))
			return true;
	}
	return false;
}

bool	Chan::userIsInv(User & user) const
{
	for (size_t i = 0; i < this->_invLst.size(); i++)
	{
		if (this->_invLst[i].compare(user.getNick()) == 0)
			return true;
	}
	return false;
}

bool	Chan::keyIsCorrect(std::string const & key) const
{
	if (this->_key.compare(key) == 0)
		return true;
	return false;
}

bool	Chan::isFull(void) const
{
	return static_cast<long long>(this->_userLimit) <= static_cast<long long>(this->_userMap.size());
}

void	Chan::setUserLimit(int userLimit)
{
	this->_userLimit = userLimit;
}

int	Chan::join(User & user)
{
	short	pfx = 0;

	if (this->_userMap.size() == 0)
		pfx = PFX_O;
	if (this->userIsBan(user))
		return 0;
	this->_userMap.insert(std::pair<int, short>(user.getId(), pfx));
	return 1;
}

void	Chan::part(int userId)
{
	std::map<int, short>::iterator	it;

	it = this->_userMap.find(userId);
	if (it != this->_userMap.end())
		this->_userMap.erase(it);
}

void	Chan::sendMsg(int fromId, std::string msg, std::map<int, User> & servUserMap) const
{
	std::map<int, short>::const_iterator	it = this->_userMap.begin();
	std::map<int, short>::const_iterator	ite = this->_userMap.end();

	for (; it != ite; it++)
	{
		if (it->first != fromId)
			servUserMap[it->first].addToSendMsg(msg);
	}
}

bool	Chan::userInChan(int userId) const
{
	if (this->_userMap.find(userId) != this->_userMap.end())
		return true;
	return false;
}

void	Chan::addBanMask(std::string mask)
{
	if (mask.size() > 0)
		this->_banLst.push_back(mask);
}

void	Chan::delBanMask(std::string mask)
{
	if (mask.size() <= 0)
		return ;

	std::vector<std::string>::iterator	it = this->_banLst.begin();
	while (it != this->_banLst.end())
	{
		if (mask.compare(*it) == 0)
			it = this->_banLst.erase(it);
		else
			it++;
	}
}

std::vector<std::string> const &	Chan::getBanLst(void) const
{
	return this->_banLst;
}

std::string	Chan::getBanMask(void) const
{
	std::vector<std::string>::const_iterator	it = this->_banLst.begin();
	std::vector<std::string>::const_iterator	ite = this->_banLst.end();
	std::string									banMask = "";

	for (; it != ite; it++)
	{
		banMask += *it;
		if (it+1 != ite)
			banMask += " ";
	}
	return banMask;
}

void	Chan::addInv(std::string guest)
{
	this->_invLst.push_back(guest);
}

void	Chan::setKey(std::string key)
{
	this->_key = key;
}

size_t		Chan::getNbUser(void) const
{
	return this->_userMap.size();
}
