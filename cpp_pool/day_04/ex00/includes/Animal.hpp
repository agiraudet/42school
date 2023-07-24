/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:36:59 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/21 09:42:21 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

class	Animal
{
	public:

		Animal(void);
		Animal(Animal const & src);
		virtual	~Animal(void);
		
		Animal & operator=(Animal const & rhs);

		virtual void	makeSound(void) const;
		void			setType(std::string type);
		std::string		getType(void) const;

	protected:

		std::string	_type;

};

#endif
