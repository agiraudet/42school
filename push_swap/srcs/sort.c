/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:51:05 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/17 11:42:01 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	sort_2(t_stack **stack_a, t_stack **stack_b)
{
	if (stack_get_pos(*stack_a, stack_get_smallest(*stack_a)) != 0)
		output_cmd("sa", stack_a, stack_b);
	return (0);
}

int	sort_3(t_stack **stack_a, t_stack **stack_b)
{
	int		small_pos;

	if (stack_is_sorted(*stack_a))
		return (0);
	small_pos = stack_get_pos(*stack_a, stack_get_smallest(*stack_a));
	if (small_pos == 0)
	{
		output_cmd("sa", stack_a, stack_b);
		output_cmd("ra", stack_a, stack_b);
	}
	else if (small_pos == 1)
	{
		if (stack_d_from_pos(*stack_a, 0) > stack_d_from_pos(*stack_a, 2))
			output_cmd("ra", stack_a, stack_b);
		else
			output_cmd("sa", stack_a, stack_b);
	}
	else
	{
		if (stack_d_from_pos(*stack_a, 0) > stack_d_from_pos(*stack_a, 1))
			output_cmd("sa", stack_a, stack_b);
		output_cmd("rra", stack_a, stack_b);
	}
	return (0);
}

int	sort_5(t_stack **stack_a, t_stack **stack_b)
{
	stack_a_small_to_top(stack_a, stack_b);
	output_cmd("pb", stack_a, stack_b);
	stack_a_small_to_top(stack_a, stack_b);
	output_cmd("pb", stack_a, stack_b);
	sort_3(stack_a, stack_b);
	output_cmd("pa", stack_a, stack_b);
	output_cmd("pa", stack_a, stack_b);
	return (0);
}
