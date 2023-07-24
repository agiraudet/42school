/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 23:23:40 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/10 15:04:05 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	args_fix_redir(char **str)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*str)[i])
	{
		ft_skip_quotes(*str, &i);
		if (!(*str)[i])
			break ;
		if (i > 0 && (*str)[i - 1] != (*str)[i]
			&& ((*str)[i] == '>' || (*str)[i] == '<') && (*str)[i - 1] != ' ')
		{
			tmp = ft_strinsert((*str), i, " ");
			free((*str));
			(*str) = tmp;
			i = 0;
		}
		i++;
	}
}

void	args_skip_spaces(const char **str)
{
	while (**str && **str == ' ')
		(*str)++;
}

void	args_scan(const char *str, t_list **arg_lst)
{
	int		i;
	char	esc;
	char	scan;

	args_skip_spaces(&str);
	esc = ' ';
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != esc)
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				scan = str[i];
				i++;
				while (str[i] && str[i] != scan)
					i++;
			}
			if (str[i])
				i++;
		}
		ft_lstadd_back(arg_lst, ft_lstnew(ft_strndup(str, i)));
		str += i;
		args_skip_spaces(&str);
	}
}

char	**args_split(const char *str)
{
	t_list	*arg_lst;
	char	**argv;

	arg_lst = 0;
	args_scan(str, &arg_lst);
	argv = (char **)ft_arrflst(&arg_lst, sizeof(char *));
	ft_lstclear(&arg_lst, 0);
	return (argv);
}
