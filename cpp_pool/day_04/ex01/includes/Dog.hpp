/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:05:42 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/21 13:47:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include <iostream>
# include "Animal.hpp"
# include "Brain.hpp"

class	Dog : public Animal
{
	public:

		Dog(void);
		Dog(Dog const & src);
		virtual	~Dog(void);
		
		Dog & operator=(Dog const & rhs);

		virtual void	makeSound(void) const;
		std::string		getIdea(int n) const;
		void			setIdea(int n, std::string idea);

	private:
		Brain *	_brain;
};
#endif
