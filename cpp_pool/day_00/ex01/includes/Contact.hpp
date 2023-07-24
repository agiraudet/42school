/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:38:58 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 16:57:39 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class	Contact
{
	public:
		Contact(void);
		~Contact(void);
		void	printContact(void) const;
		void	printSearchInfo(int id) const;
		void	fillContact(void);
		void	fillContactAuto(std::string fn, std::string ln, std::string nn, std::string pn, std::string ds);

	private:
		std::string _firstName;
		std::string _lastName;
		std::string _nickName;
		std::string _phoneNumber;
		std::string _darkestSecret;
		
		void	_getStr(std::string *str);
		void	_printStr(std::string str) const;
};


#endif
