/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 10:42:35 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/18 12:35:02 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>
# include <string>

class	Harl
{
	public:

		Harl(void);
		~Harl(void);

		void	complain(std::string level) const;
		
	private:

		void	(Harl::*_f[4])(void) const;
		void	_debug(void) const;
		void	_info(void) const;
		void	_warning(void) const;
		void	_error(void) const;

};


#endif
