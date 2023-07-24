/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:23:47 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/20 13:49:12 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main()
{
	ClapTrap	tom("Tom");
	ScavTrap	jerry("Jerry");

	std::cout << std::endl;

	tom.attack("Jerry");
	jerry.takeDamage(tom.getDamage());
	jerry.attack("Tom");
	tom.takeDamage(jerry.getDamage());
	tom.beRepaired(30);
	jerry.guardGate();

	std::cout << std::endl;

	return 0;
}
