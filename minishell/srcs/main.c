/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenabbo <mbenabbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:18:50 by agiraude          #+#    #+#             */
/*   Updated: 2022/09/11 11:41:11 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"
#include <readline/history.h>
#include <readline/readline.h>

void	exit_clean(t_list *lenvp)
{
	ft_export(0);
	ft_lstclear(&lenvp, env_del);
	clear_history();
}

void	init(int argc, char **argv, char **envp, t_list **lenvp)
{
	error_name(argv[0]);
	if (argc > 1)
	{
		error_msg("no arguments allowed", BASIC);
		exit(1);
	}
	*lenvp = 0;
	env_init(lenvp, envp);
	env_update(lenvp, "0", argv[0]);
}

int	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	exit_code_set(0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	t_list	*lenvp;

	cmd_line = 0;
	init(argc, argv, envp, &lenvp);
	while (1)
	{
		if (cmd_line)
			free(cmd_line);
		if (cmd_line)
			cmd_line = 0;
		signals_set();
		cmd_line = readline("mush> ");
		if (!cmd_line && printf("exit\n"))
			break ;
		if (*cmd_line)
			add_history(cmd_line);
		if (skip_space(cmd_line) == 0)
			if (exec_cmdlst(parse_line(cmd_line, lenvp)) == 0)
				break ;
	}
	if (cmd_line)
		free(cmd_line);
	exit_clean(lenvp);
	return (exit_code_get());
}
