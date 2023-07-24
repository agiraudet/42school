/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:45:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 12:42:08 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

template<typename T>
void	swap(T & x, T & y)
{
	T temp = x;
	x = y;
	y = temp;
}

template<typename T>
T const & min(T const & x, T const & y)
{
	return ( x < y ? x : y);
}

template<typename T>
T const & max(T const & x, T const & y)
{
	return ( x > y ? x : y);
}

#endif
