/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:57:31 by agiraude          #+#    #+#             */
/*   Updated: 2022/11/17 13:30:31 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Server.hpp"
#include "Logger.hpp"
#include "utils.hpp"

Logger	logger(".logs");

int	check_port(char *str)
{
	int i = atoi(str);
	if (i > 0 && i <= 65535 && strIsNumber(str))
		return 1;
	logger.log(ERROR) << "[Port] Bad Port value";
	logger.nl();
	return 0;
}

int	main(int argc, char **argv)
{
	struct	sigaction	sa;
	Server				serv;

	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sigIntHandler;
	logger.setLvlStd(WARN);
	logger.setLvlFile(DEBUG);
	if (argc != 3)
	{
		logger.log(ERROR) << "[Arg] Invalid Args : ./server [PORT] [PASSWORD]";
		logger.nl();
		return 1;
	}
	else
	{
		if (check_port(argv[1]) == 0)
			return 1;
		serv.coHandler.setPort(argv[1]);
		serv.setPassword(argv[2]);
	}
	sigaction(SIGINT, &sa, NULL);
	if (quitCheck(0) == 0)
		serv.run();
	return 0;
}
