/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:20:12 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 14:43:07 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>

template<typename T>
typename T::const_iterator	easyfind(T const & cont, int const & n)
{
	typename T::const_iterator	it;

	it = std::find(cont.begin(), cont.end(), n);
	if (it == cont.end())
		throw std::exception();
	return it;
}

#endif
