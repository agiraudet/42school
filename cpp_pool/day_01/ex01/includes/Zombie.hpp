/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 20:05:53 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 20:48:42 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>
# include <iostream>

class	Zombie
{
	public:
				Zombie(void);
				~Zombie(void);
		void	setName(std::string name);
		void	announce(void) const;

	private:
		std::string	_name;
};

Zombie	*zombieHorde(int N, std::string name);

#endif
