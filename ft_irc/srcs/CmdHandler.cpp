/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:49:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/16 18:19:26 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"
#include "Logger.hpp"
#include <sstream>

CmdHandler::CmdHandler(void)
: _servPtr(NULL)
{
}

CmdHandler::CmdHandler(Server * servPtr)
: _servPtr(servPtr)
{
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("NICK", &CmdHandler::_onNICK));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("PASS", &CmdHandler::_onPASS));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("USER", &CmdHandler::_onUSER));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("PING", &CmdHandler::_onPING));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("QUIT", &CmdHandler::_onQUIT));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("JOIN", &CmdHandler::_onJOIN));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("PRIVMSG", &CmdHandler::_onPRIVMSG));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("MODE", &CmdHandler::_onMODE));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("OPER", &CmdHandler::_onOPER));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("WHO", &CmdHandler::_onWHO));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("PART", &CmdHandler::_onPART));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("NOTICE", &CmdHandler::_onNOTICE));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("KICK", &CmdHandler::_onKICK));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("TOPIC", &CmdHandler::_onTOPIC));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("NAMES", &CmdHandler::_onNAMES));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("INVITE", &CmdHandler::_onINVITE));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("LIST", &CmdHandler::_onLIST));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("PONG", &CmdHandler::_onPONG));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("MOTD", &CmdHandler::_onMOTD));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("motd", &CmdHandler::_onMOTD));
	this->_cmdMap.insert(std::pair<std::string, t_cmdFct>("kill", &CmdHandler::_onKILL));
}

CmdHandler::CmdHandler(CmdHandler const & src)
{
	if (this != &src)
		*this = src;
}

CmdHandler::~CmdHandler(void)
{
}

CmdHandler & CmdHandler::operator=(CmdHandler const & rhs)
{
	this->_servPtr = rhs._servPtr;
	this->_cmdMap = rhs._cmdMap;
	return *this;
}

Server *	CmdHandler::getServ(void) const
{
	return this->_servPtr;
}

void	CmdHandler::onMsg(std::string const & msg, User & user)
{
	std::vector<std::string>	splitMsg = ircSplit(msg);

	ircFormatParam(splitMsg);
	if (!user.getPasswd() && splitMsg[0].compare("PASS") != 0)
		return ;
	if (user.getPasswd() && !user.getReg() && (splitMsg[0].compare("USER") != 0 && splitMsg[0].compare("NICK") != 0))
	{
		user.addToSendMsg(this->_numReply(user, 451));
		return;
	}

	std::map<std::string, t_cmdFct>::iterator	it = this->_cmdMap.find(splitMsg[0]);

	//If the command is Unknow
	if (it == this->_cmdMap.end())
		user.addToSendMsg(this->_numReply(user, 421, splitMsg[0]));
	else
		(this->*it->second)(user, splitMsg);
}

void	CmdHandler::sendMsg(User & user, int num)
{
	user.addToSendMsg(this->_numReply(user, num));
}

void	CmdHandler::sendMsg(User & user, int num, std::string param)
{
	user.addToSendMsg(this->_numReply(user, num, param));
}

void	CmdHandler::sendMsg(User & user, std::string msg)
{
	user.addToSendMsg(msg);
}

std::string	CmdHandler::_numToStr(int num)
{
	std::stringstream	ss;

	if (num < 10)
		ss << "0";
	if (num < 100)
		ss << "0";
	ss << num;
	return ss.str();
}

std::string	CmdHandler::_numReply(User & user, int num)
{
	return this->_numReply(user, num, "");
}

std::string	CmdHandler::_numReply(User & user, int num, std::string param)
{
	std::string	msg = "";
	std::string tmp;

	msg += (":" + this->_servPtr->getSource() + " " + this->_numToStr(num));
	msg += (" " + user.getNick() + " " + param + " ");

	switch (num)
	{
		case 1: //RPL_WELCOME
			msg += ":Welcome to the OSEF(tm) network, ";
			tmp = user.getSource();
			tmp.erase(0, 1);
			msg += tmp;
			break;
		case 2: //RPL_YOURHOST
			tmp = this->_servPtr->getSource();
			msg += ":Your host is ";
			msg += tmp;
			msg	+=	", runing ft_irc v0.1";
			break;
		case 3: //RPL_CREATED
			msg += "This server was created on ";
			msg += this->_servPtr->getCreationTime();
			break;
		case 4: //RPL_MYINFO
			msg += "xIOmtU";
			break;
		case 5: //RPL_ISUPPORT
			msg += "CASEMAPPING=ascii ";
			msg += ":are supported by this server";
			break;
		case 315: //RPL_ENDOFWHO
			msg += ":End of WHO list";
			break;
		case 321: //RPL_LISTSTART
			msg += "Channel :Users Name";
			break;
		case 322: //RPL_LIST
			break;
		case 323: //RPL_LISTEND
			msg += ":End of /LIST";
			break;
		case 324: //RPL_CHANNELMODEIS
			break;
		case 331: //RPL_NOTOPIC
			msg += ":No topic is set";
			break;
		case 341: //RPL_INVITING
			break;
		case 332: //RPL_TOPIC
			break;
		case 352: //RPL_WHOREPLY
			break;
		case 353: //RPL_NAMREPLY
			break;
		case 366: //RPL_ENDOFNAMES
			msg += ":End of /NAMES list.";
			break;
		case 367: //RPL_BANLIST
			break;
		case 368: //RPL_ENDOFBANLIST
			msg += ":End of channel ban list";
			break;
		case 372: //RPL_MOTD
			break;
		case 375: //RPL_MOTDSTART
			msg += "::- ";
			msg += this->_servPtr->getSource();
			msg += " Message of the day - ";
			break;
		case 376: //RPL_ENDOFMOTD
			msg += ":End of /MOTD command.";
			break;
		case 381: //RPL_YOUREOPER
			msg += ":You are now an IRC operator";
			break;
		case 401: //ERR_NOSUCHNICK
			msg += ":No such nick/channel";
			break;
		case 402: //ERR_NOSUCHSERVER
			msg += ":No such server";
			break;
		case 403: //ERR_NOSUCHCHANNEL
			msg += ":No such channel";
			break;
		case 404: //ERR_CANNOTSENDTOCHAN
			break;
		case 412: //ERR_NOTEXTTOSEND
			msg += ":No text to send";
			break;
		case 421: //ERR_UNKNOWNCOMMAND
			msg += ":Unknow command";
			break;
		case 422: //ERR_NOMOTD
			msg += ":MOTD File is missing";
			break;
		case 431: //ERR_NONICKNAMEGIVEN
			msg += ":No Nickname given";
			break;
		case 432: //ERR_ONEUSNICKNAME
			msg += ":Erroneus nickname";
			break;
		case 433: //ERR_NICKNAMEISUSE
			msg += ":Nickname is already in use";
			break;
		case 441: //ERR_USERNOTINCHANNEL
			msg + ":They aren't on that channel";
			break;
		case 442: //ERR_NOTONCHANNEL
			msg +=  ":You're not on that channel";
			break;
		case 443: //ERR_USERONCHANNEL
			msg += ":is already on channel";
			break;
		case 451: //ERR_NOTREGISTERED"
			msg += ":You have not registered";
			break;
		case 461: //ERR_NEEDMOREPARAMS
			msg += ":Not enough parameters";
			break;
		case 462: //ERR_ALREADYREGISTERED
			msg += "You may not reregister";
			break;
		case 464: //ERR_PASSWDMISMATCH
			msg += "Password incorrect";
			break;
		case 472: //ERR_CHANNELISFULL
			msg += ":Cannot join channel (+l)";
			break;
		case 473: //ERR_INVITEONLYCHAN
			msg += ":Cannot join channel (+i)";
			break;
		case 474: //ERR_BANNEDFROMCHAN
			msg += ":Cannot join channel (+b)";
			break;
		case 475: //ERR_BADCHANNELKEY
			msg += ":Cannot join channel (+k)";
			break;
		case 481: //ERR_NOPRILEGE
			msg += ":Permission Denied- You're not an IRC operator";
			break ;
		case 482: //ERR_CHANOPPRIVSNEEDED
			msg += ":You're not channel operator";
			break;
		case 491: //ERR_NOOPERHOST
			msg += ":No O-lines for your host";
			break;
		case 501: //ERR_UMODEUNKOWNFLAG
			msg += ":Unknown MODE flag";
			break;
		case 503: //ERR_USERSDONTMATCH
			msg += ":Cant change mode for other users";
			break;
		default:
			logger.log(ERROR) << num <<": numeric replie is not implemented yet";
			logger.nl();
			break;
	}
	return msg;
}
