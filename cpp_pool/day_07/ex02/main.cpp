/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:57:51 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 12:24:22 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Array.hpp"

int main(void)
{
	std::cout << "### Creating arrIntA (size 9) ###" << std::endl;
	Array<int>	arrIntA(9);
	std::cout << "arrIntA: ";
	for (size_t i = 0; i < arrIntA.size(); i++)
		std::cout << arrIntA[i] << " ";
	std::cout << std::endl << std::endl;
	
	std::cout << "### Filling arrIntA ###" << std::endl;
	for (int i = 0; i < 9; i++)
		arrIntA[i] = i;
	std::cout << "arrIntA: ";
	for (int i = 0; i < 9; i++)
		std::cout << arrIntA[i] << " ";
	std::cout << std::endl << std::endl;

	std::cout << "### Creating arrIntB by copy of arrIntA ###" << std::endl;
	Array<int> arrIntB(arrIntA);
	std::cout << "arrIntB: ";
	for (int i = 0; i < 9; i++)
		std::cout << arrIntB[i] << " ";
	std::cout << std::endl << std::endl;

	std::cout << "### Modifying arrIntB ###" << std::endl;
	for (int i = 0; i < 9; i++)
		arrIntB[i] += 1;
	std::cout << "arrIntA: ";
	for (int i = 0; i < 9; i++)
		std::cout << arrIntA[i] << " ";
	std::cout << std::endl;
	std::cout << "arrIntB: ";
	for (int i = 0; i < 9; i++)
		std::cout << arrIntB[i] << " ";
	std::cout << std::endl << std::endl;

	std::cout << "### Trying to acces forbiden memory ###" << std::endl;
	std::cout << "arrIntB size: " << arrIntB.size() << ", trying arrIntB[42];" << std::endl;
	try
	{
		std::cout << arrIntB[42];
	}
	catch (std::exception & e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "### Creating arrStr ###" << std::endl;
	Array<std::string>	arrStr(3);
	arrStr[0] = "Hello";
	arrStr[1] = "World";
	arrStr[2] = "!";
	std::cout << "arrStr: ";
	for (int i = 0; i < 3; i++)
		std::cout << arrStr[i] << " ";
	std::cout << std::endl << std::endl;

	std::cout << "### Creating arrEmpty ###" << std::endl;
	Array<char> arrEmpty;
	std::cout << "arrEmpty size: " << arrEmpty.size() << std::endl;
	std::cout << "trying arrEmpty[0]:" << std::endl;
	try
	{
		std::cout << arrEmpty[0];
	}
	catch (std::exception & e)
	{
		std::cout << "error: " << e.what() << std::endl;
	}




	return 0;
}
