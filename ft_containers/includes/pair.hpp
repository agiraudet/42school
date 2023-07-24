/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:49:01 by agiraude          #+#    #+#             */
/*   Updated: 2023/01/30 11:42:56 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{

template<typename T1, typename T2>
class	pair
{
	//Member type
	public:
		typedef T1	first_type;
		typedef T2	second_type;
	
	//Member objects
	public:
		T1	first;
		T2	second;

	//Member functions
	public:
		//Constuctor & destructor
		pair(void);
		pair(T1 const& x, T2 const& y);
		pair(pair const& p);
		template<typename U1, typename U2>
		pair(pair<U1, U2> const& p);
		~pair(void);

		//Member Function
		pair&	operator=(pair const& other);
};

//Non-member Functions
template<typename T1, typename T2>
pair<T1, T2>	make_pair(T1 t1, T2 t2);
template<typename T1, typename T2>
bool	operator==(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs);
template<typename T1, typename T2>
bool	operator!=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs);
template<typename T1, typename T2>
bool	operator<(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs);
template<typename T1, typename T2>
bool	operator<=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs);
template<typename T1, typename T2>
bool	operator>(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs);
template<typename T1, typename T2>
bool	operator>=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs);

/*
 * IMPLEMENTATION
 */

//Constructor & destructor
template<typename T1, typename T2>
pair<T1, T2>::pair(void)
{
}

template<typename T1, typename T2>
pair<T1, T2>::pair(T1 const& x, T2 const& y)
: first(x), second(y)
{
}

template<typename T1, typename T2>
pair<T1, T2>::pair(pair const& p)
: first(p.first), second(p.second)
{
}

template<typename T1, typename T2>
template<typename U1, typename U2>
pair<T1, T2>::pair(pair<U1, U2> const& p)
: first(p.first), second(p.second)
{
}

template<typename T1, typename T2>
pair<T1, T2>::~pair(void)
{
}

//Operator member overload
template<typename T1, typename T2>
pair<T1, T2>&	pair<T1, T2>::operator=(pair<T1, T2> const& other)
{
	first = other.first;
	second = other.second;
	return *this;
}

//Non-Member Functions
template<typename T1, typename T2>
pair<T1, T2>	make_pair(T1 t1, T2 t2)
{
	return pair<T1, T2>(t1, t2);
}

template<typename T1, typename T2>
bool	operator==(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<typename T1, typename T2>
bool	operator!=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
{
	return !(lhs == rhs);
}

template<typename T1, typename T2>
bool	operator<(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
{
	if (lhs.first == rhs.first)
		return lhs.second < rhs.second;
	return lhs.first < rhs.first;
}

template<typename T1, typename T2>
bool	operator<=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
{
	return !(rhs < lhs);
}

template<typename T1, typename T2>
bool	operator>(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
{
	return rhs < lhs;
}

template<typename T1, typename T2>
bool	operator>=(pair<T1, T2> const& lhs, pair<T1, T2> const& rhs)
{
	return !(lhs < rhs);
}

}
#endif
