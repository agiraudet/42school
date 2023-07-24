/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:36:59 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:56:09 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

class	AAnimal
{
	public:

		AAnimal(void);
		AAnimal(AAnimal const & src);
		virtual ~AAnimal(void);

		AAnimal & operator=(AAnimal const & rhs);

		virtual void	makeSound(void) const = 0;
		void			setType(std::string type);
		std::string		getType(void) const;

	protected:

		std::string	_type;

};

#endif
