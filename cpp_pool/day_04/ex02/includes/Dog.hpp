/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:05:42 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 19:53:56 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include <iostream>
# include "AAnimal.hpp"
# include "Brain.hpp"

class	Dog : public AAnimal
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
