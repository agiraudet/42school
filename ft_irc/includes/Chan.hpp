/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chan.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:24:30 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/24 11:02:51 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAN_HPP
# define CHAN_HPP

# include <iostream>
# include <string>
# include <vector>
# include <map>
# include "User.hpp"

class	Chan
{
	public:

		Chan(void);
		Chan(std::string name);
		Chan(Chan const & src);
		~Chan(void);
		
		Chan & operator=(Chan const & rhs);

		int									join(User & user);
		void								part(int userId);
		void								setUserLimit(int userLimit);
		std::string							getName(void) const;
		void								setName(std::string name);
		short								getMode(void) const;
		std::string							getModeStr(void) const;
		void								addMode(short mode);
		void								delMode(short mode);
		void								chgMode(char sign, short mode);
		short								getUserMode(int userId) const;
		std::string							getUserLst(std::map<int, User> & servUserMap) const;
		std::string							getTopic(void) const;
		void								setTopic(std::string topic);
		char								getStatus(void) const;
		void								setStatus(char status);
		void								chgUserPfx(int userId, char sign, short pfx);
		char								getUserPfx(int userId) const;
		void								sendMsg(int fromId, std::string msg, std::map<int, User> & servUserMap) const;
		bool								userInChan(int userId) const;
		bool								keyIsCorrect(std::string const & key) const;
		bool								userIsBan(User & user) const;
		bool								userIsInv(User & user) const;
		bool								userIsHalfOp(int userId) const;
		bool								userIsOp(int userId) const;
		bool								isFull(void) const;
		void								addBanMask(std::string mask);
		void								delBanMask(std::string mask);
		std::string							getBanMask(void) const;
		std::vector<std::string> const &	getBanLst(void) const;
		void								addInv(std::string guest);
		void								setKey(std::string key);
		size_t								getNbUser(void) const;

	private:

		std::map<int, short>				_userMap;
		std::vector<std::string>			_banLst;
		std::vector<std::string>			_invLst;
		int									_userLimit;
		std::string							_key;
		std::string							_topic;
		std::string							_name;
		char								_status;
		short								_mode;

		char								_getPfx(short mode) const;

};

#endif
