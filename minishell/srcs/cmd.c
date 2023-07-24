/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:35:07 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/07 16:03:30 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	cmd_set(t_cmd *cmd, t_list **arg_lst, t_list **rdr_lst)
{
	cmd->argv = (char **)ft_arrflst(arg_lst, sizeof(char *));
	cmd->rdrv = (t_redir **)ft_arrflst(rdr_lst, sizeof(t_redir *));
	cmd->envp = env_arrflst(cmd->lenvp);
	ft_lstclear(arg_lst, 0);
	ft_lstclear(rdr_lst, 0);
}

int	cmd_init_init(t_norm *n, t_cmd *cmd, const char *str)
{
	n->arg_lst = 0;
	n->rdr_lst = 0;
	cmd->pid = -1;
	n->args = args_split(str);
	if (!n->args)
		return (0);
	n->i = 0;
	return (1);
}

void	cmd_init(t_cmd *cmd, const char *str)
{
	t_norm	n;

	if (!cmd_init_init(&n, cmd, str))
		return ;
	while (n.args[n.i])
	{
		n.tmp = n.args[n.i];
		n.args[n.i] = expand_env(cmd->lenvp, n.args[n.i]);
		free(n.tmp);
		n.i++;
	}
	n.i = 0;
	while (n.args[n.i])
	{
		if (n.args[n.i] && (n.args[n.i][0] == '>' || n.args[n.i][0] == '<'))
			ft_lstadd_back(&n.rdr_lst, ft_lstnew(redir_new(n.args, &n.i)));
		else if (n.args[n.i])
			ft_lstadd_back(&n.arg_lst,
				ft_lstnew(parse_format(cmd->lenvp, n.args[n.i])));
		n.i++;
	}
	cmd_set(cmd, &n.arg_lst, &n.rdr_lst);
	if (n.args)
		ft_arrdel((void **)n.args, free);
}

t_cmd	*cmd_new(const char *str, t_list *lenvp)
{
	t_cmd	*cmd;

	if (!str)
		return (0);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->pid = -1;
	cmd->argv = 0;
	cmd->envp = 0;
	cmd->rdrv = 0;
	cmd->status = 0;
	cmd->lenvp = lenvp;
	cmd->pipe_in = 0;
	cmd->pipe_out = 0;
	cmd_init(cmd, str);
	cmd->pathname = path_set(cmd);
	return (cmd);
}

void	cmd_del(void *cmd_ptr)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_ptr;
	if (!cmd)
		return ;
	if (cmd->pathname)
		free(cmd->pathname);
	if (cmd->argv)
		ft_arrdel((void **)cmd->argv, free);
	if (cmd->envp)
		ft_arrdel((void **)cmd->envp, free);
	if (cmd->rdrv)
		ft_arrdel((void **)cmd->rdrv, redir_del);
	free(cmd);
}
