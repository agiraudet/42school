/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:19:48 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/15 12:00:05 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

t_stack	*stack_create(int data)
{
	t_stack		*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (0);
	new->data = data;
	new->next = 0;
	return (new);
}

void	stack_add(t_stack **stack, t_stack *new)
{
	new->next = *stack;
	*stack = new;
}

void	stack_swap(t_stack **stack)
{
	t_stack		*tmp;

	if (!*stack || !(*stack)->next)
		return ;
	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = tmp->next->next;
	(*stack)->next = tmp;
}

t_stack	*stack_pop(t_stack **stack)
{
	t_stack		*pop;

	pop = *stack;
	*stack = (*stack)->next;
	return (pop);
}

void	stack_push(t_stack **src, t_stack **dst)
{
	if (!src)
		return ;
	stack_add(dst, stack_pop(src));
}
