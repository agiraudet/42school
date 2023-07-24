/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:27:32 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/16 17:10:49 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "CoHandler.hpp"
# include "CmdHandler.hpp"
# include "User.hpp"
# include "Chan.hpp"
# include <iostream>
# include <map>

# define PING_TO 60
# define PING_TM 30

enum	e_opInfo
{
	OP_ERRNAME,
	OP_ERRHOST,
	OP_ERRPASS,
	OP_OK
};

class	Server
{
	public:

		Server(void);
		Server(std::string port);
		Server(std::string port, std::string pass);
		Server(Server const & src);
		~Server(void);
		
		Server & operator=(Server const & rhs);

		CoHandler	coHandler;

		std::string						getSource(void) const;
		void							setPassword(std::string pass);
		std::string						getPassword(void) const;
		void							run(void);
		void							addUser(int id);
		void							delUser(int id);
		void							delUser(int id, int cause);
		std::string						getUserLst(void) const;
		User &							getUser(int id);
		User &							getUser(std::string nick);
		bool							userExist(std::string nick) const;
		bool							userExist(int id) const;
		std::map<int, User> &			getUserMap(void);
		std::map<std::string, Chan> &	getChanMap(void);
		Chan &							getChan(std::string chanName);
		bool							chanExist(std::string chanName);
		void							userRecvMsg(int id, const char *msg, int nbytes);
		void							userSendMsg(int userId);
		int								userHasMsg(int userId, short dir);
		void							processMsg(User & user);
		e_opInfo						checkOp(std::string const & name, std::string const & pass, std::string const host) const;
		void							checkChan(Chan & chan);
		void							killUser(User & user, std::string reason, std::string src);
		void							checkTO(void);
		std::string						getCreationTime(void) const;

	private:

		CmdHandler													_cmdHandler;
		std::map<int, User>											_userMap;
		std::map<std::string, Chan>									_chanMap;
		std::map<std::string, std::pair<std::string, std::string> >	_opMap;
		std::string													_passwd;
		std::string													_source;
		std::string													_creationTime;

		void	_listUser(void);
		void	_loadOpMap(void);
		bool	_checkMsgError(std::string & msg);
		void	_delChan(std::string const & chanName);
		void	_setSource(std::string source);
		void	_setSource(void);
		void	_setCreationTime(void);

};

#endif
