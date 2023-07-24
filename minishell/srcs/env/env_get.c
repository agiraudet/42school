/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:03:03 by agiraude          #+#    #+#             */
/*   Updated: 2022/08/09 15:07:08 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

t_envar	*env_get(t_list *lenvp, const char *name)
{
	t_envar	*var;

	while (lenvp)
	{
		var = (t_envar *)lenvp->content;
		if (ft_strcmp(var->name, name) == 0)
			return (var);
		lenvp = lenvp->next;
	}
	return (0);
}

char	*env_get_value(t_list *lenvp, const char *name)
{
	t_envar	*var;

	var = env_get(lenvp, name);
	if (!var)
		return (ft_strdup(""));
	return (var->value);
}

char	*env_get_str(t_envar *var)
{
	char	*str;
	int		len_name;
	int		len_value;

	len_name = ft_strlen(var->name);
	len_value = ft_strlen(var->value);
	if (!var->value || !var->name)
		return (0);
	str = (char *)calloc(len_name + len_value + 2, sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, var->name, len_name + 1);
	str[len_name] = '=';
	ft_strlcpy(&str[len_name + 1], var->value, len_value + 1);
	return (str);
}
