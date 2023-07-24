/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:32:37 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/19 16:40:50 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>
# include <string>

class	ClapTrap
{
	public:

		ClapTrap(std::string name);
		ClapTrap(ClapTrap const & src);
		~ClapTrap(void);
		
		ClapTrap & operator=(ClapTrap const & rhs);

		std::string	getName(void) const;
		void		attack(const std::string & target);
		void		takeDamage(unsigned int amount);
		void		beRepaired(unsigned int amount);

	private:

		std::string	_name;
		int			_hitPoint;
		int			_energyPoint;
		int			_attackDamage;

};

#endif
