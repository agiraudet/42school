/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:50:00 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/17 12:21:59 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	get_pos_on_top(t_stack	**stack_a, t_stack **stack_b, int pos)
{
	int		stack_len;

	if (pos == 0)
		return ;
	stack_len = stack_count(*stack_a);
	if (pos > stack_len / 2)
	{
		while (pos++)
		{
			output_cmd("rra", stack_a, stack_b);
			if (pos >= stack_len)
				pos = 0;
		}
	}
	else
	{
		while (pos--)
			output_cmd("ra", stack_a, stack_b);
	}
}

void	get_biggest_on_top(t_stack **stack_a, t_stack **stack_b)
{
	int	biggest;
	int	stack_len;

	biggest = stack_get_pos(*stack_b, stack_get_biggest(*stack_b));
	if (biggest == 0)
		return ;
	stack_len = stack_count(*stack_b);
	if (biggest > stack_len / 2)
	{
		while (biggest++)
		{
			output_cmd("rrb", stack_a, stack_b);
			if (biggest >= stack_len)
				biggest = 0;
		}
	}
	else
	{
		while (biggest--)
			output_cmd("rb", stack_a, stack_b);
	}
}

int	find_pos(t_stack *stack, int data)
{
	t_stack	*prev;
	t_stack	*next;
	int		pos;

	pos = 0;
	next = stack;
	prev = stack_last(stack);
	while (next)
	{
		if (data < next->data && data > prev->data)
			return (pos);
		prev = next;
		next = next->next;
		pos++;
	}
	return (pos);
}

void	put_b_to_a(t_stack **stack_a, t_stack **stack_b)
{
	int	stack_size;

	stack_size = stack_count(*stack_b);
	while (stack_size > 1)
	{
		get_biggest_on_top(stack_a, stack_b);
		output_cmd("pa", stack_a, stack_b);
		stack_size--;
	}
	output_cmd("pa", stack_a, stack_b);
}

int	create_list(t_stack *stack, int **lst)
{
	int	i;
	int	nb_elem;

	nb_elem = stack_count(stack);
	if (nb_elem <= 0)
		return (0);
	*lst = (int *)malloc(sizeof(int) * nb_elem);
	if (!*lst)
		return (0);
	i = 0;
	while (stack)
	{
		(*lst)[i++] = stack->data;
		stack = stack->next;
	}
	ft_sort_int_tab(*lst, nb_elem);
	return (nb_elem);
}
