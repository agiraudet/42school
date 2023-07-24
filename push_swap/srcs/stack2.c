/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:19:48 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/15 12:00:40 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

t_stack	*stack_last(t_stack *stack)
{
	if (!stack)
		return (0);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

t_stack	*stack_before_last(t_stack *stack)
{
	if (!stack)
		return (0);
	if (!stack->next)
		return (0);
	while (stack->next->next)
		stack = stack->next;
	return (stack);
}

void	stack_rotate(t_stack **stack)
{
	t_stack		*last;

	if (!stack || !(*stack))
		return ;
	last = stack_last(*stack);
	last->next = *stack;
	*stack = (*stack)->next;
	last->next->next = 0;
}

void	stack_rev_rotate(t_stack **stack)
{
	t_stack		*bef_last;
	t_stack		*last;

	if (!stack || !(*stack))
		return ;
	bef_last = stack_before_last(*stack);
	last = bef_last->next;
	bef_last->next = 0;
	last->next = *stack;
	*stack = last;
}

void	stack_free(t_stack **stack)
{
	t_stack		*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}
