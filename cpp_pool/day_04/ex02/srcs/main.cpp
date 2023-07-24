/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:18:19 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:52:46 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	//This line bellow will not compile since Animal is an abstract class
	//AAnimal	pet;
	
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
