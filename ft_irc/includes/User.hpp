/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:20:33 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/24 16:19:15 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string>
# include <queue>

# define IN 1
# define OUT 0

class	User
{
	public:

		User(void);
		User(int id);
		User(User const & src);
		~User(void);
		
		User & operator=(User const & rhs);

		std::string	getSource(void) const;
		short		getMode(void) const;
		void		setMode(short mode);
		void		addMode(short mode);
		void		delMode(short mode);
		std::string getStrMode(void) const;
		std::string getNick(void) const;
		void		setNick(std::string nick);
		std::string	getRealName(void) const;
		void		setRealName(std::string realName);
		std::string	getDomain(void) const;
		void		setDomain(std::string domain);
		std::string	getUsername(void) const;
		void		setUsername(std::string username);
		int			getId(void) const;
		bool		getReg(void) const;
		void		setReg(bool val);
		bool		getPasswd(void) const;
		void		setPasswd(bool val);
		void		recvMsg(const char *msg, int nbytes);
		void		addToSendMsg(std::string msg);
		std::string	getMsg(short dir);
		std::string	getMsgOut(void);
		int			getNbMsg(short dir);
		void		setAwaitingPong(bool awaiting);
		bool		getAwaitingPong(void) const;
		void		setLastPing(time_t ping);
		time_t		getLastPing(void) const;
		time_t		getLastRcv(void) const;

	private:

		int const				_id;
		std::string				_nick;
		std::string				_realName;
		std::string				_domain;
		std::string				_username;
		short					_mode;
		bool					_registered;
		bool					_passwd;
		std::queue<std::string>	_msgIn;
		std::queue<std::string>	_msgOut;
		std::string				_bufIn;
		time_t					_lastRcv;
		time_t					_lastPing;
		bool					_awaitingPong;

};
#endif
