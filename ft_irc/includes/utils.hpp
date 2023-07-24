/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:50:55 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/17 09:59:49 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <arpa/inet.h>
# include <netdb.h>
# include <string>
# include <vector>
# include <algorithm>
# include <signal.h>

template<typename T>
bool	contains(std::vector<T> vec, const T & elem)
{
	if (std::find(vec.begin(), vec.end(), elem) != vec.end())
		return true;
	return false;
}

std::string					IpToStr(struct sockaddr_storage const & ss);
std::vector<std::string>	ftSplit(std::string const src, std::string sep);
std::vector<std::string>	ircSplit(std::string const src);
void						debugPrintMsgRAW(const char * buf, int nbytes);
std::string					cToStr(char c);
int							quitCheck(int mode);
void						sigIntHandler(int sig, siginfo_t *info, void *context);
void						ircFormatParam(std::vector<std::string> & param);
bool						strIsNumber(std::string const & str);
bool						strIsNumber(char const * str);

#endif
