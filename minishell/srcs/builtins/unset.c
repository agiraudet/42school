/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:05:41 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/09 16:08:09 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	ft_unset(t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->argv[i])
		ft_lstdelone(ft_lstpop_srch(&cmd->lenvp,
				env_cmp, cmd->argv[i++]), env_del);
	return (0);
}
