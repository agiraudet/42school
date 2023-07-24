/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:57:57 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/16 16:35:19 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"

/*
WHO message

     Command: WHO
  Parameters: <mask>

This command is used to query a list of users who match the provided mask. The
server will answer this command with zero, one or more RPL_WHOREPLY, and end the
list with RPL_ENDOFWHO.

The mask can be one of the following:

    A channel name, in which case the channel members are listed.
    An exact nickname, in which case a single user is returned.
    A mask pattern, in which case all visible users whose nickname matches are
	listed. Servers MAY match other user-specific values, such as the hostname,
	server, real name or username. Servers MAY not support mask patterns and
	return an empty list.

Visible users are users who aren’t invisible (user mode +i) and who don’t have a
common channel with the requesting client. Servers MAY filter or limit visible
users replies arbitrarily.

Numeric Replies:

    RPL_WHOREPLY (352)
    RPL_ENDOFWHO (315)
    ERR_NOSUCHSERVER (402)

See also:

    IRCv3 multi-prefix Extension
    WHOX

Examples

Command Examples:

  WHO emersion        ; request information on user "emersion"
  WHO #ircv3          ; list users in the "#ircv3" channel

Reply Examples:

  :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion
calcium.libera.chat emersion H :1 Simon Ser
  :calcium.libera.chat 315 dan emersion :End of WHO list
                                  ; Reply to WHO emersion

  :calcium.libera.chat 352 dan #ircv3 ~emersion sourcehut/staff/emersion
calcium.libera.chat emersion H :1 Simon Ser
  :calcium.libera.chat 352 dan #ircv3 ~val limnoria/val calcium.libera.chat val
H :1 Val
  :calcium.libera.chat 315 dan #ircv3 :End of WHO list
                                  ; Reply to WHO #ircv3
*/

static std::string	whoReplyFormat(Server * serv, std::string & userNick, std::string channel)
{
	std::string	pfx = "~&@%+";
	if (pfx.find(userNick[0]) != std::string::npos)
		userNick.erase(0, 1);
	User &		user = serv->getUser(userNick);
	std::string	ret = "";

	ret += (channel + " "
			+ user.getUsername() + " "
			+ user.getDomain() + " "
			+ serv->getSource() + " "
			+ user.getNick() + " "
			+ "H "
			+ ":0 "
			+ user.getRealName());
	return ret;
}

void	CmdHandler::_onWHO(User & user, std::vector<std::string>& param)
{
	std::string &	target = param[1];

	if ((target[0] == '#' || target[0] == '&') && this->_servPtr->chanExist(target))
	{
		Chan &						chan = this->_servPtr->getChan(target);
		std::string					whoMsg;
		std::vector<std::string>	userList;

		userList = ftSplit(chan.getUserLst(this->_servPtr->getUserMap()), " ");
		for (size_t i = 0; i < userList.size(); i++)
		{
			whoMsg = whoReplyFormat(this->_servPtr, userList[i], target);
			user.addToSendMsg(this->_numReply(user, 352, whoMsg));
		}
	}
	else
	{
		if (this->_servPtr->userExist(target))
			user.addToSendMsg(this->_numReply(user, 352, whoReplyFormat(this->_servPtr, target, "*")));
	}
	user.addToSendMsg(this->_numReply(user, 315, target));
}
