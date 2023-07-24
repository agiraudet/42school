/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunck.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:20:02 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/15 12:26:27 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

int	chunck_choose_nb(int nb_elem)
{
	if (nb_elem < 100)
		return (5);
	else
		return (11);
}

int	*chunck_create(int *lst, int chunck_start, int chunck_end)
{
	int	chunck_len;
	int	*chunck;
	int	i;

	chunck_len = chunck_end - chunck_start;
	if (!chunck_len)
		return (0);
	chunck = (int *)malloc(sizeof(int) * chunck_len);
	if (!chunck)
		return (0);
	i = 0;
	while (chunck_start != chunck_end)
		chunck[i++] = lst[chunck_start++];
	return (chunck);
}

int	chunck_cmp_elem_pose(int closest, int pos, int stack_size)
{
	int	dist_closest;
	int	dist_pos;

	if (closest == -1)
		return (1);
	if (pos == -1)
		return (0);
	if (closest > stack_size / 2)
		dist_closest = stack_size - closest;
	else
		dist_closest = closest;
	if (pos > stack_size / 2)
		dist_pos = stack_size - pos;
	else
		dist_pos = pos;
	if (dist_pos < dist_closest)
		return (1);
	return (0);
}

int	chunck_closest_elem(t_stack *stack, int *chunck, int chunck_size)
{
	int	i;
	int	closest;
	int	pos;
	int	stack_len;

	i = 0;
	closest = -1;
	stack_len = stack_count(stack);
	while (i < chunck_size)
	{
		pos = stack_get_pos_from_data(stack, chunck[i]);
		if (chunck_cmp_elem_pose(closest, pos, stack_len))
			closest = pos;
		i++;
	}
	return (closest);
}
