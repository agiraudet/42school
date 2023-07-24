/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:34:40 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/24 12:42:46 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"

/*
KICK message

      Command: KICK
   Parameters: <channel> <user> *( "," <user> ) [<comment>]

The KICK command can be used to request the forced removal of a user from a
channel. It causes the <user> to be removed from the <channel> by force. If no
comment is given, the server SHOULD use a default message instead.

The server MUST NOT send KICK messages with multiple users to clients. This is
necessary to maintain backward compatibility with existing client software.

Servers MAY limit the number of target users per KICK command via the TARGMAX
parameter of RPL_ISUPPORT, and silently drop targets if the number of targets
exceeds the limit.

Numeric Replies:

    ERR_NEEDMOREPARAMS (461)
    ERR_NOSUCHCHANNEL (403)
    ERR_CHANOPRIVSNEEDED (482)
    ERR_USERNOTINCHANNEL (441)
    ERR_NOTONCHANNEL (442)

Deprecated Numeric Reply:

    ERR_BADCHANMASK (476)

Examples:

   KICK #Finnish Matthew           ; Command to kick Matthew from
                                   #Finnish

   KICK &Melbourne Matthew         ; Command to kick Matthew from
                                   &Melbourne

   KICK #Finnish John :Speaking English
                                   ; Command to kick John from #Finnish
                                   using "Speaking English" as the
                                   reason (comment).

   :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
                                   ; KICK message on channel #Finnish
                                   from WiZ to remove John from channel
*/

void	CmdHandler::_onKICK(User & user, std::vector<std::string> & param)
{
	//param ["KICK", "param1", "p
	if (param.size() < 3)
		user.addToSendMsg(this->_numReply(user, 461));
	else if (!(this->_servPtr->chanExist(param[1])))
		user.addToSendMsg(this->_numReply(user, 403, param[1]));
	else
	{
		Chan &	chan = this->_servPtr->getChan(param[1]);

		if (!(chan.userInChan(user.getId())))
		{
			user.addToSendMsg(this->_numReply(user, 442, param[1]));
			return;
		}
		char	userPfx = chan.getUserPfx(user.getId());
		if (userPfx != '@' && userPfx != '%')
		{
			user.addToSendMsg(this->_numReply(user, 482, param[1]));
			return;
		}
		std::vector<std::string>	targetLst = ftSplit(param[2], ",");
		for (size_t i = 0; i < targetLst.size(); i++)
		{
			if (!(this->_servPtr->userExist(targetLst[i])))
			{
				user.addToSendMsg(this->_numReply(user, 441, targetLst[i]));
				continue ;
			}
			User & userToKick = this->_servPtr->getUser(targetLst[i]);
			if (!(chan.userInChan(user.getId())))
			{
				user.addToSendMsg(this->_numReply(user, 441, targetLst[i]));
				continue ;
			}
			std::string	noticeMsg = user.getSource() + " KICK " + param[1] + " " + userToKick.getNick();
			if (param.size() >= 4)
				noticeMsg += (" :" + param[3]);
			chan.sendMsg(-1, noticeMsg, this->_servPtr->getUserMap());
			chan.part(userToKick.getId());
			this->_servPtr->checkChan(chan);
		}
	}
}

