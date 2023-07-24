/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:26:30 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 12:38:28 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "iter.hpp"

int main(void)
{
	int			arrInt[] = {0, 2, 4, 6, 8};
	char		arrChar[] = {'a', 'b', 'c', 'd'};
	std::string	arrStr[] = {"Hello", "World", "!"};

	iter(arrChar, 4, printElem);
	std::cout << std::endl;

	iter(arrInt, 5, printElem<int>);
	std::cout << std::endl;

	iter(arrStr, 3, printElem);
	std::cout << std::endl;

	return 0;
}
