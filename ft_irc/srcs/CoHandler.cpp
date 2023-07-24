/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CoHandler.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:31:28 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/17 10:20:15 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "CoHandler.hpp"
#include "Server.hpp"
#include "utils.hpp"

CoHandler::CoHandler(void)
:_port(DEFAULT_PORT), _pollTO(POLL_TO), _listener(-1), _servPtr(NULL)
{
}

CoHandler::CoHandler(Server * serv)
:_port(DEFAULT_PORT), _pollTO(POLL_TO), _listener(-1), _servPtr(serv)
{
}

CoHandler::CoHandler(CoHandler const & src)
{
	*this = src;
}

CoHandler::~CoHandler(void)
{
}

CoHandler & CoHandler::operator=(CoHandler const & rhs)
{
	this->_port = rhs._port;
	this->_pfds = rhs._pfds;
	this->_pollTO = rhs._pollTO;
	this->_listener = rhs._listener;
	return *this;
}

void	CoHandler::setPort(std::string const port)
{
	this->_port = port;
}

void	CoHandler::_createListener(void)
{
	struct addrinfo hints, *ai, *p;
	int	yes = 1;
	int	rv;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	rv = getaddrinfo(NULL, this->_port.c_str(), &hints, &ai);
	if (rv != 0)
		throw CoHandler::SocketError(rv);
	for (p = ai; p != NULL; p = p->ai_next)
	{
		this->_listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (this->_listener < 0)
			continue;
		if (setsockopt(this->_listener, SOL_SOCKET,SO_REUSEADDR, &yes, sizeof(int)) != 0)
		{
			close(this->_listener);
			throw CoHandler::ListenerCreationFailed();
		}
		if (bind(this->_listener, p->ai_addr, p->ai_addrlen) < 0)
		{
			close(this->_listener);
			continue ;
		}
		break ;
	}
	freeaddrinfo(ai);
	if (p == NULL)
		throw CoHandler::ListenerCreationFailed();
	if (listen(this->_listener, 10) == -1)
		throw CoHandler::ListenerCreationFailed();
	this->_addToPfds(this->_listener, POLLIN);

	logger.log(NONE) << "[Co] Listening on 0.0.0.0:" << this->_port;
	logger.nl();
}

void	CoHandler::_addToPfds(int newFd, short events)
{
	struct pollfd	newPollFd;

	newPollFd.fd = newFd;
	newPollFd.events = events;
	this->_pfds.push_back(newPollFd);
}

void	CoHandler::_acceptCo(void)
{
	struct sockaddr_storage	remoteAddr;
	socklen_t				addrLen = sizeof(remoteAddr);

	int newCoFd = accept(this->_listener, (struct sockaddr *)&remoteAddr, &addrLen);
	if (newCoFd == -1)
	{
		logger.log(ERROR) << "[Co] Error on accept(): " << strerror(errno);
		logger.nl();
	}
	else
	{
		logger.log(INFO) << "[Co] Accepted connection from: " << IpToStr(remoteAddr);
		logger.nl();
		logger.log(DEBUG) << "[Co] NewCo is on socket " << newCoFd;
		logger.nl();
		this->_addToPfds(newCoFd, POLLIN);
		this->_servPtr->addUser(newCoFd);
	}
}

void	CoHandler::_closeCo(struct pollfd & pfd, int cause)
{
	if (cause < 0)
	{
		std::string	err = strerror(errno);
		logger.log(ERROR) << "[Co] Closing socket " << pfd.fd << ": " << err;
		logger.nl();
	}
	else if (cause == 0)
	{
		logger.log(WARN) << "[Co] Socket " << pfd.fd << " closed the connection.";
		logger.nl();
	}
	else
	{
		logger.log(WARN) << "[Co] Closing socket " << pfd.fd;
		logger.nl();
	}
	close(pfd.fd);
	std::vector<struct pollfd>::iterator it = this->_pfds.begin();
	while ((*it).fd != pfd.fd)
		it++;
	this->_servPtr->delUser((*it).fd, cause);
	this->_pfds.erase(it);
}

void	CoHandler::killCo(int userId)
{
	nfds_t	nfds = this->_pfds.size();
	for (int i = 0; i < static_cast<int>(nfds); i++)
	{
		if (this->_pfds[i].fd == userId)
		{
			this->_closeCo(this->_pfds[i], 1);
			return ;
		}
	}
}

void	CoHandler::_readFromClient(struct pollfd & pfd)
{
	char	buf[1024];
	int		nbytes;

	nbytes = recv(pfd.fd, buf, sizeof(buf), 0);
	if (nbytes <= 0)
		this->_closeCo(pfd, nbytes);
	else
	{
		logger.log(DEBUG) << "[Co] Received " << nbytes
			<< " bytes from socket " << pfd.fd << ":";
		logger.nl();
		debugPrintMsgRAW(buf, nbytes);
		this->_servPtr->userRecvMsg(pfd.fd, buf, nbytes);
	}
}

bool	CoHandler::_msgIsKillCmd(std::string const & msg) const
{
	std::string	keyWord = "KILL";
	size_t		i = 0;

	while (msg[i] == ' ')
		i++;
	if (msg[i] == ':')
	{
		while (msg[i] != ' ')
			i++;
		i++;
	}
	if (msg.compare(i, keyWord.size(), keyWord) == 0)
		return true;
	return false;
}

void	CoHandler::sendToClient(int id, std::string const & msg)
{
//	std::string tmp = msg + "\x0d\x0a";
	std::string tmp = msg;

	int			nbytes;

	nbytes = send(id, tmp.c_str(), tmp.size(), 0);
	logger.log(DEBUG) << "[Co] Send to socket " << id << ":";
	logger.nl();
	debugPrintMsgRAW(msg.c_str(), msg.size());
	if (nbytes < 0)
	{
		for (size_t i = 0; i < this->_pfds.size(); i++)
		{
			if (this->_pfds[i].fd == id)
			{
				this->_closeCo(this->_pfds[i], nbytes);
				break;
			}
		}
	}
	else if (this->_msgIsKillCmd(msg))
	{
		logger.log(WARN) << "[Co] Socket " << id << "have to be killed";
		logger.nl();
		this->killCo(id);
	}
}

void	CoHandler::_onPollEventIn(struct pollfd & pfd)
{
	logger.log(DEBUG) << "[Co] PollEvent on socket " << pfd.fd;
	logger.nl();
	if (pfd.fd == this->_listener)
		this->_acceptCo();
	else
		this->_readFromClient(pfd);
}

void	CoHandler::_onPollEventOut(struct pollfd & pfd)
{
	if (pfd.fd != this->_listener)
		this->_servPtr->userSendMsg(pfd.fd);
}

void	CoHandler::_setPfdsMode(void)
{
	for (std::vector<struct pollfd>::iterator it = this->_pfds.begin();
			it != this->_pfds.end(); it++)
	{
		if ((*it).fd != this->_listener)
		{
			if (this->_servPtr->userHasMsg((*it).fd, OUT) && (*it).fd != this->_listener)
				(*it).events = POLLOUT;
			else
				(*it).events = POLLIN;
		}
	}
}

void	CoHandler::_closeAllCo(void)
{
	std::vector<struct pollfd>::iterator	it = this->_pfds.begin();

	for (; it != this->_pfds.end();)
	{
		this->_closeCo(*it, 1);
		it = this->_pfds.begin();
	}
}

void	CoHandler::start(void)
{
	if (this->_listener == -1)
	{
		try
		{
			this->_createListener();
		}
		catch (std::exception & e)
		{
			logger.log(ERROR) << "Couldn't create listener: " << e.what();
			logger.nl();
			return;
		}
	}
	for (;;)
	{
		this->_setPfdsMode();
		nfds_t	nfds = this->_pfds.size();
		int	pollCount = poll(&(this->_pfds[0]), nfds, this->_pollTO);
		if (pollCount == -1)
			continue ;
		for (int i = 0; i < static_cast<int>(nfds); i++)
		{
			if (this->_pfds[i].fd != -1)
			{
				if (this->_pfds[i].revents & POLLIN)
					this->_onPollEventIn(this->_pfds[i]);
				if (this->_pfds[i].revents & POLLOUT)
					this->_onPollEventOut(this->_pfds[i]);
			}
		}
		this->_servPtr->checkTO();
		if (quitCheck(0) != 0)
		{
			this->_closeAllCo();
			break ;
		}
	}
}
