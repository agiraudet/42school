/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:07:49 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/21 12:58:34 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <string>

class	Brain
{
	public:

		Brain(void);
		Brain(Brain const & src);
		~Brain(void);
		
		Brain & operator=(Brain const & rhs);

		std::string	getIdea(int n) const;
		void		setIdea(int n, std::string idea);

	private:

		std::string	_ideas[100];

};
#endif
