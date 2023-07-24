#include "CmdHandler.hpp"
#include "Server.hpp"
#include "mode.hpp"

/*
      Command: KILL
   Parameters: <nickname> <comment>

   The KILL message is used to cause a client-server connection to be
   closed by the server which has the actual connection.  KILL is used
   by servers when they encounter a duplicate entry in the list of valid
      nicknames and is used to remove both entries.  It is also available
   to operators.

   Clients which have automatic reconnect algorithms effectively make
   this command useless since the disconnection is only brief.  It does
   however break the flow of data and can be used to stop large amounts
   of being abused, any user may elect to receive KILL messages
   generated for others to keep an 'eye' on would be trouble spots.

   In an arena where nicknames are required to be globally unique at all
   times, KILL messages are sent whenever 'duplicates' are detected
   (that is an attempt to register two users with the same nickname) in
   the hope that both of them will disappear and only 1 reappear.

   The comment given must reflect the actual reason for the KILL.  For
   server-generated KILLs it usually is made up of details concerning
   the origins of the two conflicting nicknames.  For users it is left
   up to them to provide an adequate reason to satisfy others who see
   it.  To prevent/discourage fake KILLs from being generated to hide
   the identify of the KILLer, the comment also shows a 'kill-path'
   which is updated by each server it passes through, each prepending
   its name to the path.

   Numeric Replies:

           ERR_NOPRIVILEGES                ERR_NEEDMOREPARAMS
           ERR_NOSUCHNICK                  ERR_CANTKILLSERVER (ignoredbysubject)


   KILL David (csd.bu.edu <- tolsun.oulu.fi)
                                   ; Nickname collision between csd.bu.edu
                                   and tolson.oulu.fi


   NOTE:
   It is recommended that only Operators be allowed to kill other users
   with KILL message.  In an ideal world not even operators would need
   to do this and it would be left to servers to deal with. */

void	CmdHandler::_onKILL(User & user, std::vector<std::string> & param)
{
	//param ["KICK", "param1", "p
	if (param.size() < 3)
		user.addToSendMsg(this->_numReply(user, 461));
    else if (!(this->_servPtr->userExist(param[1])))
		this->sendMsg(user, 401, param[1]);
    else if (!(user.getMode() & USMD_O || user.getMode() & USMD_o))
        user.addToSendMsg(this->_numReply(user, 481));
	else
		this->_servPtr->killUser(this->_servPtr->getUser(param[1]), param[2], user.getSource());
}
