/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 20:14:57 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 20:42:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie	*newZombie(std::string name)
{
	Zombie	*new_guy;

	new_guy = new Zombie();
	new_guy->setName(name);
	return (new_guy);
}

void	randomChump(std::string name)
{
	Zombie	random_guy;

	random_guy.setName(name);
	random_guy.announce();
}

int	main()
{
	Zombie	*this_guy;
	Zombie	*that_guy;

	this_guy = newZombie("Roger");
	this_guy->announce();

	randomChump("Tony");

	that_guy = newZombie("Albert");
	that_guy->announce();

	delete that_guy;
	delete this_guy;

	return (0);
}
