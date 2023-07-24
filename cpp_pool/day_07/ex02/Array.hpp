/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:38:59 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/27 12:20:09 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>

template<typename T>
class	Array
{
	public:

		Array(void) : _ptr(NULL), _size(0) {};

		Array(unsigned int n): _size(n)
		{
			if (!n)
				_ptr = NULL;
			else
				_ptr = new T[n];
		}

		Array(Array const & src) : _ptr(NULL)
		{
			*this = src;
		}

		~Array(void)
		{
			if (_ptr)
				delete [] _ptr;
		}
		
		Array & operator=(Array const & rhs)
		{
			if (_ptr)
				delete[] _ptr;
			_size = rhs._size;
			_ptr = new T[rhs._size];
			for (size_t i = 0; i < _size; i++)
				_ptr[i] = rhs._ptr[i];
			return *this;
		}

		T & operator[](size_t i)
		{
			if (i >= _size)
				throw std::exception();
			return _ptr[i];
		}

		size_t	size(void) const
		{
			return _size;
		}

	private:

		T*		_ptr;
		size_t	_size;

};

#endif
