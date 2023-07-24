/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:31:04 by agiraude          #+#    #+#             */
/*   Updated: 2021/12/17 12:51:44 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_stack
{
	struct s_stack	*next;
	int				data;
}	t_stack;

t_stack	*stack_last(t_stack *stack);
t_stack	*stack_before_last(t_stack *stack);
void	stack_rotate(t_stack **stack);
void	stack_rev_rotate(t_stack **stack);
void	stack_free(t_stack **stack);
int		stack_is_sorted(t_stack *stack);
int		stack_count(t_stack *stack);
int		stack_get_pos(t_stack *stack, int data);
int		stack_get_smallest(t_stack *stack);
int		stack_get_biggest(t_stack *stack);
int		stack_d_from_pos(t_stack *stack, int pos);
int		stack_get_pos_from_data(t_stack *stack, int data);
int		stack_guess_pos(t_stack *stack, int data);
int		stack_data_is_double(t_stack *stack, int data);
int		stack_contain_doubles(t_stack *stack);
void	stack_a_small_to_top(t_stack **stack_a, t_stack **stack_b);	
t_stack	*stack_create(int data);
void	stack_add(t_stack **stack, t_stack *new);
void	stack_swap(t_stack **stack);
t_stack	*stack_pop(t_stack **stack);
void	stack_push(t_stack **src, t_stack **dst);
int		ft_isnumber(const char *str);
int		ft_fit_in_int(const char *str);
t_stack	*parse_arg(int argc, char **argv);
int		exec_cmd(char *cmd, t_stack **stack_a, t_stack **stack_b);
int		ft_abs(int nb);
void	ft_sort_int_tab(int *tab, int size);
int		check_errors(int argc, char **argv, t_stack **stack_a);
void	output_cmd(char *cmd, t_stack **stack_a, t_stack **stack_b);
int		sort_2(t_stack **stack_a, t_stack **stack_b);
int		sort_3(t_stack **stack_a, t_stack **stack_b);
int		sort_5(t_stack **stack_a, t_stack **stack_b);
int		chunck_choose_nb(int nb_elem);
int		*chunck_create(int *lst, int chunck_start, int chunck_end);
int		chunck_closest_elem(t_stack *stack, int *chunck, int chunck_size);
void	chunck_sort(t_stack **stack_a, t_stack **stack_b);
void	get_pos_on_top(t_stack	**stack_a, t_stack **stack_b, int pos);
void	get_biggest_on_top(t_stack **stack_a, t_stack **stack_b);
void	insert_data(t_stack **stack_a, t_stack **stack_b, int data);
void	put_b_to_a(t_stack **stack_a, t_stack **stack_b);
int		create_list(t_stack *stack, int **lst);
#endif
