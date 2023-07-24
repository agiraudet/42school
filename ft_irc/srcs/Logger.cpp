/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:26:26 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/24 22:45:52 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"

Logger::Logger(void)
: _logFileName(""), _logToFile(false), _logToStd(true), _label(ERROR), _levelStd(ERROR), _levelFile(ERROR)
{
}

Logger::Logger(std::string logFileName)
: _logFileName(logFileName), _logToFile(false), _logToStd(true), _label(ERROR), _levelStd(ERROR), _levelFile(ERROR)
{
	this->_logFile.open(logFileName.c_str());
	if (this->_logFile.is_open())
		this->_logToFile = true;
}

Logger::Logger(Logger const & src)
{
	if (this != &src)
		*this = src;
}

Logger::~Logger(void)
{
	if (this->_logFile.is_open())
		this->_logFile.close();
}

Logger & Logger::operator=(Logger const & rhs)
{
	this->_logFileName = rhs._logFileName;
	this->_logToFile = rhs._logToFile;
	this->_logToStd = rhs._logToStd;
	this->_label = rhs._label;
	this->_levelStd = rhs._levelStd;
	this->_levelFile = rhs._levelFile;
	if (this->_logFileName.size() > 0 && rhs._logFile.is_open())
		this->_logFile.open(this->_logFileName.c_str());
	return *this;
}

Logger &	Logger::log(logLvl lvl)
{
	this->_label = lvl;
	return *this;
}

logLvl const &	Logger::getLabel(void) const
{
	return this->_label;
}

logLvl const &	Logger::getLvlStd(void) const
{
	return this->_levelStd;
}

logLvl const &	Logger::getLvlFile(void) const
{
	return this->_levelFile;
}

void	Logger::setLvl(logLvl lvl)
{
	this->setLvlStd(lvl);
	this->setLvlFile(lvl);
}

void	Logger::setLvlStd(logLvl lvl)
{
	this->_levelStd = lvl;
}

void	Logger::setLvlFile(logLvl lvl)
{
	this->_levelFile = lvl;
}

void	Logger::setLogToStd(bool mode)
{
	this->_logToStd = mode;
}

void	Logger::setLogToFile(bool mode)
{
	this->_logToFile = mode;
}

bool	Logger::logToStd(void) const
{
	return this->_logToStd;
}

bool	Logger::logToFile(void) const
{
	return (this->_logToFile && this->_logFile.is_open());
}

std::ofstream &	Logger::getLogFile(void)
{
	return this->_logFile;
}

Logger &	Logger::nl(void)
{
	if (this->_label >= this->_levelStd && this->logToStd())
		std::cout << std::endl;
	if (this->_label >= this->_levelFile && this->logToFile())
		this->_logFile << std::endl;
	return *this;
}
