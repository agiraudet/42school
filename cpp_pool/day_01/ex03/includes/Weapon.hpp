/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 21:24:21 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 22:04:43 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>

class	Weapon
{
	public:

		Weapon(std::string type);
		~Weapon(void);

		std::string&	getType(void);
		void			setType(std::string weapon_type);

	private:

		std::string	_type;
};	

#endif
