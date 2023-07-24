/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:13:10 by agiraude          #+#    #+#             */
/*   Updated: 2023/01/31 10:19:26 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "internals/iterator.hpp"

namespace ft
{

template <typename T>
struct is_integral {
  static const bool value = false;
};

template <>
struct is_integral<bool> {
  static const bool value = true;
};

template <>
struct is_integral<char> {
  static const bool value = true;
};

template <>
struct is_integral<signed char> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned char> {
  static const bool value = true;
};

template <>
struct is_integral<short> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned short> {
  static const bool value = true;
};

template <>
struct is_integral<int> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned int> {
  static const bool value = true;
};

template <>
struct is_integral<long> {
  static const bool value = true;
};

template <>
struct is_integral<unsigned long> {
  static const bool value = true;
};

template <typename T>
struct is_floating_point
{
  static const bool value = false;
};

template <>
struct is_floating_point<float>
{
  static const bool value = true;
};

template <>
struct is_floating_point<double>
{
  static const bool value = true;
};

template <typename T>
struct is_void
{
  static const bool value = false;
};

template <>
struct is_void<void>
{
  static const bool value = true;
};

template <typename T>
struct is_arithmetic
{
  static const bool value =
    is_integral<T>::value || is_floating_point<T>::value;
};

template <typename T>
struct is_fundamental
{
  static const bool value =
    is_arithmetic<T>::value || is_void<T>::value;
};

//////////////////////////////////////

template <bool B, typename T = void>
struct enable_if
{
};

template <typename T>
struct enable_if<true, T>
{
    typedef T type;
};

template <typename T, typename U>
struct is_same
{
    static const bool value = false;
};

template <typename T>
struct is_same<T, T>
{
    static const bool value = true;
};

//////////////////////////////////////

template <typename T>
struct is_pointer {
  static const bool value = false;
};

template <typename T>
struct is_pointer<T*> {
  static const bool value = true;
};


template <typename T>
struct is_iterator
{
  template <typename U>
  static char test(typename U::iterator_category*);

  template <typename U>
  static int test(...);

  static const bool value = sizeof(test<T>(0)) == sizeof(char) || is_pointer<T>::value;
};

//////////////////////////////////////

template<typename T>
void  swap(T& a, T& b)
{
  T tmp;

  tmp = a;
  a = b;
  b = tmp;
}

template<typename InputIt1, typename InputIt2>
bool  lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (*first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template<typename InputIt1, typename InputIt2, typename Compare>
bool  lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
    {
        if (comp(*first1, *first2))
            return true;
        if (comp(*first2, *first1))
            return false;
    }
    return (first1 == last1) && (first2 != last2);
}

}
#endif
