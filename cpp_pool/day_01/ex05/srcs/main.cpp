/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:53:08 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/18 12:37:41 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main()
{
	Harl	dbg;

	std::cout << "[testing with level \"debug\"]" << std::endl;
	dbg.complain("DEBUG");
	std::cout << "[testing with level \"info\"]" << std::endl;
	dbg.complain("INFO");
	std::cout << "[testing with level \"warning\"]" << std::endl;
	dbg.complain("WARNING");
	std::cout << "[testing with level \"error\"]" << std::endl;
	dbg.complain("ERROR");
	std::cout << "[testing with level \"other\"]" << std::endl;
	dbg.complain("OTHER");
	return (0);
}
