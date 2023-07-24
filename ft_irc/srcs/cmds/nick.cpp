/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:01:55 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/17 11:29:34 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"
#include <ctype.h>

/*
NICK message

     Command: NICK
  Parameters: <nickname>

The NICK command is used to give the client a nickname or change the old one.

If the server receives a NICK command from a client where the desired nickname
is already in use on the network,
it should issue an ERR_NICKNAMEINUSE numeric and ignore the NICK command.

If the server does not accept the new nickname supplied by the client as valid
(for instance, due to containing invalid characters),
it should issue an ERR_ERRONEUSNICKNAME numeric and ignore the NICK command.

If the server does not receive the <nickname> parameter with the NICK command,
it should issue an ERR_NONICKNAMEGIVEN numeric and ignore the NICK command.

The NICK message may be sent from the server to clients to acknowledge their
NICK command was successful, and to inform other clients about the change
of nickname. In these cases, the <source> of the message will be the old
nickname [ [ "!" user ] "@" host ] of the user who is changing their nickname.

Numeric Replies:

    ERR_NONICKNAMEGIVEN (431)
    ERR_ERRONEUSNICKNAME (432)
    ERR_NICKNAMEINUSE (433)
    ERR_NICKCOLLISION (436)

Command Example:

  NICK Wiz                  ; Requesting the new nick "Wiz".

Message Examples:

  :WiZ NICK Kilroy          ; WiZ changed his nickname to Kilroy.

  :dan-!d@localhost NICK Mamoped
                            ; dan- changed his nickname to Mamoped.
*/

static bool	nickIsValid(std::string const & nick)
{
	for (int i = 0; nick[i]; i++)
	{
		if (!isalnum(nick[i]) && (nick[i] != '_' && nick[i] != '-'))
			return false;
		if (nick.size() > 9)
			return false;
	}
	return true;
}

void	CmdHandler::_onNICK(User & user, std::vector<std::string>& param)
{
	if (param.size() <= 1)
		user.addToSendMsg(this->_numReply(user, 431));
	else if (!nickIsValid(param[1]))
		user.addToSendMsg(this->_numReply(user, 432, param[1]));
	else if (this->_servPtr->userExist(param[1]))
		user.addToSendMsg(this->_numReply(user, 433, param[1]));
	else
	{
		std::string	oldSource = user.getSource();
		user.setNick(param[1]);
		if (user.getReg())
			user.addToSendMsg(oldSource + " NICK :" + user.getNick());
	}
}
