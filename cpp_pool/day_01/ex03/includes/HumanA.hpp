/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:28:18 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 22:13:49 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"

class	HumanA
{
	public:

		HumanA(std::string name, Weapon& tool);
		~HumanA(void);

		void	attack(void) const;

	private:

		std::string	_name;
		Weapon&		_tool;
};

#endif
