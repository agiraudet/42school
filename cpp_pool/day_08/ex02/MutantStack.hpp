/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:23:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/28 13:03:03 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

template <typename T>
class	MutantStack : public std::stack<T>
{
	public:

		MutantStack(void) {}
		MutantStack(MutantStack const & src) : std::stack<T>() {*this = src;}
		virtual ~MutantStack(void) {}
		
		MutantStack & operator=(MutantStack const & rhs)
		{
			std::stack<T>::operator=(rhs);
			return *this;
		}

		typedef typename std::stack<T>::container_type::iterator	iterator;
		iterator	begin(void) { return this->c.begin(); }
		iterator	end(void) { return this->c.end(); }

		typedef typename std::stack<T>::container_type::const_iterator	const_iterator;
		const_iterator	begin(void) const { return this->c.begin(); }
		const_iterator	end(void) const { return this->c.end(); }

		typedef typename std::stack<T>::container_type::reverse_iterator	reverse_iterator;
		reverse_iterator	rbegin(void) { return this->c.rbegin(); }
		reverse_iterator	rend(void) { return this->c.rend(); }

		typedef typename std::stack<T>::container_type::const_reverse_iterator	const_reverse_iterator;
		const_reverse_iterator	rbegin(void) const { return this->c.rbegin(); }
		const_reverse_iterator	rend(void) const { return this->c.rend(); }

};
#endif
