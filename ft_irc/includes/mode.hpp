/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:06:43 by agiraude          #+#    #+#             */
/*   Updated: 2022/10/22 16:18:32 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
# define MODE_HPP

# define PFX_Q 16
# define PFX_A 8
# define PFX_O 4
# define PFX_H 2
# define PFX_V 1

# define CHMD_o	1		//give/take chan op privileges
# define CHMD_p	2		//private chan
# define CHMD_s	4		//secret chan
# define CHMD_i	8		//invite-only chan
# define CHMD_t	16		//topic settable only by chanop
# define CHMD_n	32		//block external messages
# define CHMD_m	64		//moderated chan
# define CHMD_l	128		//user limit
# define CHMD_b	256		//ban mask
# define CHMD_v	512		//voice mode
# define CHMD_k	1024	//chan key

# define USMD_i	1
# define USMD_o	2
# define USMD_O	4
# define USMD_w	8

template<typename T>
void	modeAdd(T& dst, T& toAdd)
{
	dst |= toAdd;
}

template<typename T>
void	modeDel(T& dst, T& toDel)
{
	dst &= ~toDel;
}

#endif
