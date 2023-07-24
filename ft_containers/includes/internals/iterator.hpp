#ifndef ITERATOR_HPP
#define ITERATOR_HPP

# include <cstddef>
# include "utils.hpp"

namespace ft
{
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename T, typename Distance> struct input_iterator
{
    typedef input_iterator_tag iterator_category;
    typedef T                  value_type;
    typedef Distance           difference_type;
    typedef T*                 pointer;
    typedef T&                 reference;
};

struct output_iterator
{
    typedef output_iterator_tag iterator_category;
    typedef void                value_type;
    typedef void                difference_type;
    typedef void                pointer;
    typedef void                reference;
};

template <typename T, typename Distance> struct forward_iterator
{
    typedef forward_iterator_tag iterator_category;
    typedef T                    value_type;
    typedef Distance             difference_type;
    typedef T*                   pointer;
    typedef T&                   reference;
};

template <typename T, typename Distance> struct bidirectional_iterator
{
    typedef bidirectional_iterator_tag iterator_category;
    typedef T                          value_type;
    typedef Distance                   difference_type;
    typedef T*                         pointer;
    typedef T&                         reference;
};

template <typename T, typename Distance> struct random_access_iterator
{
    typedef random_access_iterator_tag iterator_category;
    typedef T                          value_type;
    typedef Distance                   difference_type;
    typedef T*                         pointer;
    typedef T&                         reference;
};

template <typename Category, typename T, typename Distance = ptrdiff_t,
          typename Pointer = T*, typename Reference = T&>
struct iterator
{
    typedef Category  iterator_category;
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
};

template <typename Iterator>
struct iterator_traits
{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
};

template <typename T>
struct iterator_traits<T*>
{
    typedef random_access_iterator_tag iterator_category;
    typedef T                          value_type;
    typedef ptrdiff_t                  difference_type;
    typedef T*                         pointer;
    typedef T&                         reference;
};

template<typename Itor>
class const_reverse_iterator
{
	public:
		typedef typename iterator_traits<Itor>::iterator_category	iterator_category;
		typedef typename iterator_traits<Itor>::value_type			value_type;
		typedef typename iterator_traits<Itor>::difference_type		difference_type;
		typedef typename iterator_traits<Itor>::reference			reference;
		typedef typename iterator_traits<Itor>::pointer				pointer;
		typedef	const value_type*									const_pointer;
		typedef	const value_type&									const_reference;

	public:
		const_reverse_iterator(void);
		explicit const_reverse_iterator(Itor itor);
		template<typename T>
		const_reverse_iterator(const const_reverse_iterator<T>& other);
		const_reverse_iterator(const const_reverse_iterator& other);
		~const_reverse_iterator(void);

	protected:
		Itor	_current;

	public:
		Itor	base(void) const;
		const_reverse_iterator&	operator=(const const_reverse_iterator& other);
		const_reference			operator*(void) const;
		const_pointer			operator->(void) const;
		const_reverse_iterator&	operator++(void);
		const_reverse_iterator	operator++(int);
		const_reverse_iterator&	operator--(void);
		const_reverse_iterator	operator--(int);
		const_reverse_iterator&	operator+=(difference_type n);
		const_reverse_iterator&	operator-=(difference_type n);
		const_reverse_iterator	operator+(difference_type n) const;
		const_reverse_iterator	operator-(difference_type n) const;
		const reference			operator[](difference_type n) const;
		bool					operator!=(const const_reverse_iterator& rhs);
		bool					operator==(const const_reverse_iterator& rhs);
};

template<typename Itor>
class reverse_iterator : public const_reverse_iterator<Itor>
{
	public:
		typedef typename iterator_traits<Itor>::iterator_category	iterator_category;
		typedef typename iterator_traits<Itor>::value_type			value_type;
		typedef typename iterator_traits<Itor>::difference_type		difference_type;
		typedef typename iterator_traits<Itor>::reference			reference;
		typedef typename iterator_traits<Itor>::pointer				pointer;
		typedef	const value_type*									const_pointer;
		typedef	const value_type&									const_reference;

	public:
		reverse_iterator(void);
		explicit reverse_iterator(Itor itor);
		reverse_iterator(const reverse_iterator& other);
		template<typename T>
		reverse_iterator(const reverse_iterator<T>& other);
		~reverse_iterator(void);
	
	public:
		value_type&	operator*(void) const;
		value_type*		operator->(void) const;
};


template <typename Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&)
{
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}

template <typename Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

template <typename Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&)
{
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last,
           input_iterator_tag)
{
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last)
    {
        ++first; ++n;
    }
    return n;
}

template <typename RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last,
           random_access_iterator_tag)
{
    return last - first;
}

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
    typedef typename iterator_traits<InputIterator>::iterator_category category;
    return __distance(first, last, category());
}

template <typename InputIterator, typename Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag)
{
    while (n--) ++i;
}

template <typename BidirectionalIterator, typename Distance>
inline void __advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
{
    if (n >= 0)
        while (n--) ++i;
    else
        while (n++) --i;
}

template <typename RandomAccessIterator, typename Distance>
inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag)
{
    i += n;
}

template <typename InputIterator, typename Distance>
inline void advance(InputIterator& i, Distance n)
{
    __advance(i, n, iterator_category(i));
}

template <typename It>
It operator+(typename It::difference_type n, It const it)
{
    return advance(it, n);
}

template<typename Itor>
Itor prev(Itor it)
{
  return --it;
}


/**************************
 * CONST_REVERSE_ITERATOR *
 **************************/

template<typename Itor>
const_reverse_iterator<Itor>::const_reverse_iterator(void)
{
}

template<typename Itor>
const_reverse_iterator<Itor>::const_reverse_iterator(Itor itor)
: _current(itor)
{
}

template<typename Itor>
template<typename T>
const_reverse_iterator<Itor>::const_reverse_iterator(const const_reverse_iterator<T>& other)
: _current(other.base())
{
}

template<typename Itor>
const_reverse_iterator<Itor>::const_reverse_iterator(const const_reverse_iterator& other)
: _current(other.base())
{
}

template<typename Itor>
const_reverse_iterator<Itor>::~const_reverse_iterator(void)
{
}

template<typename Itor>
Itor
const_reverse_iterator<Itor>::base(void) const
{
	return _current;
}

template<typename Itor>
const_reverse_iterator<Itor>&
const_reverse_iterator<Itor>::operator=(const const_reverse_iterator& other)
{
	_current = other.base();
	return *this;
}

template<typename Itor>
typename const_reverse_iterator<Itor>::const_reference
const_reverse_iterator<Itor>::operator*(void) const
{
	return *ft::prev(_current);
}

template<typename Itor>
typename const_reverse_iterator<Itor>::const_pointer
const_reverse_iterator<Itor>::operator->(void) const
{
	return &*ft::prev(_current);
}

template<typename Itor>
const_reverse_iterator<Itor>&
const_reverse_iterator<Itor>::operator++(void)
{
	--_current;
	return *this;
}

template<typename Itor>
const_reverse_iterator<Itor>
const_reverse_iterator<Itor>::operator++(int)
{
	const_reverse_iterator tmp(*this);
	--_current;
	return tmp;
}

template<typename Itor>
const_reverse_iterator<Itor>&
const_reverse_iterator<Itor>::operator--(void)
{
	++_current;
	return *this;
}

template<typename Itor>
const_reverse_iterator<Itor>
const_reverse_iterator<Itor>::operator--(int)
{
	const_reverse_iterator tmp(*this);
	++_current;
	return tmp;
}

template<typename Itor>
const_reverse_iterator<Itor>&
const_reverse_iterator<Itor>::operator+=(difference_type n)
{
	_current -= n;
	return *this;
}

template<typename Itor>
const_reverse_iterator<Itor>&
const_reverse_iterator<Itor>::operator-=(difference_type n)
{
	_current += n;
	return *this;
}

template<typename Itor>
const_reverse_iterator<Itor>
const_reverse_iterator<Itor>::operator+(difference_type n) const
{
	return const_reverse_iterator(_current - n);
}

template<typename Itor>
const_reverse_iterator<Itor>
const_reverse_iterator<Itor>::operator-(difference_type n) const
{
	return const_reverse_iterator(_current + n);
}

template<typename Itor>
const typename const_reverse_iterator<Itor>::reference
const_reverse_iterator<Itor>::operator[](difference_type n) const
{
	return *(*this + n);
}

template<typename Itor>
bool
const_reverse_iterator<Itor>::operator!=(const const_reverse_iterator& rhs)
{
	return (_current != rhs._current);
}

template<typename Itor>
bool
const_reverse_iterator<Itor>::operator==(const const_reverse_iterator& rhs)
{
	return (_current == rhs._current);
}

/********************
 * REVERSE_ITERATOR *
 ********************/
template<typename Itor>
reverse_iterator<Itor>::reverse_iterator(void)
: const_reverse_iterator<Itor>()
{
}

template<typename Itor>
reverse_iterator<Itor>::reverse_iterator(Itor itor)
: const_reverse_iterator<Itor>(itor)
{
}

template<typename Itor>
reverse_iterator<Itor>::reverse_iterator(const reverse_iterator& other)
: const_reverse_iterator<Itor>()
{
	if (this != &other)
		*this = other;
}

template<typename Itor>
template<typename T>
reverse_iterator<Itor>::reverse_iterator(const reverse_iterator<T>& other)
: const_reverse_iterator<Itor>(other)
{
}

template<typename Itor>
reverse_iterator<Itor>::~reverse_iterator(void)
{
}

template<typename Itor>
typename reverse_iterator<Itor>::value_type&
reverse_iterator<Itor>::operator*(void) const
{
	return *ft::prev(this->_current);
}

template<typename Itor>
typename reverse_iterator<Itor>::value_type*
reverse_iterator<Itor>::operator->(void) const
{
	return &*ft::prev(this->_current);
}

}
#endif 
