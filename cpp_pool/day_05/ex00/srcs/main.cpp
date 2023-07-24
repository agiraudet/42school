/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:46:02 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 15:08:42 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main()
{
	std::cout << "# Simple bureaucrat" << std::endl;
	{
		try
		{
			Bureaucrat	a("Tom", 28);
			std::cout << a << std::endl;
			a.incGrade();
			std::cout << a << std::endl;
			a.decGrade();
			std::cout << a << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "# The BEST bureaucrat" << std::endl;
	{
		try
		{
			Bureaucrat	a("Tom", 0);
			std::cout << a << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "# The (almost) BEST bureaucrat" << std::endl;
	{
		try
		{
			Bureaucrat	a("Tom", 1);
			std::cout << a << std::endl;
			try
			{
				a.incGrade();
			}
			catch (std::exception & e)
			{
				std::cout << "error: " << e.what() << std::endl;
			}
			std::cout << a << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "# The WORST bureaucrat" << std::endl;
	{
		try
		{
			Bureaucrat	a("Tom", 151);
			std::cout << a << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "# The (almost) WORST bureaucrat" << std::endl;
	{
		try
		{
			Bureaucrat	a("Tom", 150);
			std::cout << a << std::endl;
			try
			{
				a.decGrade();
			}
			catch (std::exception & e)
			{
				std::cout << "error: " << e.what() << std::endl;
			}
			std::cout << a << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
	}
	std::cout << std::endl;
	return (0);
}
