#ifndef VECITOR_HPP
# define VECITOR_HPP

#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{

template <typename Iterator>
class VecRevItor
{
    public:
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename iterator_traits<Iterator>::value_type value_type;
        typedef typename iterator_traits<Iterator>::difference_type difference_type;
        typedef typename iterator_traits<Iterator>::reference reference;
        typedef typename iterator_traits<Iterator>::pointer pointer;

    public:
        VecRevItor(void);
        explicit VecRevItor(Iterator i);
        template <typename U>
        VecRevItor(const VecRevItor<U>& other);
        ~VecRevItor(void);

        Iterator base(void) const;

        reference   operator*(void) const;
        pointer     operator->(void) const;
        VecRevItor& operator++(void);
        VecRevItor  operator++(int);
        VecRevItor& operator--(void);
        VecRevItor  operator--(int);
        VecRevItor& operator+=(difference_type n);
        VecRevItor& operator-=(difference_type n);
        VecRevItor  operator+(difference_type n) const;
        VecRevItor  operator-(difference_type n) const;
        reference   operator[](difference_type n) const;

    protected:
        Iterator _current;
};	

template <typename Iterator>
class const_VecRevItor : public VecRevItor<Iterator>
{
    public:
        typedef typename VecRevItor<Iterator>::difference_type difference_type;
        typedef typename VecRevItor<Iterator>::value_type value_type;
        typedef typename VecRevItor<Iterator>::iterator_category iterator_category;
        typedef typename VecRevItor<Iterator>::reference  reference;
        typedef typename VecRevItor<Iterator>::pointer    pointer;

    public:
        const_VecRevItor();
        const_VecRevItor(Iterator iter);
        const_VecRevItor(const VecRevItor<Iterator>& other);
        template<typename T>
        const_VecRevItor(const VecRevItor<T>& other);

        const reference operator*(void) const;
        const pointer operator->(void) const;
}; 

template<typename It1, typename It2>
bool operator==(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs);
template<typename It1, typename It2>
bool operator!=(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs);
template<typename It1, typename It2>
bool operator>(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs);
template<typename It1, typename It2>
bool operator<(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs);
template<typename It1, typename It2>
bool operator>=(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs);
template<typename It1, typename It2>
bool operator<=(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs);
template<typename It1, typename It2>
typename VecRevItor<It1>::difference_type operator-(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs);

/******************
 * IMPLEMENTATION *
 ******************/
template <typename Iterator>
VecRevItor<Iterator>::VecRevItor(void)
{
}

template <typename Iterator>
VecRevItor<Iterator>::VecRevItor(Iterator it)
: _current(it)
{
}

template <typename Iterator>
template <typename U>
VecRevItor<Iterator>::VecRevItor(const VecRevItor<U>& other)
: _current(other.base())
{
}

template <typename Iterator>
VecRevItor<Iterator>::~VecRevItor(void)
{
}

template <typename Iterator>
Iterator
VecRevItor<Iterator>::base(void) const
{
    return _current;
}

template <typename Iterator>
typename VecRevItor<Iterator>::reference
VecRevItor<Iterator>::operator*(void) const
{
    return *ft::prev(_current);
}

template <typename Iterator>
typename VecRevItor<Iterator>::pointer
VecRevItor<Iterator>::operator->(void) const
{
    return &*ft::prev(_current);
}

template <typename Iterator>
VecRevItor<Iterator>&
VecRevItor<Iterator>::operator++()
{
    --_current;
    return *this;
}

template <typename Iterator>
VecRevItor<Iterator>
VecRevItor<Iterator>::operator++(int)
{
    VecRevItor tmp(*this);
    --_current;
    return tmp;
}

template <typename Iterator>
VecRevItor<Iterator>&
VecRevItor<Iterator>::operator--()
{
    ++_current;
    return *this;
}

template <typename Iterator>
VecRevItor<Iterator>
VecRevItor<Iterator>::operator--(int)
{
    VecRevItor tmp(*this);
    ++_current;
    return tmp;
}

template <typename Iterator>
VecRevItor<Iterator>&
VecRevItor<Iterator>::operator+=(difference_type n)
{
    _current -= n;
    return *this;
}

template <typename Iterator>
VecRevItor<Iterator>&
VecRevItor<Iterator>::operator-=(difference_type n)
{
    _current += n;
    return *this;
}

template <typename Iterator>
VecRevItor<Iterator>
VecRevItor<Iterator>::operator+(difference_type n) const
{
    return VecRevItor(_current - n);
}

template <typename Iterator>
VecRevItor<Iterator>
VecRevItor<Iterator>::operator-(difference_type n) const
{
    return VecRevItor(_current + n);
}

template <typename Iterator>
typename VecRevItor<Iterator>::reference
VecRevItor<Iterator>::operator[](difference_type n) const
{
    return *(*this + n);
}

template <typename Iterator>
VecRevItor<Iterator>
operator+(typename VecRevItor<Iterator>::difference_type n, const VecRevItor<Iterator>& it)
{
    return it + n;
}

template <typename Iterator>
VecRevItor<Iterator> make_VecRevItor(Iterator i)
{
    return VecRevItor<Iterator>(i);
}

template<typename It1, typename It2>
bool
operator==(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs)
{
    return lhs.base() == rhs.base();
}

template<typename It1, typename It2>
bool
operator!=(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs)
{
    return lhs.base() != rhs.base();
}

template<typename It1, typename It2>
bool
operator>(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs)
{
    return lhs.base() < rhs.base();
}

template<typename It1, typename It2>
bool
operator<(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs) 
{
    return lhs.base() > rhs.base();
}

template<typename It1, typename It2>
bool
operator>=(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs) 
{
    return lhs.base() <= rhs.base();
}

template<typename It1, typename It2>
bool
operator<=(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs) 
{
    return lhs.base() >= rhs.base();
}

template<typename It1, typename It2>
typename VecRevItor<It1>::difference_type
operator-(VecRevItor<It1> const& lhs, VecRevItor<It2> const& rhs) 
{
    return rhs.base() - lhs.base();
}

template <typename Iterator>
const_VecRevItor<Iterator>::const_VecRevItor(void)
{
}

template <typename Iterator>
const_VecRevItor<Iterator>::const_VecRevItor(Iterator iter)
: VecRevItor<Iterator>(iter)
{
}

template <typename Iterator>
const_VecRevItor<Iterator>::const_VecRevItor(const VecRevItor<Iterator>& other)
: VecRevItor<Iterator>(other)
{
}

template <typename Iterator>
template<typename T>
const_VecRevItor<Iterator>::const_VecRevItor(const VecRevItor<T>& other)
: VecRevItor<T>(other)
{
}

template <typename Iterator>
const typename const_VecRevItor<Iterator>::reference
const_VecRevItor<Iterator>::operator*(void) const
{
    return *this->_current;
}

template <typename Iterator>
const typename const_VecRevItor<Iterator>::pointer
const_VecRevItor<Iterator>::operator->(void) const
{
    return this->_current;
}


} //namespace ft
#endif 
