/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:26:20 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/04 11:36:54 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "tester.h"

int		g_result = 0;
int		g_nb_test = 0;

void	print_err(char *fct, int err)
{
	perror(fct);
	printf("%s nb %d\n", fct, err);
}

int		test_read(int fd)
{
	char		buf1[BUF_LEN];
	char		buf2[BUF_LEN];
	ssize_t		res1;
	ssize_t		res2;
	int			err[2];

	bzero(buf1, BUF_LEN);
	bzero(buf2, BUF_LEN);
	printf("for fd %d\n", fd);
	errno = 0;
	res1 = ft_read(fd, buf1, BUF_LEN);
	printf("ft_read: |%s|\n", buf1);
	err[0] = errno;
	if (res1 < 0)
		print_err("ft_error ", err[0]);
	errno = 0;
	res2 = read(fd, buf2, BUF_LEN);
	printf("vs read: |%s|\n", buf2);
	err[1] = errno;
	if (res2 < 0)
		print_err("error ", err[1]);
	if ((res1 != res2) || (err[0] != err[1]))
		return (0);
	return (1);
}

int		rst(int res)
{
	if (res == 0)
		printf("\033[0;31mKO\n");
	else
		printf("\033[0;32mOK\n");
	g_nb_test++;
	g_result += res;
	printf("\033[0m\n");
	return (res);
}

int		main2(void)
{
	printf("##############\n\n");
	printf("### STRDUP ###\n");
	rst(test_strdup("A"));
	rst(test_strdup("AB"));
	rst(test_strdup("Hello"));
	rst(test_strdup("Hello world!"));
	rst(test_strdup(""));
	printf("##############\n\n");
	printf("###  WRITE ###\n");
	rst(test_write("Hello world!", 1));
	rst(test_write("Hello world!", 99));
	printf("##############\n\n");
	printf("###  READ  ###\n");
	rst(test_read(1));
	rst(test_read(99));
	printf("##############\n\n");
	printf("TOTAL : %d/%d\n", g_result, g_nb_test);
	return (0);
}

int		main(void)
{
	printf("### STRLEN ###\n");
	rst(test_strlen("A"));
	rst(test_strlen("AB"));
	rst(test_strlen("Hello"));
	rst(test_strlen("Hello world!"));
	rst(test_strlen(""));
	printf("##############\n\n");
	printf("### STRCPY ###\n");
	rst(test_strcpy("A"));
	rst(test_strcpy("AB"));
	rst(test_strcpy("Hello"));
	rst(test_strcpy("Hello world!"));
	rst(test_strcpy(""));
	printf("##############\n\n");
	printf("### STRCMP ###\n");
	rst(test_strcmp("A", "A"));
	rst(test_strcmp("AB", "AB"));
	rst(test_strcmp("A", ""));
	rst(test_strcmp("", "A"));
	rst(test_strcmp("Hello", "Hell0"));
	rst(test_strcmp("Hello", "Helo"));
	rst(test_strcmp("Hello", "Helloo"));
	rst(test_strcmp("Hello", "Hel"));
	rst(test_strcmp("Hel", "Hell0"));
	main2();
}
