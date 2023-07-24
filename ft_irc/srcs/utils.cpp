/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:44:57 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/17 12:24:35 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "Logger.hpp"
#include <sstream>
#include <cstring>

void	*getInAddr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

std::string	IpToStr(struct sockaddr_storage const & ss)
{
	std::stringstream	strs;
	char				ssIP[INET6_ADDRSTRLEN];

	strs << inet_ntop(ss.ss_family, getInAddr((struct sockaddr *)&ss),
			ssIP, INET6_ADDRSTRLEN);
	return strs.str();
}

std::vector<std::string>	ftSplit(std::string const src, std::string sep)
{
	std::vector<std::string>	res;
	std::string					token;
	size_t						posStart = 0;
	size_t						posEnd;
	size_t						sepLen = sep.size();

	while ((posEnd = src.find(sep, posStart)) != std::string::npos)
	{
		token = src.substr(posStart, posEnd - posStart);
		posStart = posEnd + sepLen;
		res.push_back(token);
	}
	res.push_back(src.substr(posStart));
	return res;
}

std::vector<std::string>	ircSplit(std::string const src)
{
	// |CMD param1 param2 param3 :trailer|

	std::vector<std::string>	res;
	std::string					token;
	size_t						posStart = 0;
	size_t						strLen = src.size();
	size_t						posEnd = 0;

	while (posEnd < strLen && src[posEnd] != ':')
	{
		while (posEnd < strLen && src[posEnd] != ' ')
			posEnd++;
		res.push_back(src.substr(posStart, posEnd - posStart));
		posEnd++;
		posStart = posEnd;
	}
	if (posEnd + 1 < strLen)
		res.push_back(src.substr(posEnd + 1));
	return res;
}

void	ircFormatParam(std::vector<std::string> & param)
{
	if (param[0][0] == '@')
		param.erase(param.begin());
	if (param[0][0] == ':')
		param.erase(param.begin());
	for (size_t i = 0; i < param.size(); i++)
	{
		if (param[i][0] == '#' || param[i][0] == '&')
		{
			for (size_t ii = 0; ii < param[i].size(); ii++)
				param[i][ii] = std::tolower(param[i][ii]);
		}
	}
}

void	debugPrintMsgRAW(const char * buf, int nbytes)
{
	std::string	msg(buf, nbytes);
	size_t		pos;

	while ((pos = msg.find('\x0d')) != std::string::npos)
		msg.replace(pos, 1, "\\r");
	while ((pos = msg.find('\x0a')) != std::string::npos)
		msg.replace(pos, 1, "\\n");
	logger.log(DEBUG) << "\"" << msg  << "\"";
	logger.nl();
}

std::string	cToStr(char c)
{
	std::string ret = "";

	ret += c;
	return ret;
}

int	quitCheck(int mode)
{
	static int check = 0;

	if (mode != 0)
		check++;
	return check;
}

void	sigIntHandler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
	{
		logger.log(INFO) << "[SIG] SigInt detected";
		logger.nl();
		quitCheck(1);
		return ;
	}
	if (info && context)
		return ;
	return;
}

bool	strIsNumber(std::string const & str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

bool	strIsNumber(char const * str)
{
	if (!str)
		return false;
	for (size_t i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}
