/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:20:02 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/17 17:39:42 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"

class	PhoneBook
{
	public:
				PhoneBook(void);
				~PhoneBook(void);
		int		getNbContact(void) const;
		void	addContact(void);
		void	addContactAuto(void);
		void	addContactAuto(std::string fn, std::string ln, std::string nn, std::string pn, std::string ds);
		void	search(void);
		void	selectContact(int i);

	private:
		int		_nbContact;
		int		_cursor;
		Contact	_lstContact[8];
};


#endif
