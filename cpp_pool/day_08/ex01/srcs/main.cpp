/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 08:57:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/28 10:14:23 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Span.hpp"

int main(void)
{
	std::cout << "### Subject main ###" << std::endl;
	{
		Span sp = Span(5);

		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		sp.printLst();

		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "### Add multiple numbers ###" << std::endl;
	{
		Span	sp = Span(8);

		sp.addNumberRange(1, 29, 4);
		sp.printLst();

		try
		{
			sp.addNumber(-2);
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
		try
		{
			sp.addNumberRange(-2, 4, 2);
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
	}
	std::cout << std::endl;
	

	std::cout << "### Too small of a list ###" << std::endl;
	{
		Span sp = Span(5);

		sp.addNumber(6);
		sp.printLst();

		try
		{
			std::cout << sp.shortestSpan() << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
		try
		{
			std::cout << sp.longestSpan() << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
		sp.addNumberRange(5, 2, 1);
		sp.printLst();
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	std::cout << std::endl;


	std::cout << "### BIG list ###" << std::endl;
	{
		Span	sp = Span(15000);

		sp.addNumberRand(15000);

		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

	return 0;
}

