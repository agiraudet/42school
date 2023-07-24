/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:40:01 by agiraude          #+#    #+#             */
/*   Updated: 2022/03/09 15:06:27 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

void	env_del(void *envar_ptr)
{
	t_envar	*var;

	if (!envar_ptr)
		return ;
	var = (t_envar *)envar_ptr;
	free(var->name);
	if (var->value)
		free(var->value);
	free(var);
}

void	env_init(t_list **lenvp, char **envp)
{
	int	shlvl;

	while (envp && *envp)
		ft_lstadd_back(lenvp, ft_lstnew(env_new(*envp++)));
	shlvl = ft_atoi(env_get_value(*lenvp, "SHLVL")) + 1;
	env_update(lenvp, "SHLVL", ft_itoa(shlvl));
	env_update(lenvp, "PWD", getcwd(0, 0));
	if (!env_get(*lenvp, "HOME"))
		env_update(lenvp, "HOME", "~");
}

int	env_cmp(void *var, void *name)
{
	if (ft_strcmp(((t_envar *)var)->name, (char *)name) == 0)
		return (1);
	return (0);
}

char	**env_arrflst(t_list *lenvp)
{
	char	**envp;
	char	*tmp;
	int		i;

	envp = (char **)calloc(ft_lstlen(lenvp) + 1, sizeof(char *));
	if (!envp)
		return (0);
	i = 0;
	while (lenvp)
	{
		tmp = env_get_str(lenvp->content);
		if (tmp)
			envp[i++] = tmp;
		lenvp = lenvp->next;
	}
	return (envp);
}
