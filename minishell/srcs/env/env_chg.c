/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_chg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:04:35 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/09 15:05:16 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

t_envar	*env_newsp(const char *name, const char *value)
{
	t_envar	*new;

	new = (t_envar *)malloc(sizeof(t_envar));
	if (!new)
		return (0);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	return (new);
}

t_envar	*env_new(char *src)
{
	t_envar	*new;
	int		i;

	new = (t_envar *)malloc(sizeof(t_envar));
	if (!new)
		return (0);
	if (!strchr(src, '='))
	{
		new->name = ft_strdup(src);
		new->value = 0;
	}
	else
	{
		i = 0;
		while (src[i] != '=')
			i++;
		new->name = ft_strndup(src, i);
		new->value = ft_strdup(src + i + 1);
	}
	return (new);
}

void	env_update(t_list **lenvp, char *name, char *new_value)
{
	t_envar	*var;

	var = env_get(*lenvp, name);
	if (var)
	{
		free(var->value);
		var->value = new_value;
	}
	else
		ft_lstadd_back(lenvp, ft_lstnew(env_newsp(name, new_value)));
}

int	env_updatesp(t_list **lenvp, char *str)
{
	t_envar	*new;
	t_envar	*var;

	new = env_new(str);
	if (!new)
		return (0);
	if (!ft_issain(new->name))
	{
		error_msg(new->name, EXPORT);
		env_del((void *)new);
		return (0);
	}
	var = env_get(*lenvp, new->name);
	if (var)
	{
		free(var->value);
		var->value = new->value;
		free(new->name);
		free(new);
	}
	else
		ft_lstadd_back(lenvp, ft_lstnew(new));
	return (1);
}
