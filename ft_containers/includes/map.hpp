/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:17:52 by agiraude          #+#    #+#             */
/*   Updated: 2023/01/31 10:18:26 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "utils.hpp"
# include "internals/RbTree.hpp"

namespace ft
{

template<
	typename Key,
	typename T,
	typename Cmp=std::less<Key>,
	typename Alloc=std::allocator<pair<const Key, T> >
>
class	map : public RbTree<Key, T, Cmp, Alloc>
{
	private:
		typedef typename RbTree<Key, T, Cmp, Alloc>::Node	Node;

	public:
		typedef	Key														key_type;
		typedef T														mapped_type;
		typedef Cmp														key_compare;
		typedef	Alloc													allocator_type;
		typedef	typename RbTree<Key, T, Cmp, Alloc>::value_type			value_type;
		typedef typename RbTree<Key, T, Cmp, Alloc>::size_type			size_type;
		typedef typename RbTree<Key, T, Cmp, Alloc>::difference_type	difference_type;
		typedef typename RbTree<Key, T, Cmp, Alloc>::reference			reference;
		typedef typename RbTree<Key, T, Cmp, Alloc>::const_reference	const_reference;
		typedef	typename RbTree<Key, T, Cmp, Alloc>::pointer			pointer;
		typedef typename RbTree<Key, T, Cmp, Alloc>::const_pointer		const_pointer;
		typedef typename RbTree<Key, T, Cmp, Alloc>::iterator			iterator;
		typedef typename RbTree<Key, T, Cmp, Alloc>::const_iterator		const_iterator;

	public:
		map(void);
		explicit map(const Cmp& comp, const Alloc& alloc=Alloc());
		template<typename InputIt>
		map(InputIt first, InputIt last,
			const Cmp& comp=Cmp(),
			const Alloc& alloc=Alloc(),
			typename enable_if<!is_integral<InputIt>::value>::type* = 0);
		map(map const& other);
		~map(void);

		//Element access
		T&			at(Key const& key);
		T const&	at(Key const& key) const;
		T&			operator[](Key const& key);

		//Modifiers
		void					clear(void);
		pair<iterator, bool>	insert(const value_type& value);
		iterator				insert(iterator pos, value_type const& value);
		template<typename InputIt>
		void					insert(InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value>::type* = 0);
		void					erase(iterator pos);
		void					erase(iterator first, iterator last);
		size_type				erase(const Key& key);
		void					swap(map& other);

		//Look Up
		size_type					count(const Key& key) const;
		iterator					find(const Key& key);
		const_iterator				find(const Key& key) const; 
		pair<iterator, iterator>	equal_range(const Key& key);	
		pair<const_iterator, const_iterator>
									equal_range(const Key& key) const;
		iterator					lower_bound(const Key& key);
		const_iterator				lower_bound(const Key& key) const;
		iterator					upper_bound(const Key& key);
		const_iterator				upper_bound(const Key& key) const;
};

template<typename Key, typename T, typename Cmp, typename Alloc>
void swap(RbTree<Key, T, Cmp, Alloc>& lhs, RbTree<Key, T, Cmp, Alloc>& rhs);

/*********************
 *   IMPLEMENTATION  *
 *********************/

/* CONSTRUCTORS */

template<typename Key, typename T, typename Cmp, typename Alloc>
map<Key, T, Cmp, Alloc>::map(void)
{
}

template<typename Key, typename T, typename Cmp, typename Alloc>
map<Key, T, Cmp, Alloc>::map(const Cmp& comp, const Alloc& alloc)
: RbTree<Key, T, Cmp, Alloc>(comp, alloc)
{
}

template<typename Key, typename T, typename Cmp, typename Alloc>
template<typename InputIt>
map<Key, T, Cmp, Alloc>::map(InputIt first, InputIt last, const Cmp& comp, const Alloc& alloc, typename enable_if<!is_integral<InputIt>::value>::type*)
: RbTree<Key, T, Cmp, Alloc>(comp, alloc)
{
	insert(first, last);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
map<Key, T, Cmp, Alloc>::map(const map& other)
: RbTree<Key, T, Cmp, Alloc>()
{
	if (this != &other)
		*this = other;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
map<Key, T, Cmp, Alloc>::~map(void)
{
}

/* ELEMENT ACCESS */

template<typename Key, typename T, typename Cmp, typename Alloc>
T&
map<Key, T, Cmp, Alloc>::at(const Key& key)
{
	Node*	elem = this->_find(key);

	if (!elem)
		throw std::out_of_range("map::at");
	return elem->data->second;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
const T&
map<Key, T, Cmp, Alloc>::at(const Key& key) const
{
	Node*	elem = this->_find(key);

	if (!elem)
		throw std::out_of_range("map::at");
	return elem->data->second;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
T&
map<Key, T, Cmp, Alloc>::operator[](const Key& key)
{
	Node*	elem = this->_find(key);

	if (!elem)
		elem = this->_nodeAdd(ft::make_pair(key, T()));
	return elem->data->second;
}

/* MODIFIERS */

template<typename Key, typename T, typename Cmp, typename Alloc>
void
map<Key, T, Cmp, Alloc>::clear(void)
{
	this->_deleteTree(this->_root);
	this->_root = NULL;
	for (unsigned int i = 0; i < 3; i++)
		this->_anchor->lnk[i] = NULL;
	this->_size = 0;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
void
map<Key, T, Cmp, Alloc>::erase(iterator pos)
{
	erase(pos->first);
	/* this->_nodeRm(pos.base()); */
}

template<typename Key, typename T, typename Cmp, typename Alloc>
void
map<Key, T, Cmp, Alloc>::erase(iterator first, iterator last)
{
	if (first == last)
		return;
	while (first != last)
	{
		iterator	tmp(first);
		++tmp;
		erase(first);
		first = tmp;
	}
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::size_type
map<Key, T, Cmp, Alloc>::erase(const Key& key)
{
	Node*	elem = this->_find(key);

	if (!elem)
		return 0;
	this->_nodeRm(elem);
	return 1;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
void
map<Key, T, Cmp, Alloc>::swap(map& other)
{
	if (this == &other)
		return;
	ft::swap(this->_size, other._size);
	ft::swap(this->_alloc, other._alloc);
	ft::swap(this->_comp, other._comp);
	ft::swap(this->_root, other._root);
	ft::swap(this->_anchor, other._anchor);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
pair<typename map<Key, T, Cmp, Alloc>::iterator, bool>
map<Key, T, Cmp, Alloc>::insert(const value_type& value)
{
	Node*	elem = this->_find(value.first);

	if (elem)
		return ft::make_pair(iterator(elem, this->_anchor), false);
	return ft::make_pair(iterator(this->_nodeAdd(value), this->_anchor), true);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename map<Key, T, Cmp, Alloc>::iterator
map<Key, T, Cmp, Alloc>::insert(iterator pos, const value_type& value)
{
	Node*	elem = this->_find(value.first);

	if (elem)
		return iterator(elem, this->_anchor);
	return iterator(this->_nodeAdd(value, pos.base()), this->_anchor);
}
	
template<typename Key, typename T, typename Cmp, typename Alloc>
template<typename InputIt>
void
map<Key, T, Cmp, Alloc>::insert(InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value>::type*)
{
	if (first == last)
		return;
	for (; first != last; first++)
	{
		if (!this->_find(*first))
			this->_nodeAdd(*first);
	}
}

/* LOOK UP */

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::size_type
map<Key, T, Cmp, Alloc>::count(const Key& key) const
{
	const Node*	elem = this->_find(key);

	if (elem)
		return 1;
	return 0;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename map<Key, T, Cmp, Alloc>::iterator
map<Key, T, Cmp, Alloc>::find(const Key& key)
{
	Node*	elem = this->_find(key);

	if (!elem)
		return this->end();
	return iterator(elem, this->_anchor);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename map<Key, T, Cmp, Alloc>::const_iterator
map<Key, T, Cmp, Alloc>::find(const Key& key) const
{
	Node*	elem = this->_find(key);

	if (!elem)
		return this->end();
	return const_iterator(elem, this->_anchor);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
pair<typename map<Key, T, Cmp, Alloc>::iterator, typename map<Key, T, Cmp, Alloc>::iterator>
map<Key, T, Cmp, Alloc>::equal_range(const Key& key)
{
	return ft::make_pair(lower_bound(key), upper_bound(key));
}

template<typename Key, typename T, typename Cmp, typename Alloc>
pair<typename map<Key, T, Cmp, Alloc>::const_iterator, typename map<Key, T, Cmp, Alloc>::const_iterator>
map<Key, T, Cmp, Alloc>::equal_range(const Key& key) const
{
	return ft::make_pair(lower_bound(key), upper_bound(key));
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename map<Key, T, Cmp, Alloc>::iterator
map<Key, T, Cmp, Alloc>::lower_bound(const Key& key)
{
	iterator	it = this->begin();
	iterator	ite = this->end();

	while (it != ite && this->_comp(it->first, key))
		it++;
	return it;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename map<Key, T, Cmp, Alloc>::const_iterator
map<Key, T, Cmp, Alloc>::lower_bound(const Key& key) const
{
	const_iterator	it = this->begin();
	const_iterator	ite = this->end();

	while (it != ite && this->_comp(it->first, key))
		it++;
	return it;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename map<Key, T, Cmp, Alloc>::iterator
map<Key, T, Cmp, Alloc>::upper_bound(const Key& key)
{
	iterator	it = this->begin();
	iterator	ite = this->end();

	while (it != ite && !this->_comp(key, it->first))
		it++;
	return it;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename map<Key, T, Cmp, Alloc>::const_iterator
map<Key, T, Cmp, Alloc>::upper_bound(const Key& key) const
{
	const_iterator	it = this->begin();
	const_iterator	ite = this->end();

	while (it != ite && !this->_comp(key, it->first))
		it++;
	return it;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
void swap(RbTree<Key, T, Cmp, Alloc>& lhs, RbTree<Key, T, Cmp, Alloc>& rhs)
{
	lhs.swap(rhs);
}

} //namespace: ft
#endif
