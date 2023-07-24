/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:18:19 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/21 13:36:08 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	Animal*	animalArray[10];

	std::cout << "# Creating animal array:" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		if (i < 5)
			animalArray[i] = new Cat;
		else
			animalArray[i] = new Dog;
	}
	std::cout << std::endl;

	std::cout << "# animal[4] and animal[5] make noise:" << std::endl;
	animalArray[4]->makeSound();
	animalArray[5]->makeSound();
	std::cout << std::endl;

	std::cout << "# Desroying animal array with delete:" << std::endl;
	for (int i = 0; i < 10; i++)
		delete animalArray[i];
	std::cout << std::endl;

	std::cout << "# Creating dog \"Finn\" (and setting idea):" << std::endl;
	Dog	finn;
	finn.setIdea(0, "I could use a nap");
	std::cout << std::endl;

	std::cout << "# Creating dog \"Laika\" by copy of Finn:" << std::endl;
	Dog laika(finn);
	std::cout << std::endl;

	std::cout << "# Checking laika's ideas:" << std::endl;
	std::cout << laika.getIdea(0) << std::endl;
	std::cout << std::endl;

	std::cout << "# Finn and Laika get automaticly destroyed:" << std::endl;

	return 0;
}
