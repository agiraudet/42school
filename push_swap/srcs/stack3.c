/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:19:48 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/15 12:01:19 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	stack_is_sorted(t_stack *stack)
{
	while (stack->next)
	{
		if (stack->data > stack->next->data)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	stack_count(t_stack *stack)
{
	int		count;

	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

int	stack_get_pos(t_stack *stack, int data)
{
	int		pos;

	pos = 0;
	while (stack)
	{
		if (stack->data == data)
			return (pos);
		stack = stack->next;
		pos++;
	}
	return (-1);
}

int	stack_get_smallest(t_stack *stack)
{
	int		smallest;

	smallest = 2147483647;
	while (stack)
	{
		if (stack->data < smallest)
			smallest = stack->data;
		stack = stack->next;
	}
	return (smallest);
}

int	stack_get_biggest(t_stack *stack)
{
	int		biggest;

	biggest = stack->data;
	while (stack)
	{
		if (stack->data > biggest)
			biggest = stack->data;
		stack = stack->next;
	}
	return (biggest);
}
