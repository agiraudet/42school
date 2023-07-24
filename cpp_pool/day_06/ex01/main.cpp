/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:51:08 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/26 16:10:05 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdint.h>

typedef struct	s_data
{
	std::string	str;
	int			n;
}				Data;

uintptr_t	serialize(Data* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

Data*	deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data*>(raw);
}

int	main()
{
	Data		test;
	Data		*ptr1;
	Data		*ptr2;
	uintptr_t	raw;

	test.str = "Hello World!";
	test.n = 57;

	ptr1 = &test;
	raw = serialize(ptr1);
	ptr2 = deserialize(raw);

	std::cout << ptr1 << std::endl << raw << std::endl << ptr2 << std::endl;
	std::cout << std::endl << ptr1->str << std::endl << ptr2->str << std::endl;
	std::cout << std::endl << ptr1->n << std::endl << ptr2->n << std::endl;

	return 0;
}
