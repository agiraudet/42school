/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:23:47 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/20 15:01:51 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int	main()
{
	ClapTrap	don("Donatello");
	ScavTrap	leo("Leonardo");
	FragTrap	mic("Michelangelo");
	FragTrap	rap("Raphael");

	std::cout << std::endl;

	leo.guardGate();
	mic.highFivesGuys();
	rap.attack("Michelangelo");
	mic.takeDamage(rap.getDamage());
	rap.attack("Michelangelo");
	mic.takeDamage(rap.getDamage());
	rap.attack("Michelangelo");
	mic.takeDamage(rap.getDamage());
	mic.beRepaired(10);
	rap.attack("Michelangelo");
	mic.takeDamage(rap.getDamage());
	mic.highFivesGuys();

	std::cout << std::endl;

	return 0;
}
