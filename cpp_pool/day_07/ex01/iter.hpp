/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:02:24 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 12:34:49 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>

template<typename T>
void	iter(T* arr, size_t len, void (*f)(T const & elem))
{
	for (size_t i = 0; i < len; i++)
		f(arr[i]);
}

template<typename T>
void	printElem(T const & elem)
{
	std::cout << elem << " ";
}

#endif
