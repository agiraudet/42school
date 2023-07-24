/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:11:04 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/28 10:16:14 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <list>

class	Span
{
	public:

		Span(void);
		Span(unsigned int N);
		Span(Span const & src);
		~Span(void);
		
		Span & operator=(Span const & rhs);

		void	addNumber(int n);
		int		shortestSpan(void);
		int		longestSpan(void);
		void	addNumberRange(int from, int to, int step);
		void	addNumberRand(int n);
		void	printLst(void) const;

		class	NoRoomException : public std::exception
		{
			public :
				virtual const char * what() const throw()
				{
					return ("Already too many elems in list");
				}
		};

		class	NoElemException : public std::exception
		{
			public :
				virtual const char * what() const throw()
				{
					return ("Not enough elems in list");
				}
		};

	private:

		std::list<int>	_lst;
		unsigned int	_N;
};
#endif
