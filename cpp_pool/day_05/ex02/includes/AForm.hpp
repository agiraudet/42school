/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:47:25 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/01 20:32:22 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AForm_HPP
# define AForm_HPP

# include <iostream>
# include <string>

class	Bureaucrat;

class	AForm
{
	public:

		AForm(void);
		AForm(std::string name, unsigned int gToSign, unsigned int gToExecute);
		AForm(AForm const & src);
		~AForm(void);
		AForm & operator=(AForm const & rhs);

		virtual void	act(void) const = 0;

		std::string		getName(void) const;
		unsigned int	getGradeToSign(void) const;
		unsigned int	getGradeToExecute(void) const;
		bool			getSigned(void) const;
		void			beSigned(Bureaucrat const & guy);
		void			execute(Bureaucrat const & executor) const;

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

		class	NotSignedException : public std::exception
		{
			public :
				virtual const char * what() const throw()
				{
					return ("Form not signed");
				}
		};

	private:
		
		std::string const	_name;
		bool				_signed;
		unsigned int const	_gradeToSign;
		unsigned int const	_gradeToExecute;

		void	_checkGrade(unsigned int grade) const;
};

std::ostream &	operator<<(std::ostream & o, AForm const & rhs);

#endif
