/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:26:44 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/24 22:52:24 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <iostream>
# include <fstream>
# include <string>

enum	logLvl {
	DEBUG,
	INFO,
	WARN,
	ERROR,
	NONE
};

class	Logger
{
	public:

		Logger(void);
		Logger(std::string logFile);
		Logger(Logger const & src);
		~Logger(void);
		
		Logger &		operator=(Logger const & rhs);
		
		Logger &		log(logLvl lvl);
		Logger &		nl(void);
		logLvl const &	getLabel(void) const;
		logLvl const &	getLvlStd(void) const;
		logLvl const &	getLvlFile(void) const;
		void			setLvl(logLvl lvl);
		void			setLvlStd(logLvl lvl);
		void			setLvlFile(logLvl lvl);
		void			setLogToStd(bool mode);
		void			setLogToFile(bool mode);
		std::ofstream &	getLogFile(void);
		bool			logToStd(void) const;
		bool			logToFile(void) const;

	private:

		std::string		_logFileName;
		std::ofstream	_logFile;
		bool			_logToFile;
		bool			_logToStd;
		logLvl			_label;
		logLvl			_levelStd;
		logLvl			_levelFile;
};

template <typename T>
Logger &	operator<<(Logger & lhs, T const & msg)
{
	if (lhs.getLabel() >= lhs.getLvlStd() && lhs.logToStd())
		std::cout << msg;
	if (lhs.getLabel() >= lhs.getLvlFile() && lhs.logToFile())
		lhs.getLogFile() << msg;
	return lhs;
}

extern Logger logger;

#endif
