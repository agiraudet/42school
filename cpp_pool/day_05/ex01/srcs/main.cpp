/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:46:02 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/21 18:05:29 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main()
{
	std::cout << "# Simple form with low grade guy" << std::endl;
	{
		try
		{
			Form	cerfa("Cerfa n° 15776*02", 50, 10);
			std::cout << cerfa << std::endl;
			Bureaucrat	guy("Arthur", 51);
			std::cout << guy << std::endl;
			std::cout << "# Try to sign:" << std::endl;
			cerfa.beSigned(guy);
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "# Simple form with better guy" << std::endl;
	{
		try
		{
			Form	cerfa("Cerfa n° 15776*02", 50, 10);
			std::cout << cerfa << std::endl;
			Bureaucrat	guy("Arthur", 51);
			std::cout << guy << std::endl;
			guy.incGrade();
			std::cout << guy << std::endl;
			std::cout << "# Try to sign:" << std::endl;
			cerfa.beSigned(guy);
			std::cout << cerfa << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "# Simple form with guy action" << std::endl;
	{
		try
		{
			Form	cerfa("Cerfa n° 15776*02", 50, 10);
			std::cout << cerfa << std::endl;
			Bureaucrat	guy("Arthur", 40);
			std::cout << guy << std::endl;
			std::cout << "# Try to sign:" << std::endl;
			guy.signForm(cerfa);
			std::cout << cerfa << std::endl;
			std::cout << "# Try to sign again:" <<std::endl;
			guy.signForm(cerfa);
		}
		catch (std::exception & e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
	}
	return (0);
}
