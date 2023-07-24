/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:19:48 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/17 11:42:19 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	stack_d_from_pos(t_stack *stack, int pos)
{
	int		stack_pos;

	stack_pos = 0;
	while (stack && stack_pos != pos)
	{
		stack = stack->next;
		stack_pos++;
	}
	if (stack_pos == pos)
		return (stack->data);
	else
		return (-1);
}

int	stack_get_pos_from_data(t_stack *stack, int data)
{
	int		stack_pos;

	stack_pos = 0;
	while (stack)
	{
		if (stack->data == data)
			return (stack_pos);
		stack_pos++;
		stack = stack->next;
	}
	return (-1);
}

void	stack_a_small_to_top(t_stack **stack_a, t_stack **stack_b)
{
	int	smallest_pos;

	smallest_pos = stack_get_pos(*stack_a, stack_get_smallest(*stack_a));
	get_pos_on_top(stack_a, stack_b, smallest_pos);
}

int	stack_data_is_double(t_stack *stack, int data)
{
	int	nb_data;

	nb_data = 0;
	while (stack)
	{
		if (stack->data == data)
			nb_data++;
		stack = stack->next;
	}
	if (nb_data > 1)
		return (1);
	return (0);
}

int	stack_contain_doubles(t_stack *stack)
{
	t_stack		*stack_check;

	stack_check = stack;
	while (stack)
	{
		if (stack_data_is_double(stack_check, stack->data))
			return (1);
		stack = stack->next;
	}
	return (0);
}
