/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:28:30 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 14:54:04 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <vector>
#include "easyfind.hpp"

int main(void)
{
	{
		std::cout << "### LIST ###" << std::endl;
		std::list<int>	lstA;

		lstA.push_back(24);
		lstA.push_back(56);
		lstA.push_back(12);
		lstA.push_back(85);
		lstA.push_back(32);
		lstA.push_back(9);
		lstA.push_back(4);

		std::list<int>::const_iterator	found;
		try
		{
			found = easyfind(lstA, 12);
			std::cout << "found: " << *found << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "12 not found" << std::endl;
		}
		try
		{
			found = easyfind(lstA, 4);
			std::cout << "found: " << *found << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "4 not found" << std::endl;
		}
		try
		{
			found = easyfind(lstA, 5);
			std::cout << "found: " << *found << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "5 not found" << std::endl;
		}
	}
	{
		std::cout << std::endl << "### VECTOR ###" << std::endl;
		std::vector<int>	vctA;

		vctA.push_back(48);
		vctA.push_back(6);
		vctA.push_back(345);
		vctA.push_back(-65);
		vctA.push_back(0);
		vctA.push_back(-24);
		
		std::vector<int>::const_iterator	found;
		try
		{
			found = easyfind(vctA, 12);
			std::cout << "found: " << *found << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "12 not found" << std::endl;
		}
		try
		{
			found = easyfind(vctA, -65);
			std::cout << "found: " << *found << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "4 not found" << std::endl;
		}
		try
		{
			found = easyfind(vctA, 0);
			std::cout << "found: " << *found << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "5 not found" << std::endl;
		}
	}
	return 0;
}
