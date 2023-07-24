/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:16:50 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/17 12:18:39 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	output_cmd(char *cmd, t_stack **stack_a, t_stack **stack_b)
{
	ft_putendl(cmd);
	exec_cmd(cmd, stack_a, stack_b);
}

t_stack	*parse_arg_solo(char **argv)
{
	char	**lst;
	t_stack	*stack;
	int		i;

	lst = ft_split(argv[1], ' ');
	i = 0;
	stack = 0;
	while (lst[i])
		i++;
	i--;
	while (i >= 0)
	{
		if (!ft_isnumber(lst[i]) || !ft_fit_in_int(lst[i]))
		{
			stack_free(&stack);
			break ;
		}
		stack_add(&stack, stack_create(ft_atoi(lst[i--])));
	}
	i = 0;
	while (lst[i])
		free(lst[i++]);
	free(lst);
	return (stack);
}		

int	check_errors(int argc, char **argv, t_stack **stack_a)
{
	if (argc <= 1)
		return (0);
	if (argc == 2)
		*stack_a = parse_arg_solo(argv);
	else
		*stack_a = parse_arg(argc, argv);
	if (!*stack_a)
	{
		ft_putendl_fd("Error", 2);
		return (0);
	}
	if (stack_contain_doubles(*stack_a))
	{
		stack_free(stack_a);
		ft_putendl_fd("Error", 2);
		return (0);
	}
	if (stack_is_sorted(*stack_a))
	{
		stack_free(stack_a);
		return (0);
	}
	return (1);
}
