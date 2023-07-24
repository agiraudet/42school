/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:28:47 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/16 18:36:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "utils.hpp"
#include "Logger.hpp"
#include <ctime>
#include <sstream>

Server::Server(void)
: coHandler(this), _cmdHandler(this), _passwd("nopass"), _source("localhost")
{
	this->_loadOpMap();
	this->_setSource();
	this->_setCreationTime();
}

Server::Server(std::string port)
: coHandler(this), _cmdHandler(this), _passwd("nopass"), _source("localhost")
{
	this->_loadOpMap();
	this->_setSource();
	this->_setCreationTime();
	this->coHandler.setPort(port);
}

Server::Server(std::string port, std::string pass)
: coHandler(this), _cmdHandler(this), _source("localhost")
{
	this->_loadOpMap();
	this->_setSource();
	this->_setCreationTime();
	this->coHandler.setPort(port);
	this->setPassword(pass);
}

Server::Server(Server const & src)
: coHandler(this), _cmdHandler(this)
{
	*this = src;
}

Server::~Server(void)
{
}

Server & Server::operator=(Server const & rhs)
{
	this->_opMap = rhs._opMap;
	this->_chanMap = rhs._chanMap;
	this->_userMap = rhs._userMap;
	this->_passwd = rhs._passwd;
	this->_source = rhs._source;
	return *this;
}

void	Server::_loadOpMap(void)
{
	this->_opMap.insert(std::pair<std::string,
			std::pair<std::string, std::string> >("name",
			std::pair<std::string, std::string>("127.0.0.1", "pass")));
}

void	Server::_setCreationTime(void)
{
	std::time_t			t = std::time(0);
	std::tm *			now = std::localtime(&t);
	char				buf[500];

	if (strftime(buf, sizeof(buf), "%F at %X", now) != 0)
		this->_creationTime = std::string(buf);
	else
		this->_creationTime = "unknow time";
}

std::string	Server::getCreationTime(void) const
{
	return this->_creationTime;
}

void	Server::_setSource(std::string source)
{
	this->_source = source;
}

void	Server::_setSource(void)
{
	char	name[256];

	if (gethostname(name, 256) == -1)
		this->_source = "42IRCserv";
	else
		this->_source = std::string(name);
}

std::string	Server::getSource(void) const
{
	return this->_source;
}

void	Server::setPassword(std::string pass)
{
	this->_passwd = pass;
}

std::string	Server::getPassword(void) const
{
	return this->_passwd;
}

void	Server::run(void)
{
	this->coHandler.start();
}

void	Server::addUser(int id)
{
	this->_userMap.insert(std::pair<int, User>(id, User(id)));
	this->_listUser();
}

void	Server::delUser(int id)
{
	this->delUser(id, 1);
}

void	Server::delUser(int id, int cause)
{
	std::map<std::string, Chan>::iterator	it = this->_chanMap.begin();
	std::map<std::string, Chan>::iterator	tmp;

	while (it != this->_chanMap.end())
	{
		if (it->second.userInChan(id))
		{
			if (cause == 0)
			{
				std::string quitNotice = this->_userMap[id].getSource() + " QUIT :Quit: Connection reset by peer";
				it->second.sendMsg(id, quitNotice, this->_userMap);
			}
			it->second.part(id);
			if (it->second.getNbUser() <= 0)
			{
				tmp = it;
				it++;
				this->_chanMap.erase(tmp);
			}
			else
				it++;
		}
		else
			it++;
	}
	this->_userMap.erase(id);
}

User &	Server::getUser(int id)
{
	return this->_userMap[id];
}

User &	Server::getUser(std::string nick)
{
	std::map<int, User>::iterator	it = this->_userMap.begin();
	std::map<int, User>::iterator	ite = this->_userMap.end();

	for (; it != ite; it++)
	{
		if (nick.compare(it->second.getNick()) == 0)
			break ;
	}
	return it->second;
}

std::string	Server::getUserLst(void) const
{
	std::map<int, User>::const_iterator	it = this->_userMap.begin();
	std::map<int, User>::const_iterator	ite = this->_userMap.end();
	std::string							usLst = "";

	for (; it != ite; it++)
		usLst += it->second.getNick();
	return usLst;
}

bool	Server::userExist(std::string nick) const
{
	std::map<int, User>::const_iterator	it = this->_userMap.begin();
	std::map<int, User>::const_iterator	ite = this->_userMap.end();

	for (; it != ite; it++)
	{
		if (nick.compare(it->second.getNick()) == 0)
			return true;
	}
	return false;
}

bool	Server::userExist(int id) const
{
	std::map<int, User>::const_iterator	it = this->_userMap.begin();
	std::map<int, User>::const_iterator	ite = this->_userMap.end();

	for (; it != ite; it++)
	{
		if (it->first == id)
			return true;
	}
	return false;
}

std::map<int, User> &	Server::getUserMap(void)
{
	return this->_userMap;
}

std::map<std::string, Chan> &	Server::getChanMap(void)
{
	return this->_chanMap;
}

void	Server::_listUser(void)
{
	std::map<int, User>::iterator	it;
	logger.log(DEBUG) << "[Serv] User List: ";
	for (it = this->_userMap.begin(); it != this->_userMap.end(); it++)
		logger.log(DEBUG) << it->first << ":" << it->second.getNick() << " ";
	logger.nl();
}


Chan &	Server::getChan(std::string chanName)
{
	if (this->_chanMap.find(chanName) == this->_chanMap.end())
		this->_chanMap.insert(std::pair<std::string, Chan>(chanName, Chan(chanName)));
	return this->_chanMap[chanName];
}

bool	Server::chanExist(std::string chanName)
{
	if (this->_chanMap.find(chanName) != this->_chanMap.end())
		return true;
	return false;
}

void	Server::userRecvMsg(int id, const char *msg, int nbytes)
{	
	if (this->userExist(id))
	{
		User &	user = this->getUser(id);
		user.recvMsg(msg, nbytes);
		this->processMsg(user);
	}
}

bool	Server::_checkMsgError(std::string & msg)
{
	std::vector<std::string>	splitMsg = ftSplit(msg, " ");
	int							i = 0;

	if (splitMsg[i][0] == ':')
		i++;
	if (splitMsg[i].compare("ERROR") == 0)
		return true;
	return false;
}

void	Server::userSendMsg(int userId)
{
	if (!this->userExist(userId))
		return ;
	User &		user = this->getUser(userId);
	std::string	msg;

//	while (user.getNbMsg(OUT) > 0)
	if (user.getNbMsg(OUT) > 0)
	{
		msg = user.getMsgOut();
		this->coHandler.sendToClient(userId, msg);
		if (this->_checkMsgError(msg))
		{
			this->coHandler.killCo(userId);
			//break;
		}
	}
}

int	Server::userHasMsg(int userId, short dir)
{
	return (this->_userMap[userId].getNbMsg(dir));
}

void	Server::processMsg(User & user)
{
	std::string	msg;

	while (user.getNbMsg(IN) > 0)
	{
		msg = user.getMsg(IN);
		this->_cmdHandler.onMsg(msg, user);
	}
}

e_opInfo	Server::checkOp(std::string const & name, std::string const & pass, std::string const host) const
{
	std::map<std::string, std::pair<std::string, std::string> >::const_iterator	it;

	it = this->_opMap.find(name);
	if (it == this->_opMap.end())
		return OP_ERRNAME;
	if (pass.compare(it->second.second) != 0)
		return OP_ERRPASS;
	if (host.compare(it->second.first) != 0)
		return OP_ERRHOST;
	return OP_OK;
}

void	Server::checkChan(Chan & chan)
{
	if (chan.getNbUser() <= 0)
		this->_delChan(chan.getName());
}

void	Server::_delChan(std::string const & chanName)
{
	std::map<std::string, Chan>::iterator	it = this->_chanMap.find(chanName);

	if (it != this->_chanMap.end())
		this->_chanMap.erase(it);
}

void	Server::killUser(User & user, std::string reason, std::string src)
{
	user.addToSendMsg(src + " KILL " + reason);

	std::map<std::string, Chan>::iterator	it = this->_chanMap.begin();
	std::map<std::string, Chan>::iterator	ite = this->_chanMap.end();
	std::string	killNotice = user.getSource() + " QUIT :Quit: killed: " + reason;
	for (; it != ite; it++)
	{
		Chan & chan = it->second;
		if (chan.userInChan(user.getId()))
			chan.sendMsg(user.getId(), killNotice, this->_userMap);
	}
}

void	Server::checkTO(void)
{
	std::map<int, User>::iterator	it = this->_userMap.begin();
	std::map<int, User>::iterator	ite = this->_userMap.end();
	time_t							currentTime = time(NULL);

	for (; it != ite; it++)
	{
		User & user = it->second;
		if (user.getAwaitingPong() && (currentTime - user.getLastPing() > PING_TO))
		{
			this->killUser(user, "Connection timed out", ":" + this->getSource());
			user.setAwaitingPong(false);
		}
		else if (!(user.getAwaitingPong()) && currentTime - user.getLastRcv() > PING_TM)
		{
			user.addToSendMsg(":" + this->getSource() + " PING " + user.getNick());
			user.setAwaitingPong(true);
			user.setLastPing(currentTime);
		}
	}
}
