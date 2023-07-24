/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:05:42 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/21 09:42:43 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include <iostream>
# include "Animal.hpp"

class	Dog : public Animal
{
	public:

		Dog(void);
		Dog(Dog const & src);
		virtual	~Dog(void);
		
		Dog & operator=(Dog const & rhs);

		virtual void	makeSound(void) const;
};
#endif
