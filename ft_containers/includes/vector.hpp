/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:26:26 by agiraude          #+#    #+#             */
/*   Updated: 2023/01/31 23:18:14 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "internals/iterator.hpp"
# include "internals/VecItor.hpp"
# include "utils.hpp"
# include <stdexcept>
# include <cstring>

namespace ft
{
template<typename T, typename Alloc=std::allocator<T> >
class	vector
{
	public:
		typedef	Alloc							allocator_type;
		typedef	typename Alloc::value_type		value_type;
		typedef typename Alloc::size_type		size_type;
		typedef typename Alloc::difference_type	difference_type;
		typedef typename Alloc::reference		reference;
		typedef typename Alloc::const_reference	const_reference;
		typedef	typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer	const_pointer;
	
	//Iterators
		typedef	pointer								iterator;
		typedef	const_pointer						const_iterator;
		typedef	VecRevItor<iterator>				reverse_iterator;
		typedef VecRevItor<const_iterator>	const_reverse_iterator;

	//Constructors
	public:
		explicit vector(Alloc const& alloc = Alloc());
		explicit vector(size_type count, T const& value = T(), Alloc const& = Alloc());
		template<typename InputIt>
		vector(InputIt first, InputIt last, Alloc const& alloc = Alloc(),
				typename ft::enable_if<ft::is_iterator<InputIt>::value>::type* = 0);
		vector(vector const& other);
		~vector();
		
		void			assign(size_type count, const T& value);
		template<typename InputIt>
		void			assign(InputIt first, InputIt last,
				typename ft::enable_if<ft::is_iterator<InputIt>::value>::type* = 0);
		allocator_type	get_allocator(void) const;
		vector&	operator=(vector const& other);
	
	//Element Access
		reference		at(size_type pos);
		const_reference	at(size_type pos) const;
		reference		operator[](size_type pos);
		const_reference	operator[](size_type pos) const;
		reference		front(void);
		const_reference	front(void) const;
		reference		back(void);
		const_reference	back(void) const;
		T*				data(void);
		T const*		data(void) const;
	
	//Iterators
		iterator				begin(void);
		iterator				end(void);
		const_iterator			begin(void) const;
		const_iterator			end(void) const;
		reverse_iterator		rbegin(void);
		reverse_iterator		rend(void);
		const_reverse_iterator	rbegin(void) const;
		const_reverse_iterator	rend(void) const;
		

	//Capacity
		bool		empty(void) const;
		size_type	size(void) const;
		size_type	max_size(void) const;
		void		reserve(size_type newCapacity);
		size_type	capacity(void) const;
	
	//Modifier
		void		clear(void);
		iterator	insert(const_iterator pos, T const& value);
		iterator	insert(const_iterator pos, size_type count, T const& value);
		template<typename InputIt>
		iterator	insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<ft::is_iterator<InputIt>::value>::type* = 0);

		iterator	erase(iterator pos);
		iterator	erase(iterator first, iterator last);
		void		push_back(T const& value);
		void		pop_back(void);
		void		resize(size_type count, T value = T());
		void		swap(vector& other);

	private:
		Alloc		_alloc;
		T*			_data;
		size_type	_size;
		size_type	_capacity;

	//Helper
	private:
		void		_grow(size_type newCapacity);
		void		_shrink(size_type newCapacity);
};

//Non-Member Functions
template<typename T, typename Alloc>
bool	operator==(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs);
template<typename T, typename Alloc>
bool	operator!=(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs);
template<typename T, typename Alloc>
bool	operator<(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs);
template<typename T, typename Alloc>
bool	operator<=(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs);
template<typename T, typename Alloc>
bool	operator>(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs);
template<typename T, typename Alloc>
bool	operator>=(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs);

/******************
 * IMPLEMENTATION *
 ******************/

//Constructor
template<typename T, typename Alloc>
vector<T, Alloc>::vector(Alloc const& alloc)
: _alloc(alloc), _data(NULL), _size(0), _capacity(0)
{
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(size_type count, T const& value , Alloc const& alloc)
: _alloc(alloc), _data(NULL), _size(0), _capacity(0)
{
	resize(count, value);
}

template<typename T, typename Alloc>
template<typename InputIt>
vector<T, Alloc>::vector(InputIt first, InputIt last, const Alloc& alloc,
		typename ft::enable_if<ft::is_iterator<InputIt>::value>::type*)
: _alloc(alloc), _data(NULL), _size(0), _capacity(0)
{
	size_type	count = ft::distance(first, last);
	_grow(count);
	for (size_type i = 0; first != last; first++)
		_alloc.construct(_data + i++, *first);
	_size = count;
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(vector const& other)
: _alloc(other._alloc), _data(NULL), _size(0), _capacity(0)
{
	*this = other;
}


template<typename T, typename Alloc>
vector<T, Alloc>::~vector(void)
{
	if (_capacity > 0 && _data)
	{
		for (size_type i = 0; i < _size; i++)
			_alloc.destroy(_data + i);
		_alloc.deallocate(_data, _capacity);
		_data = NULL;	
	}
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::assign(size_type count, T const& value)
{
	if (_capacity < count)
		_grow(count);
	for (size_type i = 0; i < _size; i++)
		_alloc.destroy(_data + i);
	for (size_type i = 0; i < count; i++)
		_alloc.construct(_data + i, value);
	_size = count;
}

template<typename T, typename Alloc>
template<typename InputIt>
void
vector<T, Alloc>::assign(InputIt first, InputIt last,
		typename ft::enable_if<ft::is_iterator<InputIt>::value>::type*)
{
	size_type	count = ft::distance(first, last);
	if (_capacity < count)
		_grow(count);
	for (size_type i = 0; i < _size; i++)
		_alloc.destroy(_data + i);
	for (size_type i = 0; first != last; first++)
		_alloc.construct(_data + i++, *first);
	_size = count;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::allocator_type
vector<T, Alloc>::get_allocator(void) const
{
	return _alloc;
}

template<typename T, typename Alloc>
vector<T, Alloc>&
vector<T, Alloc>::operator=(vector const& other)
{
	if (this == &other)
		return *this;
	size_type	otherSize = other.size();
	if (_capacity < otherSize)
		_grow(otherSize);
	size_type	i = 0;
	for (; i < otherSize; i++)
	{
		if (i < _size)
			_alloc.destroy(_data + i);
		_alloc.construct(_data + i, other[i]);
	}
	for (; i < _size; i++)
		_alloc.destroy(_data + i);
	_size = otherSize;
	return *this;
}

//Element Access
template<typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::at(size_type pos)
{
	if (pos >= _size)
		throw std::out_of_range("Index out of range");
	return _data[pos];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::at(size_type pos) const
{
	if (pos >= _size)
		throw std::out_of_range("Index out of range");
	return _data[pos];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::operator[](size_type pos)
{
	return _data[pos];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::operator[](size_type pos) const
{
	return _data[pos];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::front(void)
{
	return _data[0];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::front(void) const
{
	return _data[0];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::back(void)
{
	return _data[_size -1];
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::back(void) const
{
	return _data[_size -1];
}

template<typename T, typename Alloc>
T*
vector<T, Alloc>::data(void) 
{
	return _data;
}

template<typename T, typename Alloc>
T const*
vector<T, Alloc>::data(void) const
{
	return _data;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::begin(void)
{
	return iterator(_data);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::end(void)
{
	return iterator(_data + _size);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator
vector<T, Alloc>::begin(void) const
{
	return iterator(_data);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator
vector<T, Alloc>::end(void) const
{
	return iterator(_data + _size);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator
vector<T, Alloc>::rbegin(void)
{
	return reverse_iterator(_data + _size);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator
vector<T, Alloc>::rend(void)
{
	return reverse_iterator(_data);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator
vector<T, Alloc>::rbegin(void) const
{
	return const_reverse_iterator(_data + _size);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator
vector<T, Alloc>::rend(void) const
{
	return const_reverse_iterator(_data);
}

//Capacity
template<typename T, typename Alloc>
bool	vector<T, Alloc>::empty(void) const
{
	return _size == 0;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::size(void) const
{
	return _size;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::max_size(void) const
{
	return _alloc.max_size();
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::reserve(vector<T, Alloc>::size_type newCapacity)
{
	if (newCapacity > _capacity)
		_grow(newCapacity);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::capacity(void) const
{
	return _capacity;
}

//Modifier
template<typename T, typename Alloc>
void
vector<T, Alloc>::clear(void)
{
	for (size_type i = 0; i < _size; i++)
		_alloc.destroy(_data + i);
	_size = 0;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::insert(const_iterator pos, T const& value)
{
	size_type index = pos - _data;
	if (_size == _capacity)
		_grow(_capacity + 1);
	for (size_type i = _size; i > index; i--)
	{
		_alloc.construct(_data + i, _data[i-1]);
		_alloc.destroy(_data + i - 1);
	}
	_alloc.construct(_data + index, value);
	_size++;
	return _data + index;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::insert(const_iterator pos, size_type count, T const& value)
{
	size_type index = pos - _data;
	if (count <= 0)
		return _data + index;
	if (_size + count > _capacity)
		_grow(_size + count);
	for (size_type i = _size + count - 1; i >= index + count; i--)
	{
		_alloc.construct(_data + i, _data[i-count]);
		_alloc.destroy(_data + i - count);
	}
	for (size_type i = index; i < index + count; i++)
		_alloc.construct(_data + i, value);
	_size += count;
	return _data + index;
}

template<typename T, typename Alloc>
template<typename InputIt>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::insert(const_iterator pos, InputIt first, InputIt last,
		typename ft::enable_if<ft::is_iterator<InputIt>::value>::type*)
{
	size_type	index = pos - _data;
	size_type	count = ft::distance(first, last);
	if (count <= 0 )
		return _data + index;
	if (_size + count > _capacity)
		_grow(_size + count);
	for (size_type i = _size + count - 1; i >= index + count; i--)
	{
		_alloc.construct(_data + i, _data[i-count]);
		_alloc.destroy(_data + i - count);
	}
	for (size_type i = index; i < index + count; i++, first++)
		_alloc.construct(_data + i, *first);
	_size += count;
	return _data + index;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::erase(iterator pos)
{
	size_type index = pos - _data;
	_alloc.destroy(_data + index);
	for (size_type i = index; i < _size - 1; i++)
	{
		_alloc.construct(_data + i, _data[i+1]);
		_alloc.destroy(_data + i + 1);
	}
	_size--;
	return _data + index;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::erase(iterator first, iterator last)
{
	size_type index = first - _data;
	size_type count = ft::distance(first, last);
	if (count <= 0)
		return _data + index;
	for (size_type i = index; i < index + count; i++)
		_alloc.destroy(_data + i);
	for (size_type i = index; i < _size - count; i++)
	{
		_alloc.construct(_data + i, _data[i + count]);
		_alloc.destroy(_data + i + count);
	}
	_size -= count;
	return _data + index;
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::push_back(T const& value)
{
	if (_size >= _capacity)
		_grow(_capacity * 2 + 1);
	_alloc.construct(_data + _size, value);
	_size++;
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::pop_back(void)
{
	if (_size)
	{
		_alloc.destroy(_data + (_size - 1));
		_size--;
	}
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::resize(size_type count, T value)
{
	if (count > _capacity)
		_grow(count);
	if (count > _size)
	{
		for (size_type i = _size; i < count; i++)
			_alloc.construct(_data + i, value);
	}
	else
		_shrink(count);
	_size = count;
}

//Helper

template<typename T, typename Alloc>
void
vector<T, Alloc>::_grow(size_type newCapacity)
{
	if (newCapacity > _alloc.max_size())
		throw std::length_error("max_size exceded");
	T*	newData = _alloc.allocate(newCapacity);
	if (_data)
	{
		for (size_type i = 0; i < _size; i++)
		{
			_alloc.construct(newData + i, _data[i]);
			_alloc.destroy(_data + i);
		}
		_alloc.deallocate(_data, _capacity);
	}
	_data = newData;
	_capacity = newCapacity;
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::_shrink(size_type newCapacity)
{
	T*	newData = newCapacity ? _alloc.allocate(newCapacity) : NULL;
	for (size_type i = 0; i < _size; i++)
	{
		if (i < newCapacity)
			_alloc.construct(newData + i, _data[i]);
		_alloc.destroy(_data + i);
	}
	if (_data)
		_alloc.deallocate(_data, _capacity);
	_data = newData;
	_capacity = newCapacity;
}

template<typename T, typename Alloc>
void
vector<T, Alloc>::swap(vector& other)
{
	if (this == &other)
		return;
	ft::swap(_alloc, other._alloc);
	ft::swap(_data, other._data);
	ft::swap(_size, other._size);
	ft::swap(_capacity, other._capacity);
}

//Non-member functions
template<typename T, typename Alloc>
bool
operator==(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size(); i++)
	{
		if (lhs[i] != rhs[i])
			return false;
	}
	return true;
}

template<typename T, typename Alloc>
bool
operator!=(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs)
{
	return !(lhs == rhs);
}

template<typename T, typename Alloc>
bool
operator>(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs)
{
	return rhs < lhs;
}

template<typename T, typename Alloc>
bool
operator<(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, typename Alloc>
bool
operator>=(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs)
{
	return !(lhs < rhs);
}

template<typename T, typename Alloc>
bool
operator<=(vector<T, Alloc> const& lhs, vector<T, Alloc> const& rhs)
{
	return !(rhs < lhs);
}

}
#endif
