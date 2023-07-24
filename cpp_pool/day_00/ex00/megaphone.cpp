/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:10:18 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/16 23:04:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(int argc, char **argv)
{
	int	ii;
	int	i;

	if (argc < 2)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	for (i = 1; i < argc; i++)
	{
		ii = 0;
		while (argv[i][ii])
			std::cout << (char)toupper(argv[i][ii++]);
	}
	std::cout << std::endl;
	return (0);
}
