/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:55:15 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/04 11:01:13 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester_bonus.h"

void	lst_print(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", lst->data);
		lst = lst->next;
	}
}

void	test_remove(t_list **lst, char *str)
{
	printf("\n### LIST REMOVE IF (== %s) ###\n", str);
	ft_list_remove_if(lst, str, &strcmp, &free);
	lst_print(*lst);
	printf("#################\n");
}

void	test_push(t_list **lst, char *str)
{
	printf("\n### PUSH \"%s\" FRONT ###\n", str);
	ft_list_push_front(lst, strdup(str));
	lst_print(*lst);
	printf("#################\n");
}

void	test_size(t_list **lst)
{
	printf("\n### LIST SIZE ###\n");
	printf(">%d\n", ft_list_size(*lst));
	printf("#################\n");
}

void	test_sort(t_list **lst)
{
	printf("\n### LIST SORT ###\n");
	ft_list_sort(lst, &strcmp);
	lst_print(*lst);
	printf("#################\n");
}
