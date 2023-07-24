/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:16:36 by user42            #+#    #+#             */
/*   Updated: 2021/02/04 11:09:40 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "libasm_bonus.h"
#include "tester_bonus.h"

int		test_atoi_base(char *str, char *base)
{
	int		res1;
	int		res2;

	res1 = ft_atoi_base(str, base);
	res2 = atoi_base(str, base);
	printf("string: |%s|\nbase  : |%s|\n", str, base);
	printf("ft_atoi_base: %d\n", res1);
	printf("vs atoi_base: %d\n", res2);
	return (res1 == res2);
}

int		rst(int res)
{
	if (res == 0)
		printf("\033[0;31mKO\n");
	else
		printf("\033[0;32mOK\n");
	printf("\033[0m\n");
	return (res);
}

void	test_list(void)
{
	t_list	*lst;

	printf("### INIT LIST ###\n");
	lst = ft_create_elem(strdup("E"));
	lst_print(lst);
	printf("#################\n");
	test_push(&lst, "C");
	test_push(&lst, "A");
	test_push(&lst, "B");
	test_size(&lst);
	test_push(&lst, "D");
	test_sort(&lst);
	test_size(&lst);
	test_sort(&lst);
	test_remove(&lst, "E");
	test_remove(&lst, "Z");
	test_remove(&lst, "C");
	test_remove(&lst, "A");
	test_push(&lst, "Z");
	test_sort(&lst);
}

int		main(void)
{
	printf("### ATOI_BASE ###\n");
	rst(test_atoi_base("10A1", "0123456789ABCDEF"));
	rst(test_atoi_base("\t10A1", "0123456789ABCDEF"));
	rst(test_atoi_base("   ---10A1", "0123456789ABCDEF"));
	rst(test_atoi_base("-+-10A1", "0123456789ABCDEF"));
	rst(test_atoi_base("101010", "01"));
	rst(test_atoi_base("7524", "0123456789"));
	rst(test_atoi_base("7524", "01234056789"));
	rst(test_atoi_base("7524", "01234i+56789"));
	rst(test_atoi_base("7524", "012345-6789"));
	rst(test_atoi_base("7524", "012345 6789"));
	printf("### LIST ###\n");
	test_list();
	return (0);
}
