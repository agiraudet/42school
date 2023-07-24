/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:18:08 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/17 13:50:59 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "push_swap.h"

int	result(t_stack *stack_a, t_stack *stack_b)
{
	if (!stack_is_sorted(stack_a) || stack_b != 0)
	{
		ft_putendl("KO");
		return (0);
	}
	ft_putendl("OK");
	return (1);
}

int	clean_exit(t_stack **stack_a, t_stack **stack_b, char **cmd)
{
	if (*cmd)
		free(*cmd);
	if (stack_a)
		stack_free(stack_a);
	if (stack_b)
		stack_free(stack_b);
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	char		*cmd;
	int			res;

	if (argc <= 1)
		return (0);
	stack_a = 0;
	stack_b = 0;
	cmd = 0;
	if (!check_errors(argc, argv, &stack_a))
		return (0);
	while (get_next_line(0, &cmd) > 0)
	{
		if (!exec_cmd(cmd, &stack_a, &stack_b))
		{
			ft_putendl_fd("Error", 2);
			return (clean_exit(&stack_a, &stack_b, &cmd));
		}
		free(cmd);
		cmd = 0;
	}
	res = result(stack_a, stack_b);
	clean_exit(&stack_a, &stack_b, &cmd);
	return (res);
}
