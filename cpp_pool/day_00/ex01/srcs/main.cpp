/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:03:23 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 18:51:57 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PhoneBook.hpp"

void	fillBookAuto(PhoneBook *pageBlanches)
{
	pageBlanches->addContactAuto("0123456789abcdef", "Smith", "hexa", "0681193571", "pas malin");
	pageBlanches->addContactAuto("aaa", "aaa", "a", "aaaaaa", "aaaaaaaaa");
	pageBlanches->addContactAuto("b", "bbbbbbbbbbbbb", "bb", "bbb", "bbbbb");
	pageBlanches->addContactAuto("x", "xx", "xxx", "xxxx", "xxxxx");
	pageBlanches->addContactAuto("y", "yy", "yyy", "yyyy", "yyyyy");
	pageBlanches->addContactAuto("z", "zz", "zzz", "zzzz", "zzzzz");
	pageBlanches->addContactAuto("w", "ww", "www", "wwww", "wwwww");
	pageBlanches->addContactAuto("v", "vv", "vvv", "vvvv", "vvvvv");
}

int	main()
{
	PhoneBook	pageBlanches;
	std::string	input;

	//fillBookAuto(&pageBlanches);

	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin >> std::ws, input);
		if (input.compare("EXIT") == 0)
			break ;
		else if (input.compare("ADD") == 0)
			pageBlanches.addContact();
		else if (input.compare("SEARCH") == 0)
		{
			pageBlanches.search();
			while (true && pageBlanches.getNbContact() > 0)
			{
				std::cout << "index> ";
				std::getline(std::cin >> std::ws, input);
				if (isdigit(input[0]) && !input[1] && input[0] - '0' < pageBlanches.getNbContact())
				{
					pageBlanches.selectContact(input[0] - '0');
					break ;
				}
				else
					std::cout << "Please choose a valid index" << std::endl;
			}
		}
	}
	return (0);
}
