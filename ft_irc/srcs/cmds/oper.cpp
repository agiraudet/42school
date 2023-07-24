/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:18:43 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/21 11:09:01 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"
#include "mode.hpp"

/*
OPER message

     Command: OPER
  Parameters: <name> <password>

The OPER command is used by a normal user to obtain IRC operator privileges.
Both parameters are required for the command to be successful.

If the client does not send the correct password for the given name, the server
replies with an ERR_PASSWDMISMATCH message and the request is not successful.

If the client is not connecting from a valid host for the given name, the server
replies with an ERR_NOOPERHOST message and the request is not successful.

If the supplied name and password are both correct, and the user is connecting
from a valid host, the RPL_YOUREOPER message is sent to the user. The user will
also receive a MODE message indicating their new user modes, and other messages
may be sent.

The <name> specified by this command is separate to the accounts specified by
SASL authentication, and is generally stored in the IRCd configuration.

Numeric Replies:

    ERR_NEEDMOREPARAMS (461)
    ERR_PASSWDMISMATCH (464)
    ERR_NOOPERHOST (491)
    RPL_YOUREOPER (381)

Command Example:

  OPER foo bar                ; Attempt to register as an operator
                              using a name of "foo" and the password "bar".
*/

void	CmdHandler::_onOPER(User & user, std::vector<std::string>& param)
{
	if (param.size() < 3)
	{
		user.addToSendMsg(this->_numReply(user, 461));
		return;
	}
	switch (this->_servPtr->checkOp(param[1], param[2], user.getDomain()))
	{
		case OP_ERRPASS:
			user.addToSendMsg(this->_numReply(user, 464));
			break;
		case OP_ERRNAME:
			user.addToSendMsg(this->_numReply(user, 464));
			break;
		case OP_ERRHOST:
			user.addToSendMsg(this->_numReply(user, 491));
			break;
		default:
			user.addToSendMsg(this->_numReply(user, 381));
			user.addMode(USMD_o);
			user.addToSendMsg(":" + user.getSource() + " MODE " + user.getNick() + " :" + user.getStrMode());
			break;
	}
}
