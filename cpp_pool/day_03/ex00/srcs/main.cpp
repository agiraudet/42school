/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:23:47 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/19 16:57:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main()
{
	ClapTrap	tony("Tony");
	ClapTrap	edgar("Edgar");

	{
		ClapTrap	clone(tony);
	}

	tony.attack("Edgar");
	edgar.takeDamage(2);
	edgar.beRepaired(1);
	tony.attack("Edgar");
	edgar.takeDamage(2);
	tony.attack("Edgar");
	edgar.takeDamage(2);
	tony.attack("Edgar");
	edgar.takeDamage(2);
	tony.attack("Edgar");
	edgar.takeDamage(2);
	tony.attack("Edgar");
	edgar.takeDamage(2);
	tony.attack("Edgar");
	edgar.takeDamage(2);

	edgar.beRepaired(5);

	tony.attack("himself");
	tony.takeDamage(1);
	tony.attack("himself");
	tony.takeDamage(1);
	tony.attack("himself");
	tony.takeDamage(1);
	tony.attack("himself");
	tony.beRepaired(10);

	return 0;
}
