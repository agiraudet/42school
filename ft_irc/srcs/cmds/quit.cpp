/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:15:00 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/21 13:28:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"

/*
QUIT message

    Command: QUIT
 Parameters: [<reason>]

The QUIT command is used to terminate a client’s connection to the server.
The server acknowledges this by replying with an ERROR message and closing the
connection to the client.

This message may also be sent from the server to a client to show that a client
has exited from the network. This is typically only dispatched to clients that
share a channel with the exiting user. When the QUIT message is sent to clients,
<source> represents the client that has exited the network.

When connections are terminated by a client-sent QUIT command, servers SHOULD
prepend <reason> with the ASCII string "Quit: " when sending QUIT messages to
other clients, to represent that this user terminated the connection themselves.
This applies even if <reason> is empty, in which case the reason sent to other
clients SHOULD be just this "Quit: " string. However, clients SHOULD NOT change
behaviour based on the prefix of QUIT message reasons, as this is not required
behaviour from servers.

When a netsplit (the disconnecting of two servers) occurs, a QUIT message is
generated for each client that has exited the network, distributed in the same
way as ordinary QUIT messages. The <reason> on these QUIT messages SHOULD be
composed of the names of the two servers involved, separated by a
SPACE (' ', 0x20). The first name is that of the server which is still connected
and the second name is that of the server which has become disconnected.
If servers wish to hide or obscure the names of the servers involved,
the <reason> on these messages MAY also be the literal ASCII
string "*.net *.split" (i.e. the two server names are replaced with "*.net" and
"*.split"). Software that implements the IRCv3 batch Extension should also look
at the netsplit and netjoin batch types.

If a client connection is closed without the client issuing a QUIT command to
the server, the server MUST distribute a QUIT message to other clients informing
them of this, distributed in the same was an ordinary QUIT message. Servers MUST
fill <reason> with a message reflecting the nature of the event which caused it
to happen. For instance, "Ping timeout: 120 seconds", "Excess Flood", and "Too
many connections from this IP" are examples of relevant reasons for closing or
for a connection with a client to have been closed.

Numeric Replies:

    None

Command Example:

  QUIT :Gone to have lunch         ; Client exiting from the network

Message Example:

  :dan-!d@localhost QUIT :Quit: Bye for now!
                                   ; dan- is exiting the network with
                                   the message: "Quit: Bye for now!"
*/

void	CmdHandler::_onQUIT(User & user, std::vector<std::string>& param)
{
	std::string	reason = "";
	if (param.size() >= 2)
		reason = param[1];

	std::map<std::string, Chan>::iterator	it = this->_servPtr->getChanMap().begin();
	std::map<std::string, Chan>::iterator	ite = this->_servPtr->getChanMap().end();

	std::string quitNotice = user.getSource() + " QUIT :Quit: " + reason;
	for (; it != ite; it++)
	{
		if (it->second.userInChan(user.getId()))
			it->second.sendMsg(user.getId(), quitNotice, this->_servPtr->getUserMap());
	}
	user.addToSendMsg("ERROR " + reason);


}
