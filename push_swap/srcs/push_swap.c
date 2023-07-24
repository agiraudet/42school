/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 20:17:44 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/17 12:19:07 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

#include <stdio.h>

int	print_one(t_stack *stack)
{
	while (stack)
	{
		printf("%d\n", stack->data);
		stack = stack->next;
	}
	return (0);
}

int	print_stack(t_stack **stack_a, t_stack **stack_b)
{
	printf("STACK A:\n");
	print_one(*stack_a);
	printf("STACK B:\n");
	print_one(*stack_b);
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	int			stack_size;

	stack_a = 0;
	stack_b = 0;
	if (!check_errors(argc, argv, &stack_a))
		return (0);
	stack_size = stack_count(stack_a);
	if (stack_size == 2)
		sort_2(&stack_a, &stack_b);
	else if (stack_size == 3)
		sort_3(&stack_a, &stack_b);
	else if (stack_size == 5)
		sort_5(&stack_a, &stack_b);
	else
		chunck_sort(&stack_a, &stack_b);
	stack_free(&stack_a);
	if (stack_b)
		stack_free(&stack_b);
}
