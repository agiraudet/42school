/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:17:38 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/09 12:11:12 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

int	parse_check_pipe(const char *str)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (!open)
				break ;
			open = 0;
		}
		else if (str[i] != ' ' && str[i] != '\t' )
			open = 1;
		i++;
	}
	if (!open)
		return (error_msg(ft_strdup("|"), TOKEN));
	return (1);
}

int	parse_check_cmd(const char *str)
{
	t_parse	p;

	p.i = 0;
	if (!str || !*str)
		return (0);
	p.ptr = ft_strchr(str, '>');
	if (p.ptr && !check_rdr(p.ptr))
		return (error_msg(ft_strndup(p.ptr, 1), TOKEN));
	p.ptr = ft_strchr(str, '<');
	if (p.ptr && !check_rdr(p.ptr))
		return (error_msg(ft_strndup(p.ptr, 1), TOKEN));
	p.i = 0;
	p.nope = ft_split("|| && >>> <<< <> ><", ' ');
	while (p.nope[p.i])
	{
		if (ft_strstr(str, p.nope[p.i]))
		{
			p.ret = error_msg(p.nope[p.i], HANDLE);
			ft_arrdel((void **)p.nope, free);
			return (p.ret);
		}
		p.i++;
	}
	ft_arrdel((void **)p.nope, free);
	return (parse_check_pipe(str));
}

char	**parse_split(const char *line)
{
	char	*wip;
	char	**ret;
	char	dq;
	char	sq;
	int		i;

	wip = ft_strdup(line);
	dq = -1;
	sq = -1;
	i = 0;
	while (wip[i])
	{
		if (wip[i] == '"')
			dq *= -1;
		if (wip[i] == '\'')
			sq *= -1;
		if (wip[i] == '|' && sq < 0 && dq < 0)
			wip[i] = 6;
		i++;
	}
	ret = ft_split(wip, 6);
	free(wip);
	return (ret);
}

char	*parse_format(t_list *lenvp, const char *src)
{
	char	*tmp;
	char	*token;
	int		i[2];
	char	esc;

	if (!src)
		return (0);
	tmp = expand_env(lenvp, src);
	token = (char *)malloc(sizeof(char) * ft_strlen(tmp) + 1);
	i[0] = 0;
	i[1] = 0;
	esc = 0;
	while (tmp[i[0]])
	{
		if (esc == 0 && (tmp[i[0]] == '\'' || tmp[i[0]] == '"'))
				esc = tmp[i[0]];
		else if (esc != 0 && tmp[i[0]] == esc)
			esc = 0;
		else
			token[i[1]++] = tmp[i[0]];
		i[0]++;
	}
	token[i[1]] = 0;
	free(tmp);
	return (token);
}

t_cmd	**parse_line(const char *line, t_list *lenvp)
{
	char	**line_split;
	t_cmd	**cmd_lst;
	int		i;

	if (!parse_check_cmd(line))
		return (0);
	line_split = parse_split(line);
	cmd_lst = (t_cmd **)malloc(sizeof(t_cmd *)
			* (ft_arrlen((void **)line_split) + 1));
	if (!cmd_lst)
		return (0);
	i = 0;
	while (line_split[i])
	{
		args_fix_redir(&line_split[i]);
		cmd_lst[i] = cmd_new(line_split[i], lenvp);
		if (!cmd_lst[i])
			break ;
		i++;
	}
	cmd_lst[i] = NULL;
	if (line_split)
		ft_arrdel((void **)line_split, free);
	return (cmd_lst);
}
