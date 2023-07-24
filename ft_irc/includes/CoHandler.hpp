/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CoHandler.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:30:28 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/16 16:21:04 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CoHandler_HPP
# define CoHandler_HPP

# include <iostream>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <poll.h>
# include <vector>
# include <string>
# include <algorithm>
# include "utils.hpp"
# include <errno.h>

# define DEFAULT_PORT "6667"
# define POLL_TO 600

class	Server;

class	CoHandler
{
	public:

		CoHandler(Server * serv);
		CoHandler(CoHandler const & src);
		~CoHandler(void);
		
		CoHandler & operator=(CoHandler const & rhs);

		void	start(void);
		void	setPort(std::string const port);
		void	sendToClient(int id, std::string const & msg);
		void	killCo(int userId);

		class	ListenerCreationFailed : public std::exception
		{
			public :
				virtual const char * what() const throw()
				{
					return (strerror(errno));
				}
		};

		class	SocketError : public std::exception
		{
			public :
				int	errcode;

				SocketError(void)
				: errcode(0) {}
				SocketError(int code)
				: errcode(code) {}
				virtual const char * what() const throw()
				{
					return (gai_strerror(this->errcode));
				}
		};

	private:

		std::string					_port;
		int							_pollTO;
		std::vector<struct pollfd>	_pfds;
		int							_listener;
		Server *					_servPtr;

		CoHandler(void);

		void	_createListener(void);
		void	_addToPfds(int newfd, short events);
		void	_setPfdsMode(void);
		void	_readFromClient(struct pollfd & pfd);
		void	_onPollEventIn(struct pollfd & pfd);
		void	_onPollEventOut(struct pollfd & pfd);
		void	_acceptCo(void);
		void	_closeCo(struct pollfd & pfd, int cause);
		void	_closeAllCo(void);
		bool	_msgIsKillCmd(std::string const & msg) const;
};
#endif
