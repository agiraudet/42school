/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunck_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:20:02 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/15 12:28:31 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	chunck_sort_one(t_stack **stack_a, t_stack **stack_b,
		int *chunck, int chunck_size)
{
	int	i;
	int	next_pos;

	i = 0;
	while (i < chunck_size && stack_count(*stack_a))
	{
		next_pos = chunck_closest_elem(*stack_a, chunck, chunck_size);
		if (stack_count(*stack_a) > 1)
			get_pos_on_top(stack_a, stack_b, next_pos);
		output_cmd("pb", stack_a, stack_b);
		i++;
	}
}

void	chunck_sort_all(t_stack **stack_a, t_stack **stack_b,
		int *lst, int nb_elem)
{
	int	chunck_size;
	int	nb_chunck;
	int	*chunk_to_sort;
	int	i;

	nb_chunck = chunck_choose_nb(nb_elem);
	chunck_size = nb_elem / nb_chunck;
	if (nb_chunck * chunck_size < nb_elem)
		nb_chunck++;
	i = 0;
	while (i < nb_chunck)
	{
		if (i == nb_chunck - 1)
		{
			chunk_to_sort = chunck_create(lst, i * chunck_size, nb_elem);
			chunck_size = nb_elem - i * chunck_size;
		}
		else
			chunk_to_sort = chunck_create(lst, i * chunck_size,
					i * chunck_size + chunck_size);
		chunck_sort_one(stack_a, stack_b, chunk_to_sort, chunck_size);
		free(chunk_to_sort);
		i++;
	}
}

void	chunck_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	nb_elem;
	int	*lst;

	lst = 0;
	nb_elem = create_list(*stack_a, &lst);
	chunck_sort_all(stack_a, stack_b, lst, nb_elem);
	put_b_to_a(stack_a, stack_b);
	free(lst);
}
