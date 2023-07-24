/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:15:52 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/26 16:44:31 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base*	generate(void)
{
	srand(time(NULL));
	switch (rand() % 3 + 1)
	{
		case 1:
			std::cout << "generating... A type." << std::endl;
			return new A;
		case 2:
			std::cout << "generating... B type." << std::endl;
			return new B;
		case 3:
			std::cout << "generating... C type." << std::endl;
			return new C;
	}
	return 0;
}

void	identify(Base* p)
{
	A*	a = dynamic_cast<A*>(p);
	B*	b = dynamic_cast<B*>(p);
	C*	c = dynamic_cast<C*>(p);

	if (a)
		std::cout << "guessing via ptr: A type." << std::endl;
	if (b)
		std::cout << "guessing via ptr: B type." << std::endl;
	if (c)
		std::cout << "guessing via ptr: C type." << std::endl;
}

void	identify(Base& p)
{
	try
	{
		A&	a = dynamic_cast<A&>(p);
		std::cout << "guessing via ref: A type." << std::endl;
		(void)a;
	}
	catch (...) {}
	try
	{
		B&	b = dynamic_cast<B&>(p);
		std::cout << "guessing via ref: B type." << std::endl;
		(void)b;
	}
	catch (...) {}
	try
	{
		C&	c = dynamic_cast<C&>(p);
		std::cout << "guessing via ref: C type." << std::endl;
		(void)c;
	}
	catch (...) {}
}

int main()
{
	Base*	test;

	test = generate();
	identify(test);
	identify(*test);

	delete test;
	return 0;
}
