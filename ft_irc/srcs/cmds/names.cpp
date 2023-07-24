/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:35:46 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/23 11:38:22 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"

/*
NAMES message

     Command: NAMES
  Parameters: <channel>{,<channel>}

The NAMES command is used to view the nicknames joined to a channel and their
channel membership prefixes. The param of this command is a list of channel
names, delimited by a comma (",", 0x2C) character.

The channel names are evaluated one-by-one. For each channel that exists and
they are able to see the users in, the server returns one of more RPL_NAMREPLY
numerics containing the users joined to the channel and a single RPL_ENDOFNAMES
numeric. If the channel name is invalid or the channel does not exist, one
RPL_ENDOFNAMES numeric containing the given channel name should be returned. If
the given channel has the secret channel mode set and the user is not joined to
that channel, one RPL_ENDOFNAMES numeric is returned. Users with the invisible
user mode set are not shown in channel responses unless the requesting client is
also joined to that channel.

Servers MAY allow more than one target channel. They can advertise the maximum
the number of target users per NAMES command via the TARGMAX RPL_ISUPPORT
parameter.

Numeric Replies:

    RPL_NAMREPLY (353)
    RPL_ENDOFNAMES (366)

Command Examples:

  NAMES #twilight_zone,#42        ; List all visible users on
                                  "#twilight_zone" and "#42".

  NAMES                           ; Attempt to list all visible users on
                                  the network, which SHOULD be responded to
                                  as specified above.
*/

void	CmdHandler::_onNAMES(User & user, std::vector<std::string> & param)
{
	if (param.size() <= 1)
	{
		std::string usList = ":" + this->_servPtr->getUserLst();
		user.addToSendMsg(this->_numReply(user, 353, usList));
		user.addToSendMsg(this->_numReply(user, 366));
	}
	else
	{
		std::vector<std::string> targetLst = ftSplit(param[1], ",");
		for (size_t i = 0; i < targetLst.size(); i++)
		{
			if (this->_servPtr->chanExist(targetLst[i]))
			{
				Chan & chan = this->_servPtr->getChan(targetLst[i]);
				std::string usList = cToStr(chan.getStatus()) + " " + targetLst[i] +" :" + chan.getUserLst(this->_servPtr->getUserMap());
				user.addToSendMsg(this->_numReply(user, 353, usList));
			}
			user.addToSendMsg(this->_numReply(user, 366, targetLst[i]));
		}
	}
}
