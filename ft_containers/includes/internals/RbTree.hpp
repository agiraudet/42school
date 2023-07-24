/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RbTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:24:51 by agiraude          #+#    #+#             */
/*   Updated: 2023/02/01 09:43:19 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <functional>
# include <cstddef>
# include <memory>
# include <iostream>
# include "pair.hpp"
# include "RbItor.hpp"

namespace ft
{

template<
	typename Key,
	typename T,
	typename Cmp=std::less<Key>,
	typename Alloc=std::allocator<pair<const Key, T> >
>
class	RbTree
{
	public:
		typedef	Key								key_type;
		typedef T								mapped_type;
		typedef Cmp								key_compare;
		typedef	Alloc							allocator_type;
		typedef	typename Alloc::value_type		value_type;
		typedef typename Alloc::size_type		size_type;
		typedef typename Alloc::difference_type	difference_type;
		typedef typename Alloc::reference		reference;
		typedef typename Alloc::const_reference	const_reference;
		typedef	typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer	const_pointer;
		
	public:
		class	Node
		{
			public:
				bool		black;
				Node*		lnk[3];
				value_type*	data;

			private:
				Alloc&		_alloc;

			public:
				Node(Alloc& alloc);
				Node(Alloc& alloc, value_type& value);
				Node(Node const& other);
				~Node(void);
				Node& operator=(Node const & rhs);
		};

	public:
		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			protected:
				Cmp comp;

			public:
				value_compare(Cmp const& c);
				bool operator()(const value_type& lhs, const value_type& rhs) const;
		};
	
	//Iterators
	public:
		typedef rbitor<value_type, Node>					iterator;
		typedef const_rbitor<value_type, Node>				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::const_reverse_iterator<const_iterator>	const_reverse_iterator;

	public:
		RbTree(Cmp const& comp=Cmp(), Alloc const& alloc=Alloc());
		RbTree(RbTree const & src);
		~RbTree(void);
		RbTree& operator=(RbTree const & rhs);

	protected:
		Cmp			_comp;
		Alloc		_alloc;
		size_type	_size;
		Node*		_root;
		Node*		_anchor;

	public: //Those are directly parts of map
		allocator_type			get_allocator(void) const;

		//Iterators
		iterator				begin(void);
		const_iterator			begin(void) const;
		iterator				end(void);
		const_iterator			end(void) const;
		reverse_iterator		rbegin(void);
		const_reverse_iterator	rbegin(void) const;
		reverse_iterator		rend(void);
		const_reverse_iterator	rend(void) const;

		//Capacity
		bool					empty(void) const;
		size_type				size(void) const;
		size_type				max_size(void) const;

		//Observers
		value_compare			value_comp(void) const;
		key_compare				key_comp(void) const;

	protected:
		Node*		_nodeAdd(value_type value, Node* hint=NULL);
		void		_nodeRm(Node* node);
		Node*		_find(const value_type& key) const;
		Node*		_find(Key const& key) const;
		static void	_deleteTree(Node* node);

	private:
		void	_cpTree(Node* node);
		Node*	_findNodeParent(Node* node, Node* hint, way& dir);
		Node*	_getLastChild(Node* node, way dir);
		void	_nodeRotate(Node* node, way dir);
		void	_nodeInsert(Node* node, Node* nodeParent, way dir);
		void	_nodeErase(Node* node, Node* nodeAnchor);
		Node*	_fixAfterErase(Node* nodeChild, Node* nodeChildParent);

	/* public: //DEBUG */
	/* 	static void		printIO(Node* node); */
	/* 	static void		draw(Node* node, int depth=0); */
	/* 	Node*			getRoot(void); */
};

template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator==(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs);
template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator!=(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs);
template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator<(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs);
template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator>(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs);
template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator<=(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs);
template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator>=(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs);

/******************************
 *                            *
 *      IMPLEMENTATION        *
 *                            *
 ******************************/

/*****************
 * VALUE_COMPARE *
 *****************/
template<typename Key, typename T, typename Cmp, typename Alloc>
RbTree<Key, T, Cmp, Alloc>::value_compare::value_compare(const Cmp& c)
: comp(c)
{
}

template<typename Key, typename T, typename Cmp, typename Alloc>
bool
RbTree<Key, T, Cmp, Alloc>::value_compare::operator()(const value_type& lhs,
													  const value_type& rhs) const
{
	return comp(lhs.first, rhs.first);
}


/********
 * NODE *
 ********/
template<typename Key, typename T, typename Cmp, typename Alloc>
RbTree<Key, T, Cmp, Alloc>::Node::Node(Alloc& alloc)
: black(false), data(NULL), _alloc(alloc)
{
}

template<typename Key, typename T, typename Cmp, typename Alloc>
RbTree<Key, T, Cmp, Alloc>::Node::Node(Alloc& alloc, value_type& value)
: black(false), data(NULL), _alloc(alloc)
{
	for (unsigned int i = 0; i < 3; i++)
		lnk[i] = NULL;
	data = _alloc.allocate(1);
	_alloc.construct(data, value);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
RbTree<Key, T, Cmp, Alloc>::Node::Node(Node const& other)
{
	if (this != &other)
		*this = other;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
RbTree<Key, T, Cmp, Alloc>::Node::~Node(void)
{
	if (data)
	{
		_alloc.destroy(data);
		_alloc.deallocate(data, 1);
	}
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::Node&
RbTree<Key, T, Cmp, Alloc>::Node::operator=(Node const& rhs)
{
	if (data)
	{
		_alloc.destroy(data);
		_alloc.deallocate(data, 1);
		data = NULL;
	}
	_alloc = rhs._alloc;
	data = _alloc.allocate(1);
	_alloc.construct(data, *rhs.data);
	black = rhs.black;
	for (unsigned int i = 0; i < 3; i++)
		lnk[i] = rhs.lnk[i];
	return *this;
}

/**********
 * RBTREE *
 **********/

// Constructors

template<typename Key, typename T, typename Cmp, typename Alloc>
RbTree<Key, T, Cmp, Alloc>::RbTree(Cmp const& comp, Alloc const& alloc)
: _comp(comp), _alloc(alloc), _size(0), _root(NULL), _anchor(NULL)
{
	_anchor = new Node(_alloc);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
RbTree<Key, T, Cmp, Alloc>::RbTree(RbTree const& other)
: _comp(other._comp), _alloc(other._alloc), _size(0), _root(NULL), _anchor(NULL)
{
	if (this != &other)
		*this = other;
}


template<typename Key, typename T, typename Cmp, typename Alloc>
RbTree<Key, T, Cmp, Alloc>::~RbTree(void)
{
	_deleteTree(_root);
	if (_anchor)
		delete _anchor;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
RbTree<Key, T, Cmp, Alloc>&
RbTree<Key, T, Cmp, Alloc>::operator=(RbTree const& rhs)
{
	if (_root)
		_deleteTree(_root);
	_root = NULL;
	for (unsigned int i = 0; i < 3; i++)
		_anchor->lnk[i] = NULL;
	_cpTree(rhs._root);
	_size = rhs._size;
	return *this;
}

// MEMBER FCT

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::Node*
RbTree<Key, T, Cmp, Alloc>::_find(const value_type& value) const
{
	return _find(value.first);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::Node*
RbTree<Key, T, Cmp, Alloc>::_find(Key const& key) const
{
	Node*	node = _root;

	while (node)
	{
		if (_comp(key, node->data->first))
			node = node->lnk[l];
		else if (_comp(node->data->first, key))
			node = node->lnk[r];
		else
			break;
	}
	return node;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::Node*
RbTree<Key, T, Cmp, Alloc>::_nodeAdd(value_type value, Node* hint)
{
	Node*	newNode = new Node(_alloc, value);

	if (!_root)
	{
		_root = newNode;
		_root->black = true;
		_anchor->lnk[l] = newNode;
		_anchor->lnk[p] = newNode;
		_anchor->lnk[r] = newNode;
		_size++;
		return newNode;
	}

	way		dir			= l;
	Node*	nodeParent	= _findNodeParent(newNode, hint, dir);
	_nodeInsert(newNode, nodeParent, dir);
	_size++;
	_anchor->lnk[p] = _root;
	return newNode;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::Node*
RbTree<Key, T, Cmp, Alloc>::_findNodeParent(Node* node, Node* hint, way& dir)
{
	Node*	nodeParent = _root;

	if (hint)
		dir = r;

	while (nodeParent)
	{
		if (_comp(node->data->first, nodeParent->data->first))
			dir = l;
		else if (_comp(nodeParent->data->first, node->data->first))
			dir = r;
		if (!nodeParent->lnk[dir])
			break;
		nodeParent = nodeParent->lnk[dir];
	}
	return nodeParent;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::Node*
RbTree<Key, T, Cmp, Alloc>::_getLastChild(Node* node, way dir)
{
	while (node && node->lnk[dir])
		node = node->lnk[dir];
	return node;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
void
RbTree<Key, T, Cmp, Alloc>::_nodeRm(Node* node)
{
	_nodeErase(node, _anchor);
	if (node)
		delete node;
	_size--;
	return ;
}

/****************
 * Parts of map *
 ****************/

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::allocator_type
RbTree<Key, T, Cmp, Alloc>::get_allocator(void) const
{
	return _alloc;
}

/* ACCESS */
template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::iterator
RbTree<Key, T, Cmp, Alloc>::begin(void)
{
	if (_size)
		return (iterator(_anchor->lnk[l], _anchor));
	return (iterator(_anchor, _anchor));
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::const_iterator
RbTree<Key, T, Cmp, Alloc>::begin(void) const
{
	if (_size)
		return (const_iterator(_anchor->lnk[l], _anchor));
	return (const_iterator(_anchor, _anchor));
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::iterator
RbTree<Key, T, Cmp, Alloc>::end(void)
{
	return (iterator(_anchor, _anchor));
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::const_iterator
RbTree<Key, T, Cmp, Alloc>::end(void) const
{
	return (const_iterator(_anchor, _anchor));
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::reverse_iterator
RbTree<Key, T, Cmp, Alloc>::rbegin(void)
{
	return reverse_iterator(iterator(_anchor, _anchor));
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::const_reverse_iterator
RbTree<Key, T, Cmp, Alloc>::rbegin(void) const
{
	return const_reverse_iterator(const_iterator(_anchor, _anchor));
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::reverse_iterator
RbTree<Key, T, Cmp, Alloc>::rend(void)
{
	if (_size)
		return reverse_iterator(iterator(_anchor->lnk[l], _anchor));
	return rbegin();
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::const_reverse_iterator
RbTree<Key, T, Cmp, Alloc>::rend(void) const
{
	if (_size)
		return const_reverse_iterator(const_iterator(_anchor->lnk[l], _anchor));
	return rbegin();
}


/* CAPACITY */
template<typename Key, typename T, typename Cmp, typename Alloc>
bool
RbTree<Key, T, Cmp, Alloc>::empty(void) const
{
	return (_size == 0);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::size_type
RbTree<Key, T, Cmp, Alloc>::size(void) const
{
	return _size;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::size_type
RbTree<Key, T, Cmp, Alloc>::max_size(void) const
{
	return _alloc.max_size();
}

/***********
 * HELPERS *
 ***********/

template<typename Key, typename T, typename Cmp, typename Alloc>
void
RbTree<Key, T, Cmp, Alloc>::_cpTree(Node* node)
{
	if (!node)
		return;
	_nodeAdd(*node->data);
	_cpTree(node->lnk[l]);
	_cpTree(node->lnk[r]);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
void
RbTree<Key, T, Cmp, Alloc>::_deleteTree(Node* node)
{
	if (!node)
		return;
	_deleteTree(node->lnk[l]);
	_deleteTree(node->lnk[r]);
	delete node;
}

/*********************
 * TREE MANIPULATION *
 *********************/

template<typename Key, typename T, typename Cmp, typename Alloc>
void
RbTree<Key, T, Cmp, Alloc>::_nodeRotate(Node* node, way dir)
{
	way			rdir = (dir == l) ? r : l;
	Node* nodeTemp = node->lnk[rdir];

	node->lnk[rdir] = nodeTemp->lnk[dir];

	if (nodeTemp->lnk[dir])
		nodeTemp->lnk[dir]->lnk[p] = node;
	nodeTemp->lnk[p] = node->lnk[p];

	if (node == _root)
		_root = nodeTemp;
	else if (node == node->lnk[p]->lnk[dir])
		node->lnk[p]->lnk[dir] = nodeTemp;
	else
		node->lnk[p]->lnk[rdir] = nodeTemp;

	nodeTemp->lnk[dir] = node;
	node->lnk[p] = nodeTemp;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
void
RbTree<Key, T, Cmp, Alloc>::_nodeInsert(Node* node, Node* nodeParent, way dir)
{
	node->lnk[p] = nodeParent;

	nodeParent->lnk[dir] = node;
	if(dir == l && _anchor->lnk[l] == nodeParent)
		_anchor->lnk[l] = node;
	else if (dir == r && nodeParent == _anchor->lnk[r])
		_anchor->lnk[r] = node;
	
	// Rebalance the tree.
	while((node != _root) && (node->lnk[p]->black == false)) 
	{
		Node* const nodeParentParent = node->lnk[p]->lnk[p];

		dir = (node->lnk[p] == nodeParentParent->lnk[l]) ? r : l;
		way rdir = (dir == l) ? r : l;

		Node* const nodeTemp = nodeParentParent->lnk[dir];

		if(nodeTemp && (nodeTemp->black == false)) 
		{
			node->lnk[p]->black = true;
			nodeTemp->black = true;
			nodeParentParent->black = false;
			node = nodeParentParent;
		}
		else 
		{
			if(node->lnk[p] && node == node->lnk[p]->lnk[dir]) 
			{
				node = node->lnk[p];
				_nodeRotate(node, rdir);
			}

			node->lnk[p]->black = true;
			nodeParentParent->black = false;
			_nodeRotate(nodeParentParent, dir);
		}
	}
	_root->black = true;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
void
RbTree<Key, T, Cmp, Alloc>::_nodeErase(Node* node, Node* nodeAnchor)
{
	Node*& nodeLeftmostRef  = nodeAnchor->lnk[l];
	Node*& nodeRightmostRef = nodeAnchor->lnk[r];
	Node*  nodeSuccessor    = node;
	Node*  nodeChild        = NULL;
	Node*  nodeChildParent  = NULL;

	if(nodeSuccessor->lnk[l] == NULL)		// node has at most one non-NULL child.
		nodeChild = nodeSuccessor->lnk[r];	// nodeChild might be null.
	else if(nodeSuccessor->lnk[r] == NULL)	// node has exactly one non-NULL child.
		nodeChild = nodeSuccessor->lnk[l];	// nodeChild is not null.
	else									// node has two non-NULL childs. 
	{
		nodeSuccessor = nodeSuccessor->lnk[r];
		while(nodeSuccessor->lnk[l])
			nodeSuccessor = nodeSuccessor->lnk[l];
		nodeChild = nodeSuccessor->lnk[r];
	}

	if(nodeSuccessor == node) // node was a leaf
	{
		nodeChildParent = nodeSuccessor->lnk[p];
		if(nodeChild) 
			nodeChild->lnk[p] = nodeSuccessor->lnk[p];
		if (node == _root)
			_root = nodeChild;
		else 
		{
			if(node == node->lnk[p]->lnk[l]) // node is a left child
				node->lnk[p]->lnk[l]  = nodeChild;
			else
				node->lnk[p]->lnk[r] = nodeChild;
		}
		if(node == nodeLeftmostRef)
		{
			if(node->lnk[r] && nodeChild)
				nodeLeftmostRef = _getLastChild(nodeChild, l); 
			else
				nodeLeftmostRef = node->lnk[p];
		}
		if(node == nodeRightmostRef)
		{
			if(node->lnk[l] && nodeChild)
				nodeRightmostRef = _getLastChild(nodeChild, r);
			else
				nodeRightmostRef = node->lnk[p];
		}
	}
	else // else (nodeSuccessor != node)
	{
		node->lnk[l]->lnk[p] = nodeSuccessor; 
		nodeSuccessor->lnk[l] = node->lnk[l];

		if(nodeSuccessor == node->lnk[r])
			nodeChildParent = nodeSuccessor;
		else
		{
			nodeChildParent = nodeSuccessor->lnk[p];

			if(nodeChild)
				nodeChild->lnk[p] = nodeChildParent;

			nodeChildParent->lnk[l] = nodeChild;

			nodeSuccessor->lnk[r] = node->lnk[r];
			node->lnk[r]->lnk[p] = nodeSuccessor;
		}

		if (node == _root)
			_root = nodeSuccessor;
		else if(node == node->lnk[p]->lnk[l])
			node->lnk[p]->lnk[l] = nodeSuccessor;
		else 
			node->lnk[p]->lnk[r] = nodeSuccessor;

		nodeSuccessor->lnk[p] = node->lnk[p];
		ft::swap(node->black, nodeSuccessor->black);
	}

	if(node->black) 
	{ 
		nodeChild = _fixAfterErase(nodeChild, nodeChildParent);
		if(nodeChild)
			nodeChild->black = true;
	}
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::Node*
RbTree<Key, T, Cmp, Alloc>::_fixAfterErase(Node* nodeChild, Node* nodeChildParent)
{
	while((nodeChild != _root) && ((nodeChild == NULL) || (nodeChild->black)))
	{
		way	dir		= (nodeChild == nodeChildParent->lnk[l]) ? r : l;
		way	rdir	= (dir == r) ? l : r;
		Node* nodeTemp = nodeChildParent->lnk[dir];

		if(!nodeTemp->black) 
		{
			nodeTemp->black = true;
			nodeChildParent->black = false;
			_nodeRotate(nodeChildParent, rdir);
			nodeTemp = nodeChildParent->lnk[dir];
		}

		if(((nodeTemp->lnk[rdir] == NULL) || (nodeTemp->lnk[rdir]->black)) &&
			((nodeTemp->lnk[dir] == NULL) || (nodeTemp->lnk[dir]->black))) 
		{
			nodeTemp->black = false;
			nodeChild = nodeChildParent;
			nodeChildParent = nodeChildParent->lnk[p];
		} 
		else 
		{
			if((nodeTemp->lnk[dir] == NULL) || (nodeTemp->lnk[dir]->black)) 
			{
				nodeTemp->lnk[rdir]->black = true;
				nodeTemp->black = false;
				_nodeRotate(nodeTemp, dir);
				nodeTemp = nodeChildParent->lnk[dir];
			}

			nodeTemp->black = nodeChildParent->black;
			nodeChildParent->black = true;

			if(nodeTemp->lnk[dir]) 
				nodeTemp->lnk[dir]->black = true;

			_nodeRotate(nodeChildParent, rdir);
			break;
		}
	}
	return nodeChild;
}

/*************
 * OBSERVERS *
 *************/
template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::value_compare
RbTree<Key, T, Cmp, Alloc>::value_comp(void) const
{
	return value_compare(_comp);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
typename RbTree<Key, T, Cmp, Alloc>::key_compare
RbTree<Key, T, Cmp, Alloc>::key_comp(void) const
{
	return _comp;
}

/***************
 * COMPARAISON *
 ***************/

template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator==(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	typename RbTree<Key, T, Cmp, Alloc>::const_iterator	cilt = lhs.begin();
	typename RbTree<Key, T, Cmp, Alloc>::const_iterator	cilte = lhs.end();
	typename RbTree<Key, T, Cmp, Alloc>::const_iterator	cirt = rhs.begin();
	
	while (cilt != cilte)
	{
		if (!(cilt->first == cirt->first) || !(cilt->second == cirt->second))
			return false;
		cilt++;
		cirt++;
	}
	return true;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator!=(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs)
{
	return !(lhs == rhs);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator<(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator>(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs)
{
	return rhs < lhs;
}

template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator<=(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs)
{
	return !(rhs < lhs);
}

template<typename Key, typename T, typename Cmp, typename Alloc>
bool operator>=(const RbTree<Key, T, Cmp, Alloc>& lhs, const RbTree<Key, T, Cmp, Alloc>& rhs)
{
	return !(lhs < rhs);
}

/*********
 * DEBUG *
 *********/

/* template<typename Key, typename T, typename Cmp, typename Alloc> */
/* typename RbTree<Key, T, Cmp, Alloc>::Node* */
/* RbTree<Key, T, Cmp, Alloc>::getRoot(void) */
/* { */
/* 	return _root; */
/* } */

/* template<typename Key, typename T, typename Cmp, typename Alloc> */
/* void */
/* RbTree<Key, T, Cmp, Alloc>::printIO(Node* node) */
/* { */
/* 	if (!node) */
/* 		return; */
/* 	printIO(node->lnk[l]); */
/* 	if (node->black) */
/* 		std::cout << "\033[1;34m" << node->data->second << "\033[m "; */
/* 	else */
/* 		std::cout << "\033[1;31m" << node->data->second << "\033[m "; */
/* 	printIO(node->lnk[r]); */
/* } */

/* template<typename Key, typename T, typename Cmp, typename Alloc> */
/* void */
/* RbTree<Key, T, Cmp, Alloc>::draw(Node* node, int depth) */
/* { */
/* 	if (!node) */
/* 		return; */
/* 	draw(node->lnk[r], depth + 1); */
/* 	for (int i = 0; i < depth; i++) */
/* 		std::cout << "   "; */
/* 	if (node->black) */
/* 		std::cout << "\033[1;34m" << node->data->first << "\033[m " << std::endl; */
/* 	else */
/* 		std::cout << "\033[1;31m" << node->data->first << "\033[m " << std::endl; */
/* 	draw(node->lnk[l], depth + 1); */
/* } */

}
#endif
