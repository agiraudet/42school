/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:18:37 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/15 12:40:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	ft_isnumber(const char *str)
{
	if (!str)
		return (0);
	if (*str == '-')
		str++;
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int	ft_fit_in_int(const char *str)
{
	long	nb;

	nb = ft_atol(str);
	if (nb < -2147483648 || nb > 2147483647)
		return (0);
	return (1);
}

t_stack	*parse_arg(int argc, char **argv)
{
	int		i;
	t_stack	*stack;

	stack = 0;
	i = argc - 1;
	while (i > 0)
	{
		if (!ft_isnumber(argv[i]) || !ft_fit_in_int(argv[i]))
		{
			stack_free(&stack);
			return (0);
		}
		stack_add(&stack, stack_create(ft_atoi(argv[i])));
		i--;
	}
	return (stack);
}

int	exec_cmd_2(char *cmd, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strcmp(cmd, "ra") == 0)
		stack_rotate(stack_a);
	else if (ft_strcmp(cmd, "rb") == 0)
		stack_rotate(stack_b);
	else if (ft_strcmp(cmd, "rr") == 0)
	{
		stack_rotate(stack_a);
		stack_rotate(stack_b);
	}
	else if (ft_strcmp(cmd, "rra") == 0)
		stack_rev_rotate(stack_a);
	else if (ft_strcmp(cmd, "rrb") == 0)
		stack_rev_rotate(stack_b);
	else if (ft_strcmp(cmd, "rrr") == 0)
	{
		stack_rev_rotate(stack_a);
		stack_rev_rotate(stack_b);
	}
	else
		return (0);
	return (1);
}

int	exec_cmd(char *cmd, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strcmp(cmd, "sa") == 0)
		stack_swap(stack_a);
	else if (ft_strcmp(cmd, "sb") == 0)
		stack_swap(stack_b);
	else if (ft_strcmp(cmd, "ss") == 0)
	{
		stack_swap(stack_a);
		stack_swap(stack_b);
	}
	else if (ft_strcmp(cmd, "pa") == 0)
		stack_push(stack_b, stack_a);
	else if (ft_strcmp(cmd, "pb") == 0)
		stack_push(stack_a, stack_b);
	else
		return (exec_cmd_2(cmd, stack_a, stack_b));
	return (1);
}
