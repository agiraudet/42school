/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mask.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:52:17 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/22 15:16:19 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MASK_HPP
# define MASK_HPP

# include <iostream>
# include <string>

class	Mask
{
	public:

		Mask(std::string mask);
		Mask(Mask const & src);
		~Mask(void);
		
		bool			match(std::string const & in);
		bool			match(Mask & inMask);
		std::string &	getNick(void);
		std::string &	getUser(void);
		std::string &	getHost(void);
		Mask & 			operator=(Mask const & rhs);

	private:

		std::string	_nick;
		std::string	_user;
		std::string	_host;

		Mask(void);
		bool	_fieldMatch(std::string const & in, std::string const & field);



};

bool maskMatch(Mask & in, Mask & mask);
bool maskMatch(std::string in, Mask & mask);
bool maskMatch(Mask & in, std::string mask);
bool maskMatch(std::string in, std::string mask);

#endif
