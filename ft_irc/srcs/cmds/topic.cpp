#include "CmdHandler.hpp"
#include "Server.hpp"
#include "mode.hpp"

/*
TOPIC message

     Command: TOPIC
  Parameters: <channel> [<topic>]

	The TOPIC command is used to change or view the topic of the given channel. If <topic> is not given,
	 either RPL_TOPIC or RPL_NOTOPIC is returned specifying the current channel topic or lack of one. 
	 If <topic> is an empty string, the topic for the channel will be cleared.

	If the client sending this command is not joined to the given channel, 
	and tries to view its’ topic, the server MAY return the ERR_NOTONCHANNEL (442) numeric and have the command fail.

	If RPL_TOPIC is returned to the client sending this command, RPL_TOPICWHOTIME SHOULD also be sent to that client.

	If the protected topic mode is set on a channel, then clients MUST have appropriate channel permissions to modify the topic of that channel. 
	If a client does not have appropriate channel permissions and tries to change the topic, the ERR_CHANOPRIVSNEEDED (482) numeric is returned and the command will fail.

	If the topic of a channel is changed or cleared, every client in that channel
	 (including the author of the topic change) will receive a TOPIC command with the new topic
	  as argument (or an empty argument if the topic was cleared) alerting them to how the topic
	   has changed.

	Clients joining the channel in the future will receive a RPL_TOPIC numeric (or lack thereof) accordingly.

Numeric Replies:

    ERR_NEEDMOREPARAMS (461)
    ERR_NOSUCHCHANNEL (403)
    ERR_NOTONCHANNEL (442)
    ERR_CHANOPRIVSNEEDED (482)
    RPL_NOTOPIC (331)
    RPL_TOPIC (332)
    RPL_TOPICWHOTIME (333)

Command Examples:

  TOPIC #test :New topic          ; Setting the topic on "#test" to
                                  "New topic".

  TOPIC #test :                   ; Clearing the topic on "#test"

  TOPIC #test                     ; Checking the topic for "#test"

*/

void	CmdHandler::_onTOPIC(User & user, std::vector<std::string> & param)
{
	if (param.size() < 2)
		user.addToSendMsg(this->_numReply(user, 461));
	else if (!(this->_servPtr->chanExist(param[1])))
		user.addToSendMsg(this->_numReply(user, 403, param[1]));
	else
	{
		Chan &	chan = this->_servPtr->getChan(param[1]);
		if (param.size() == 2)
		{
			if (chan.getTopic().size() == 0)
				user.addToSendMsg(this->_numReply(user, 331));
			else
				user.addToSendMsg(this->_numReply(user, 332, ":" + chan.getTopic()));
			return ;
		}
		if (param.size() >= 3)
		{
			if (!(chan.userInChan(user.getId())))
			{
				user.addToSendMsg(this->_numReply(user, 442, param[1]));
				return;
			}
			char	userPfx = chan.getUserPfx(user.getId());
			if (chan.getMode() & CHMD_t && (userPfx != '@' && userPfx != '%'))
			{
				user.addToSendMsg(this->_numReply(user, 482, param[1]));
				return;
			}
			chan.setTopic(param[2]);
			std::string noticeMsg = user.getSource() + " TOPIC " + param[1] + " :" + param[2];
			chan.sendMsg(-1, noticeMsg, this->_servPtr->getUserMap());
		}
	}
}
