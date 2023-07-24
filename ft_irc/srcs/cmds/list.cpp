/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:03:59 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/24 11:44:36 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"
#include "mode.hpp"
#include <sstream>

/*
LIST message


      Command: LIST
   Parameters: [<channel>{,<channel>} [<server>]]

   The list message is used to list channels and their topics.  If  the
   <channel>  parameter  is  used,  only  the  status  of  that  channel
   is displayed.  Private  channels  are  listed  (without  their
   topics)  as channel "Prv" unless the client generating the query is
   actually on that channel.  Likewise, secret channels are not listed

   at  all  unless  the client is a member of the channel in question.

   Numeric Replies:

           ERR_NOSUCHSERVER (402)
		   RPL_LISTSTART (321)
           RPL_LIST (322)
		   RPL_LISTEND (323)

   Examples:

   LIST                            ; List all channels.

   LIST #twilight_zone,#42         ; List channels #twilight_zone and #42
*/

static	std::string	listThisChan(Chan const & chan, User const & user)
{
	std::stringstream	ss;

	if (chan.getMode() & CHMD_p && !(chan.userInChan(user.getId())))
		ss << "Prv" << chan.getNbUser() << ":";
	else
		ss << chan.getName() << " " << chan.getNbUser() << " :" << chan.getTopic();
	return ss.str();
}

void	CmdHandler::_onLIST(User & user, std::vector<std::string> & param)
{
	user.addToSendMsg(this->_numReply(user, 321));
	if (param.size() == 1)
	{
		std::map<std::string, Chan>::const_iterator	it = this->_servPtr->getChanMap().begin();
		std::map<std::string, Chan>::const_iterator	ite = this->_servPtr->getChanMap().end();

		for (; it != ite; it++)
		{
			if (!(it->second.getMode() & CHMD_s) || it->second.userInChan(user.getId()))
				user.addToSendMsg(this->_numReply(user, 322, listThisChan(it->second, user)));
		}
	}
	else
	{
		std::vector<std::string>	targetLst = ftSplit(param[1], ",");
		
		for (size_t i = 0; i < targetLst.size(); i++)
		{
			if (this->_servPtr->chanExist(targetLst[i]))
			{
				Chan & chan = this->_servPtr->getChan(targetLst[i]);
				if (!(chan.getMode() & CHMD_s) || chan.userInChan(user.getId()))
					user.addToSendMsg(this->_numReply(user, 322, listThisChan(chan, user)));
			}
		}
	}
	user.addToSendMsg(this->_numReply(user, 323));
}
