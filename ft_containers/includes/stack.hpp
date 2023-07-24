/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:39:03 by agiraude          #+#    #+#             */
/*   Updated: 2023/01/31 10:18:41 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include "utils.hpp"
# include "internals/iterator.hpp"

namespace ft
{

template<typename T, typename Container=ft::vector<T> >
class	stack
{
	//Member types
	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

	//Member objects
	protected:
		Container	c;

	//Constructor & Destructor
	public:
		explicit stack(Container const& cont=Container());
		stack(stack const& other);
		~stack(void);

	//Member Functions
	public:
		stack& operator=(stack const& other);

		//Element acess
		reference		top(void);
		const_reference	top(void) const;

		//Capacity
		bool			empty(void) const;
		size_type		size(void) const;

		//Modifiers
		void			push(value_type const& value);
		void			pop(void);

	//Non-member Functions
	template<typename U, typename C>
	friend bool	operator==(stack<U, C> const& lhs, stack<U, C> const& rhs);
	template<typename U, typename C>
	friend bool	operator<(stack<U, C> const& lhs, stack<U, C> const& rhs);
};

//Non-Member Functions
template<typename T, typename Container>
bool	operator!=(stack<T, Container> const& lhs, stack<T, Container> const& rhs);
template<typename T, typename Container>
bool	operator<=(stack<T, Container> const& lhs, stack<T, Container> const& rhs);
template<typename T, typename Container>
bool	operator>(stack<T, Container> const& lhs, stack<T, Container> const& rhs);
template<typename T, typename Container>
bool	operator>=(stack<T, Container> const& lhs, stack<T, Container> const& rhs);

/*
 * IMPLEMENTATION
 */

//Container and Destructor
template<typename T, typename Container>
stack<T, Container>::stack(Container const& cont)
: c(cont)
{
}

template<typename T, typename Container>
stack<T, Container>::stack(stack const& other)
{
	if (this == &other)
		return;
	*this = other;
}

template<typename T, typename Container>
stack<T, Container>::~stack(void)
{
}

//Member Functions
template<typename T, typename Container>
stack<T, Container>&	stack<T, Container>::operator=(stack const& other)
{
	if (this != &other)
		c = other.c;
	return *this;
}

template<typename T, typename Container>
typename stack<T, Container>::reference	stack<T, Container>::top(void)
{
	return c.back();
}

template<typename T, typename Container>
typename stack<T, Container>::const_reference	stack<T, Container>::top(void) const
{
	return c.back();
}

template<typename T, typename Container>
bool	stack<T, Container>::empty(void) const
{
	return c.empty();
}

template<typename T, typename Container>
typename stack<T, Container>::size_type	stack<T, Container>::size(void) const
{
	return c.size();
}

template<typename T, typename Container>
void	stack<T, Container>::push(value_type const& value)
{
	c.push_back(value);
}

template<typename T, typename Container>
void	stack<T, Container>::pop(void)
{
	c.pop_back();
}

//Non_Member Functions
template<typename T, typename Container>
bool	operator==(stack<T, Container> const& lhs, stack<T, Container> const& rhs)
{
	return lhs.c == rhs.c;
}

template<typename T, typename Container>
bool	operator!=(stack<T, Container> const& lhs, stack<T, Container> const& rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename Container>
bool	operator<(stack<T, Container> const& lhs, stack<T, Container> const& rhs)
{
	return ft::lexicographical_compare(lhs.c.begin(), lhs.c.end(), rhs.c.begin(), rhs.c.end());
}

template<typename T, typename Container>
bool	operator<=(stack<T, Container> const& lhs, stack<T, Container> const& rhs)
{
	return !(rhs < lhs);
}

template<typename T, typename Container>
bool	operator>(stack<T, Container> const& lhs, stack<T, Container> const& rhs)
{
	return rhs < lhs;
}

template<typename T, typename Container>
bool	operator>=(stack<T, Container> const& lhs, stack<T, Container> const& rhs)
{
	return !(lhs < rhs);
}

}
#endif
