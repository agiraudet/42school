/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:30:05 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/04 18:01:46 by mbenabbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

char	*tilde_token(const char *str)
{
	char	scan;

	scan = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			if (!scan)
				scan = *str;
			else
				scan = 0;
		}
		if (*str && *str == '~' && !scan)
			return ((char *)str);
		str++;
	}
	return (0);
}

char	*tilde_homes(const char *oken)
{
	char	*tmp;

	if (ft_strcmp(oken, "root") == 0)
		return (ft_strdup("/root"));
	tmp = ft_strjoin("/home/", oken);
	if (ft_isdir(tmp))
		return (tmp);
	free(tmp);
	return (ft_strjoin("~", oken));
}

char	*tilde_env(t_list *lenvp, const char *token, const char *var_name)
{
	char	*data;

	data = env_get_value(lenvp, var_name);
	if (!data || !*data)
		return (ft_strdup(token));
	else
		return (ft_strjoin(data, &token[2]));
}

char	*tilde_value(t_list *lenvp, const char *token)
{
	if (!token[1])
		return (ft_strdup(env_get_value(lenvp, "HOME")));
	else if (token[1] == '/')
		return (ft_strjoin(env_get_value(lenvp, "HOME"), &token[1]));
	else if (token[1] == '+')
		return (tilde_env(lenvp, token, "PWD"));
	else if (token[1] == '-')
		return (tilde_env(lenvp, token, "OLDPWD"));
	else if (ft_strchr(&token[1], '/'))
		return (ft_strjoin("/home/", ft_strchr(&token[1], '/')));
	else
		return (tilde_homes(&token[1]));
}

char	*tilde_manage_expand(t_list *lenvp, char *str)
{
	char	*path;
	char	*token;

	token = tilde_token(str);
	if (!token)
		return (str);
	path = tilde_value(lenvp, token);
	ft_str_substitute(&str, token, path);
	free(path);
	return (str);
}
