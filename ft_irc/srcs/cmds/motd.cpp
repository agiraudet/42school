/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:47:08 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/16 18:27:35 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"
#include <fstream>

/*
MOTD message

     Command: MOTD
  Parameters: [<target>]

The MOTD command is used to get the “Message of the Day” of the given server.
If <target> is not given, the MOTD of the server the client is connected to
should be returned.

If <target> is a server, the MOTD for that server is requested. If <target> is
given and a matching server cannot be found, the server will respond with the
ERR_NOSUCHSERVER numeric and the command will fail.

If the MOTD can be found, one RPL_MOTDSTART numeric is returned, followed by one
or more RPL_MOTD numeric, then one RPL_ENDOFMOTD numeric.

If the MOTD does not exist or could not be found, the ERR_NOMOTD numeric is
returned.

Numeric Replies:

    ERR_NOSUCHSERVER (402)
    ERR_NOMOTD (422)
    RPL_MOTDSTART (375)
    RPL_MOTD (372)
    RPL_ENDOFMOTD (376)
*/

void	CmdHandler::_onMOTD(User & user, std::vector<std::string>& param)
{
	std::ifstream motdFile;
	std::string		line;

	if (param.size() > 1 && false)
	{
		user.addToSendMsg(this->_numReply(user, 402, param[1]));
		return;
	}
	motdFile.open(".motd");
	if (!motdFile.is_open())
	{
		user.addToSendMsg(this->_numReply(user, 422));
		return ;
	}
	user.addToSendMsg(this->_numReply(user, 375));
	while (getline(motdFile, line))
	{
		while (line.size() > 80)
		{
			user.addToSendMsg(this->_numReply(user, 372, line.substr(0, 80)));
			line.erase(0, 80);
		}
		if (line.size())
			user.addToSendMsg(this->_numReply(user, 372, line.substr(0, 80)));
	}
	motdFile.close();
	user.addToSendMsg(this->_numReply(user, 376));
}
