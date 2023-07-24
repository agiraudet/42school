/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:18:19 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/23 13:16:44 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"
#include "mode.hpp"
#include "utils.hpp"

/*
JOIN message

     Command: JOIN
  Parameters: <channel>{,<channel>} [<key>{,<key>}]
  Alt Params: 0

The JOIN command indicates that the client wants to join the given channel(s),
each channel using the given key for it. The server receiving the command checks
whether or not the client can join the given channel, and processes the request.
Servers MUST process the parameters of this command as lists on incoming
commands from clients, with the first <key> being used for the first <channel>,
the second <key> being used for the second <channel>, etc.

While a client is joined to a channel, they receive all relevant information
about that channel including the JOIN, PART, KICK, and MODE messages affecting
the channel. They receive all PRIVMSG and NOTICE messages sent to the channel,
and they also receive QUIT messages from other clients joined to the same
channel (to let them know those users have left the channel and the network).
This allows them to keep track of other channel members and channel modes.

If a client’s JOIN command to the server is successful, the server MUST send,
in this order:

    A JOIN message with the client as the message <source> and the channel they
	have joined as the first parameter of the message.
    The channel’s topic (with RPL_TOPIC (332) and optionally RPL_TOPICWHOTIME
	(333)), and no message if the channel does not have a topic.
    A list of users currently joined to the channel (with one or more
	RPL_NAMREPLY (353) numerics followed by a single RPL_ENDOFNAMES (366)
	numeric). These RPL_NAMREPLY messages sent by the server MUST include the
	requesting client that has just joined the channel.

The key, client limit , ban - exception, invite-only - exception, and other
(depending on server software) channel modes affect whether or not a given
client may join a channel. More information on each of these modes and how they
affect the JOIN command is available in their respective sections.

Servers MAY restrict the number of channels a client may be joined to at one
time. This limit SHOULD be defined in the CHANLIMIT RPL_ISUPPORT parameter. If
the client cannot join this channel because they would be over their limit, they
will receive an ERR_TOOMANYCHANNELS (405) reply and the command will fail.

Note that this command also accepts the special argument of ("0", 0x30) instead
of any of the usual parameters, which requests that the sending client leave all
channels they are currently connected to. The server will process this command
as though the client had sent a PART command for each channel they are a member
of.

This message may be sent from a server to a client to notify the client that
someone has joined a channel. In this case, the message <source> will be the
client who is joining, and <channel> will be the channel which that client has
joined. Servers SHOULD NOT send multiple channels in this message to clients,
and SHOULD distribute these multiple-channel JOIN messages as a series of
messages with a single channel name on each.

Numeric Replies:

    ERR_NEEDMOREPARAMS (461)
    ERR_NOSUCHCHANNEL (403)
    ERR_TOOMANYCHANNELS (405)
    ERR_BADCHANNELKEY (475)
    ERR_BANNEDFROMCHAN (474)
    ERR_CHANNELISFULL (471)
    ERR_INVITEONLYCHAN (473)
    RPL_TOPIC (332)
    RPL_TOPICWHOTIME (333)
    RPL_NAMREPLY (353)
    RPL_ENDOFNAMES (366)

Command Examples:

  JOIN #foobar                    ; join channel #foobar.

  JOIN &foo fubar                 ; join channel &foo using key "fubar".

  JOIN #foo,&bar fubar            ; join channel #foo using key "fubar"
                                  and &bar using no key.

  JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar".
                                  and channel #bar using key "foobar".

  JOIN #foo,#bar                  ; join channels #foo and #bar.

Message Examples:

  :WiZ JOIN #Twilight_zone        ; WiZ is joining the channel
                                  #Twilight_zone

  :dan-!d@localhost JOIN #test    ; dan- is joining the channel #test
*/

static void	joinUserChan(User & user, Chan & chan, CmdHandler & cmdH, Server * serv)
{
	std::string	noticeMsg = "";
	std::string usLst = "";

	chan.join(user);
	user.addToSendMsg(":" + user.getNick() + " JOIN " + chan.getName());
	if (chan.getTopic().size() > 0)
		cmdH.sendMsg(user, 332, chan.getName() + " :" + chan.getTopic());
	noticeMsg = user.getSource() + " JOIN " + chan.getName();
	chan.sendMsg(user.getId(), noticeMsg, serv->getUserMap());
	usLst += chan.getStatus();
	usLst += " " + chan.getName();
	usLst += " :" + chan.getUserLst(serv->getUserMap());
	cmdH.sendMsg(user, 353, usLst);
	cmdH.sendMsg(user, 366, chan.getName());
}

void	CmdHandler::_onJOIN(User & user, std::vector<std::string>& param)
{
	if (param.size() <= 1)
	{
		user.addToSendMsg(this->_numReply(user, 461));
		return ;
	}
	std::vector<std::string>	targetLst = ftSplit(param[1], ",");
	std::vector<std::string>	keyLst;
	size_t						ii = 0;
	if (param.size() >= 3)
		keyLst = ftSplit(param[2], ",");
	for (size_t i = 0; i < targetLst.size(); i++)
	{
		Chan & chan = this->_servPtr->getChan(targetLst[i]);
		if (chan.getMode() & CHMD_l && chan.isFull())
			user.addToSendMsg(this->_numReply(user, 471, targetLst[i]));
		else if (chan.getMode() & CHMD_i && !chan.userIsInv(user))
			user.addToSendMsg(this->_numReply(user, 473, targetLst[i]));
		else if (chan.userIsBan(user))
			user.addToSendMsg(this->_numReply(user, 474, targetLst[i]));
		else if (chan.getMode() & CHMD_k && !chan.keyIsCorrect(keyLst.size() > ii ? keyLst[ii++] : ""))
			user.addToSendMsg(this->_numReply(user, 475, targetLst[i]));
		else
			joinUserChan(user, this->_servPtr->getChan(targetLst[i]), *this, this->_servPtr);
	}
}
