/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RbItor.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:08:53 by agiraude          #+#    #+#             */
/*   Updated: 2023/01/30 15:13:27 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBITOR_HPP
# define RBITOR_HPP

# include "iterator.hpp"

namespace ft
{

enum	way
{
	l = 0,
	p = 1,
	r = 2
};

template<typename T, typename Node>
class	const_rbitor
{
	public:
		typedef size_t								size_type;
		typedef ptrdiff_t							difference_type;
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef bidirectional_iterator_tag			iterator_category;

	public:
		const_rbitor(void);
		const_rbitor(Node* node, Node* anchor);
		const_rbitor(const const_rbitor& other);
		~const_rbitor(void);
		
	protected:
		Node*	_current;
		Node*	_anchor;

	public:
		Node*			base(void) const;
		Node*			anc(void) const;
		const_rbitor&	operator=(const const_rbitor& other);
		const T&		operator*(void) const;
		const T*		operator->(void) const;
		const_rbitor&	operator++(void);
		const_rbitor	operator++(int);
		const_rbitor&	operator--(void);
		const_rbitor	operator--(int);
		bool			operator!=(const const_rbitor& rhs);
		bool			operator==(const const_rbitor& rhs);

	protected:
		Node*	_mv(Node* node, way dir);
		Node*	_getLastChild(Node* node, way dir);
};

template<typename T, typename Node>
class	rbitor : public const_rbitor<T, Node>
{
	public:
		rbitor(void);
		rbitor(Node* node, Node* anchor);
		rbitor(const rbitor& other);
		~rbitor(void);

	public:
		rbitor&	operator=(const const_rbitor<T, Node>& rhs);
		T&		operator*(void) const;
		T*		operator->(void) const;
		rbitor&	operator++(void);
		rbitor	operator++(int);
		rbitor&	operator--(void);
		rbitor	operator--(int);
};


/*******************************
 * CONST_RBITOR IMPLEMENTATION *
 *******************************/

template<typename T, typename Node>
const_rbitor<T, Node>::const_rbitor(void)
: _current(NULL), _anchor(NULL)
{
}

template<typename T, typename Node>
const_rbitor<T, Node>::const_rbitor(Node* node, Node* anchor)
: _current(node), _anchor(anchor)
{
}

template<typename T, typename Node>
const_rbitor<T, Node>::const_rbitor(const const_rbitor& other)
{
	if (this != &other)
		*this = other;
}

template<typename T, typename Node>
const_rbitor<T, Node>::~const_rbitor(void)
{
}

template<typename T, typename Node>
Node*
const_rbitor<T, Node>::base(void) const
{
	return _current;
}

template<typename T, typename Node>
Node*
const_rbitor<T, Node>::anc(void) const
{
	return _anchor;
}

template<typename T, typename Node>
const_rbitor<T, Node>&
const_rbitor<T, Node>::operator=(const const_rbitor& rhs)
{
	_anchor = rhs._anchor;
	_current = rhs._current;
	return *this;
}

template<typename T, typename Node>
const T&
const_rbitor<T, Node>::operator*(void) const
{
	return *_current->data;
}

template<typename T, typename Node>
const T*
const_rbitor<T, Node>::operator->(void) const
{
	return _current->data;
}

template<typename T, typename Node>
const_rbitor<T, Node>&
const_rbitor<T, Node>::operator++(void)
{
	if (_current == _anchor->lnk[r])
		_current = _anchor;
	else
		_current = _mv(_current, r);
	return *this;
}

template<typename T, typename Node>
const_rbitor<T, Node>
const_rbitor<T, Node>::operator++(int)
{
	const_rbitor	tmp(*this);
	if (_current == _anchor->lnk[r])
		_current = _anchor;
	else
		_current = _mv(_current, r);
	return tmp;
}

template<typename T, typename Node>
const_rbitor<T, Node>&
const_rbitor<T, Node>::operator--(void)
{
	if (_current == _anchor)
		_current = _anchor->lnk[r];
	else
		_current = _mv(_current, l);
	return *this;
}

template<typename T, typename Node>
const_rbitor<T, Node>
const_rbitor<T, Node>::operator--(int)
{
	const_rbitor	tmp(*this);
	if (_current == _anchor)
		_current = _anchor->lnk[r];
	else
		_current = _mv(_current, l);
	return tmp;
}

template<typename T, typename Node>
bool
const_rbitor<T, Node>::operator!=(const const_rbitor& rhs)
{
	return (_current != rhs._current);
}

template<typename T, typename Node>
bool
const_rbitor<T, Node>::operator==(const const_rbitor& rhs)
{
	return (_current == rhs._current);
}

template<typename T, typename Node>
Node*
const_rbitor<T, Node>::_getLastChild(Node* node, way dir)
{
	while (node && node->lnk[dir])
		node = node->lnk[dir];
	return node;
}

template<typename T, typename Node>
Node*
const_rbitor<T, Node>::_mv(Node* node, way dir)
{
	way rdir = (dir == l) ? r : l;

	if (!node)
		return node;
	if (node->lnk[dir])
		return _getLastChild(node->lnk[dir], rdir);
	while (node)
	{
		if (node->lnk[p]->lnk[rdir] == node)
			return node->lnk[p];
		node = node->lnk[p];
	}
	return NULL; //Should never happen
}

/*************************
 * RBITOR IMPLEMENTATION *
 *************************/

template<typename T, typename Node>
rbitor<T, Node>::rbitor(void)
: const_rbitor<T, Node>()
{
}

template<typename T, typename Node>
rbitor<T, Node>::rbitor(Node* node, Node* anchor)
: const_rbitor<T, Node>(node, anchor)
{
}

template<typename T, typename Node>
rbitor<T, Node>::rbitor(const rbitor& other)
: const_rbitor<T, Node>()
{
	if (this != &other)
		*this = other;
}

template<typename T, typename Node>
rbitor<T, Node>::~rbitor(void)
{
}

template<typename T, typename Node>
rbitor<T, Node>&
rbitor<T, Node>::operator=(const const_rbitor<T, Node>& rhs)
{
	this->_anchor = rhs.anc();
	this->_current = rhs.base();
	return *this;
}

template<typename T, typename Node>
T&
rbitor<T, Node>::operator*(void) const
{
	return *this->_current->data;
}

template<typename T, typename Node>
T*
rbitor<T, Node>::operator->(void) const
{
	return this->_current->data;
}

template<typename T, typename Node>
rbitor<T, Node>&
rbitor<T, Node>::operator++(void)
{
	if (this->_current == this->_anchor->lnk[r])
		this->_current = this->_anchor;
	else
		this->_current = this->_mv(this->_current, r);
	return *this;
}

template<typename T, typename Node>
rbitor<T, Node>
rbitor<T, Node>::operator++(int)
{
	rbitor	tmp(*this);
	if (this->_current == this->_anchor->lnk[r])
		this->_current = this->_anchor;
	else
		this->_current = this->_mv(this->_current, r);
	return tmp;
}

template<typename T, typename Node>
rbitor<T, Node>&
rbitor<T, Node>::operator--(void)
{
	if (this->_current == this->_anchor)
		this->_current = this->_anchor->lnk[r];
	else
		this->_current = this->_mv(this->_current, l);
	return *this;
}

template<typename T, typename Node>
rbitor<T, Node>
rbitor<T, Node>::operator--(int)
{
	rbitor	tmp(*this);
	if (this->_current == this->_anchor)
		this->_current = this->_anchor->lnk[r];
	else
		this->_current = this->_mv(this->_current, l);
	return tmp;
}

} //namespace ft
#endif
