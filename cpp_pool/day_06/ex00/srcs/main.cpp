/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:20:53 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/26 13:02:41 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Convert.hpp"

int	checkArg(char *arg)
{
	while (*arg == ' ' || *arg == '\t')
		arg++;
	if (*arg == '-')
		arg++;
	while (*arg >= '0' && *arg <= '9')
		arg++;
	if (*arg == '.')
		arg++;
	while (*arg >= '0' && *arg <= '9')
		arg++;
	if (*arg == 'f')
		arg++;
	if (*arg)
		return 0;
	return 1;
}

int	main(int argc, char **argv)
{
	std::string keywords = "nan nanf -inf +inf -inff +inff";
	std::string	arg = std::string(argv[1]);

	if (argc != 2)
	{
		std::cout << "Need one argument !" << std::endl;
		return 1;
	}
	if (!checkArg(argv[1]) && keywords.find(arg) == std::string::npos)
	{
		std::cout << "Wrong input format" << std::endl;
		return 1;
	}
	Convert cvrt = Convert(argv[1]);
	std::cout << cvrt << std::endl;
	return 0;
}
