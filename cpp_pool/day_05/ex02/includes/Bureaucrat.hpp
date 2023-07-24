/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:17:45 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 20:05:02 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include "AForm.hpp"

class	Bureaucrat
{
	public:

		Bureaucrat(void);
		Bureaucrat(std::string name, unsigned int grade);
		Bureaucrat(Bureaucrat const & src);
		~Bureaucrat(void);
		
		Bureaucrat & operator=(Bureaucrat const & rhs);

		std::string		getName(void) const;
		unsigned int	getGrade(void) const;
		void			incGrade(void);
		void			decGrade(void);
		void			signForm(AForm & AForm) const;
		void			executeForm(AForm const & form) const;

		class	GradeTooHighException : public std::exception
		{
			public :
				virtual const char * what() const throw()
				{
					return ("Grade too high");
				}
		};

		class	GradeTooLowException : public std::exception
		{
			public :
				virtual const char * what() const throw()
				{
					return ("Grade too low");
				}
		};

	private:
		
		std::string const	_name;
		unsigned int		_grade;

};

std::ostream &	operator<<(std::ostream & o, Bureaucrat const & rhs);

#endif
