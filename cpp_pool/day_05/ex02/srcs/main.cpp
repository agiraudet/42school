/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:46:02 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 15:44:12 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main()
{
	{
		Bureaucrat				guy("Martin", 30);
		RobotomyRequestForm		f("dude");
		guy.executeForm(f);
		guy.signForm(f);
		guy.executeForm(f);
		guy.executeForm(f);
	}
	std::cout << std::endl;
	{
		Bureaucrat				guy("Martin", 24);
		Bureaucrat				boss("Boss", 1);
		PresidentialPardonForm	f("dude");
		guy.signForm(f);
		guy.executeForm(f);
		boss.executeForm(f);
	}
	std::cout << std::endl;
	{
		Bureaucrat				guy("Martin", 138);
		ShrubberyCreationForm	f("garden");
		guy.signForm(f);
		guy.executeForm(f);
		guy.incGrade();
		guy.executeForm(f);
	}

	return (0);
}
