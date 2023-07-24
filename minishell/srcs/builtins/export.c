/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:05:27 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/10 17:56:24 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	ft_export_new(char ***exported, t_cmd *cmd)
{
	int	status;
	int	i;

	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		if (!env_updatesp(&cmd->lenvp, cmd->argv[i]))
			status = 1;
		ft_arradd((void ***)exported, ft_strdup(cmd->argv[i]), sizeof(char *));
		i++;
	}
	ft_arrsort((void **)*exported, (void *)ft_strcmp);
	return (status);
}

char	*ft_export_get_name(const char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (0);
	while (var[i] && var[i] != '=')
		i++;
	return (ft_strndup(var, i));
}

int	ft_export(t_cmd *cmd)
{
	static char		**exported = 0;
	char			*tmp;
	int				i;

	if (!cmd && exported)
	{
		ft_arrdel((void **)exported, free);
		exported = 0;
	}
	else if (cmd && cmd->argv[1])
		return (ft_export_new(&exported, cmd));
	else
	{
		i = 0;
		while (exported && exported[i])
		{
			tmp = ft_export_get_name(exported[i]);
			if (env_get(cmd->lenvp, tmp))
				printf("declare -x %s\n", exported[i]);
			if (tmp)
				free(tmp);
			i++;
		}
	}
	return (0);
}
