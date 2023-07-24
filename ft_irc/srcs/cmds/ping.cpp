/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:56:12 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/20 19:33:01 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"

/*
PING message

     Command: PING
  Parameters: <token>

The PING command is sent by either clients or servers to check the other side
of the connection is still connected and/or to check for connection latency,
at the application layer.

The <token> may be any non-empty string.

When receiving a PING message, clients or servers must reply to it with
a PONG message with the same <token> value. This allows either to match PONG
with the PING they reply to, for example to compute latency.

Clients should not send PING during connection registration,
though servers may accept it.
Servers may send PING during connection registration
and clients must reply to them.

Older versions of the protocol gave specific semantics to the <token>
and allowed an extra parameter;
but these features are not consistently implemented and should not be relied on.
Instead, the <token> should be treated as an opaque value by the receiver.

Numeric Replies:

    ERR_NEEDMOREPARAMS (461)
    ERR_NOORIGIN (409)
*/

void	CmdHandler::_onPING(User & user, std::vector<std::string>& param)
{
	std::string&	arg = param[1];

	std::string	msg = ":" + this->_servPtr->getSource() + " PONG ";
	if (arg.size() > 0)
		msg += arg;
	user.addToSendMsg(msg);
}
