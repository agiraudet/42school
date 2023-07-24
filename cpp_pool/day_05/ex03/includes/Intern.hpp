/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:23:51 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/23 14:28:34 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include <iostream>
# include <string>
# include "AForm.hpp"

class	Intern
{
	public:

		Intern(void);
		Intern(Intern const & src);
		~Intern(void);
		
		Intern & operator=(Intern const & rhs);

		AForm	*makeForm(std::string name, std::string target) const;

	private :

		AForm*	_SCForm(std::string target) const;
		AForm*	_PPForm(std::string target) const;
		AForm*	_RRForm(std::string target) const;
		AForm*	(Intern::*_f[3])(std::string) const;
};
#endif
