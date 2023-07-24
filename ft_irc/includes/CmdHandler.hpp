/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CmdHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:44:38 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/16 18:12:56 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDHANDLER_HPP
# define CMDHANDLER_HPP

# include "User.hpp"
# include <iostream>
# include <string>
# include <map>
# include <vector>

class	Server;

class	CmdHandler
{
	public:

		CmdHandler(Server * servPtr);
		CmdHandler(CmdHandler const & src);
		~CmdHandler(void);
		
		CmdHandler & operator=(CmdHandler const & rhs);

		Server 	*	getServ(void) const;
		void		onMsg(std::string const & msg, User & user);
		void		sendMsg(User & user, int num);
		void		sendMsg(User & user, int num, std::string param);
		void		sendMsg(User & user, std::string msg);

	private:

		typedef	void(CmdHandler::*t_cmdFct)(User &, std::vector<std::string>&);

		Server *						_servPtr;
		std::map<std::string, t_cmdFct>	_cmdMap;

		CmdHandler(void);
		
		std::string	_numToStr(int num);
		std::string	_numReply(User & user, int num, std::string param);
		std::string	_numReply(User & user, int num);

		void		_onNICK(User & user, std::vector<std::string>& param);
		void		_onPING(User & user, std::vector<std::string>& param);
		void		_onUSER(User & user, std::vector<std::string>& param);
		void		_onPASS(User & user, std::vector<std::string>& param);
		void		_onQUIT(User & user, std::vector<std::string>& param);
		void		_onJOIN(User & user, std::vector<std::string>& param);
		void		_onPRIVMSG(User & user, std::vector<std::string>& param);
		void		_onMODE(User & user, std::vector<std::string>& param);
		void		_onOPER(User & user, std::vector<std::string>& param);
		void		_onWHO(User & user, std::vector<std::string>& param);
		void		_onPART(User & user, std::vector<std::string>& param);
		void		_onNOTICE(User & user, std::vector<std::string>& param);
		void		_onKICK(User & user, std::vector<std::string>& param);
		void		_onTOPIC(User & user, std::vector<std::string> & param);
		void		_onNAMES(User & user, std::vector<std::string> & param);
		void		_onINVITE(User & user, std::vector<std::string> & param);
		void		_onLIST(User & user, std::vector<std::string> & param);
		void		_onPONG(User & user, std::vector<std::string> & param);
		void		_onMOTD(User & user, std::vector<std::string> & param);
		void		_onKILL(User & user, std::vector<std::string> & param);
};
#endif
