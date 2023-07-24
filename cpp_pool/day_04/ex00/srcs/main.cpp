/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:18:19 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:38:36 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "# Subject exemple:" << std::endl;
	{
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();

		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); //will output the cat sound!
		j->makeSound();
		meta->makeSound();

		delete i;
		delete j;
		delete meta;
	}
	std::cout << std::endl;
	std::cout << "# With WrongCat/WrongAnimal (no virtual keywords)" << std::endl;
	{
		const WrongAnimal* meta = new WrongCat();
		const WrongCat* i = new WrongCat();

		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); //will output the wrong cat sound!
		meta->makeSound();

		delete i;
		delete meta;
	}

	return 0;
}
