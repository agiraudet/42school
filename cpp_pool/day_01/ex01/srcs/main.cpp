/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 20:14:57 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 20:53:39 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

void	test(int N, std::string name)
{
	Zombie	*horde;

	horde = zombieHorde(N, name);
	for (int i = 0; i < N; i++)
		horde[i].announce();
	delete [] horde;
}

int	main()
{
	test(4, "Jim");
	std::cout << std::endl;
	test(8, "George");

	return (0);
}
