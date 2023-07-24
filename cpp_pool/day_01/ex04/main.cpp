/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 09:17:03 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/18 16:05:37 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

std::string	strrplc(std::string str, std::string from, std::string to)
{
	std::size_t	found;
	std::string	tmp;

	while (true)
	{
		found = str.find(from);
		if (found == std::string::npos)
			break ;
		tmp = "";
		if (found != 0)
			tmp += str.substr(0, found - 1);
		tmp += to;
		tmp += str.substr(found + from.size(), std::string::npos);
		str = tmp;
	}
	return (str);
}

int	check_args(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "Wrong number of arguments" << std::endl;
		return 0;
	}
	if (argv[2][0] == 0)
	{
		std::cout << "argument 2 should not be empty" << std::endl;
		return 0;
	}
	return 1;
}

int	main(int argc, char *argv[])
{
	std::ifstream	ifs;
	std::ofstream	ofs;
	std::string		outfile;

	if (!check_args(argc, argv))
		return 0;
	ifs.open(argv[1]);
	if (!ifs.is_open())
	{
		std::cout << argv[1] << ": not a valid file." << std::endl;
		return 0;
	}
	outfile = std::string(argv[1]);
	outfile += ".replace";
	ofs.open(outfile.c_str());
	if (ofs.is_open())
	{
		std::string line;
		while (getline(ifs, line))
			ofs << strrplc(line, argv[2], argv[3]) << std::endl;
		ofs.close();
	}
	ifs.close();
	return (0);
}



