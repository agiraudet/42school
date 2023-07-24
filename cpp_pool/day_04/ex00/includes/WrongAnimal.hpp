/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:36:59 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/21 13:54:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>
# include <string>

class	WrongAnimal
{
	public:

		WrongAnimal(void);
		WrongAnimal(WrongAnimal const & src);
		virtual ~WrongAnimal(void);
		
		WrongAnimal & operator=(WrongAnimal const & rhs);

		void	makeSound(void) const;
		void			setType(std::string type);
		std::string		getType(void) const;

	protected:

		std::string	_type;

};

#endif
