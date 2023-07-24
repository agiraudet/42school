/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:08:39 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/24 16:21:29 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CmdHandler.hpp"
#include "Server.hpp"

void	CmdHandler::_onPONG(User & user, std::vector<std::string> & param)
{
	if (param.size() > 1 && param[1].compare(user.getNick()) == 0)
		user.setAwaitingPong(false);
}
