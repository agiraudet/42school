/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 17:58:57 by mbenabbo          #+#    #+#             */
/*   Updated: 2022/09/10 15:30:29 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

t_redir	*redir_new(char **args, int *i)
{
	t_redir	*rdr;
	int		ii;

	rdr = (t_redir *)malloc(sizeof(t_redir));
	if (!rdr)
		return (0);
	rdr->fd = -1;
	rdr->word = 0;
	if (args[*i][0] == '>')
		rdr->dir = OUT;
	else
		rdr->dir = IN;
	if (args[*i][0] == args[*i][1])
		rdr->type = DOUBLE;
	else
		rdr->type = SIMPLE;
	ii = 0;
	while (args[*i][ii] && args[*i][ii] == args[*i][0])
		ii++;
	if (args[*i][ii])
		rdr->word = ft_strdup(&args[*i][ii]);
	else
		rdr->word = ft_strdup(args[++(*i)]);
	return (rdr);
}

void	redir_del(void *redir_ptr)
{
	t_redir	*rdr;

	rdr = (t_redir *)redir_ptr;
	if (rdr->word)
		free(rdr->word);
	free(rdr);
}
