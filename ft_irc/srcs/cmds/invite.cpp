/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 13:20:17 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/23 13:58:52 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"
#include "mode.hpp"

/*
INVITE message

     Command: INVITE
  Parameters: <nickname> <channel>

The INVITE command is used to invite a user to a channel. The parameter
<nickname> is the nickname of the person to be invited to the target channel
<channel>.

The target channel SHOULD exist (at least one user is on it). Otherwise, the
erver SHOULD reject the command with the ERR_NOSUCHCHANNEL numeric.

Only members of the channel are allowed to invite other users. Otherwise, the
server MUST reject the command with the ERR_NOTONCHANNEL numeric.

Servers MAY reject the command with the ERR_CHANOPRIVSNEEDED numeric. In
particular, they SHOULD reject it when the channel has invite-only mode set, and
the user is not a channel operator.

If the user is already on the target channel, the server MUST reject the command
with the ERR_USERONCHANNEL numeric.

When the invite is successful, the server MUST send a RPL_INVITING numeric to
the command issuer, and an INVITE message, with the issuer as <source>, to the
target user. Other channel members SHOULD NOT be notified.

Numeric Replies:

    RPL_INVITING (341)
    ERR_NEEDMOREPARAMS (461)
    ERR_NOSUCHCHANNEL (403)
    ERR_NOTONCHANNEL (442)
    ERR_CHANOPRIVSNEEDED (482)
    ERR_USERONCHANNEL (443)

Command Examples:

  INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar

Message Examples:

  :dan-!d@localhost INVITE Wiz #test    ; dan- has invited Wiz
                                        to the channel #test
*/

void	CmdHandler::_onINVITE(User & user, std::vector<std::string> & param)
{
	if (param.size() < 3)
		user.addToSendMsg(this->_numReply(user, 461));
	else if (!(this->_servPtr->userExist(param[1])))
		user.addToSendMsg(this->_numReply(user, 401, param[1]));
	else if (!(this->_servPtr->chanExist(param[2])))
		user.addToSendMsg(this->_numReply(user, 403, param[2]));
	else
	{
		Chan & chan = this->_servPtr->getChan(param[2]);
		if (!(chan.userInChan(user.getId())))
			user.addToSendMsg(this->_numReply(user, 442, chan.getName()));
		else if (chan.getMode() & CHMD_i && !(chan.userIsHalfOp(user.getId())))
			user.addToSendMsg(this->_numReply(user, 482, chan.getName()));
		else
		{
			User &		userTo = this->_servPtr->getUser(param[1]);
			std::string	msg = userTo.getNick() + " " + chan.getName();
			if (chan.userInChan(userTo.getId()))
				user.addToSendMsg(this->_numReply(user, 443, msg));
			else
			{
				chan.addInv(userTo.getNick());
				user.addToSendMsg(this->_numReply(user, 341, msg));
				userTo.addToSendMsg(user.getSource() + " INVITE " + msg);
			}
		}
	}
}
