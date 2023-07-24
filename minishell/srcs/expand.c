/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 11:25:13 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/11 11:38:48 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	expand_envscan_add(const char **str, t_list **env_lst)
{
	int	i;

	i = 1;
	if (ft_isdigit((*str)[i]))
		i++;
	else
	{
		while (ft_isalnum((*str)[i]) || (*str)[i] == '_')
			i++;
	}
	ft_lstadd_back(env_lst, ft_lstnew(ft_strndup(*str, i)));
	(*str)++;
}

char	**expand_envscan(const char *str)
{
	t_list	*env_lst;
	int		scan;
	int		scan_anymay;

	env_lst = 0;
	if (!str)
		return (0);
	scan = 1;
	scan_anymay = 0;
	while (*str)
	{
		if (*str == '"')
			scan_anymay ^= 1;
		if (*str == '\'' && !scan_anymay)
			scan ^= 1;
		if (scan && *str == '$' && (*(str + 1)
				&& (ft_isalnum(*(str + 1)) || *(str + 1) == '_')))
			expand_envscan_add(&str, &env_lst);
		else
			str++;
	}
	return ((char **)ft_arrflst(&env_lst, sizeof(char *)));
}

void	expand_exit_code(char **str)
{
	int		i;
	char	*code;

	i = 0;
	while ((*str)[i])
	{
		ft_skip_quotes(*str, &i);
		if (!(*str)[i])
			break ;
		if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] == '?')
		{
			code = ft_itoa(exit_code_get());
			ft_str_substitute(str, "$?", code);
			free(code);
		}
		i++;
	}
}

char	*expand_env(t_list *lenvp, const char *str)
{
	char	**var_lst;
	char	*dst;
	char	*tmp;
	int		i;

	dst = ft_strdup(str);
	expand_exit_code(&dst);
	var_lst = expand_envscan(dst);
	i = 0;
	while (var_lst && var_lst[i])
	{
		tmp = env_get_value(lenvp, &var_lst[i][1]);
		ft_str_substitute(&dst, var_lst[i], tmp);
		if (ft_strcmp(tmp, "") == 0)
			free(tmp);
		i++;
	}
	ft_arrdel((void **)var_lst, free);
	return (tilde_manage_expand(lenvp, dst));
}
