/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:30:29 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/04 11:38:57 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "tester.h"

int	test_strlen(char *str)
{
	int		res1;
	int		res2;

	printf("for \"%s\"\n", str);
	res1 = ft_strlen(str);
	res2 = strlen(str);
	printf("ft_strlen: %d\n", res1);
	printf("vs strlen: %d\n", res2);
	return (res1 == res2);
}

int	test_strcpy(char *str)
{
	char	cpy1[100];
	char	cpy2[100];
	int		res;

	printf("for \"%s\"\n", str);
	ft_strcpy(cpy1, str);
	strcpy(cpy2, str);
	printf("ft_strcpy: |%s|\n", cpy1);
	printf("vs strcpy: |%s|\n", cpy2);
	res = strcmp(cpy1, cpy2) == 0 ? 1 : 0;
	return (res);
}

int	test_strcmp(char *s1, char *s2)
{
	int		res1;
	int		res2;

	printf("for \"%s\" vs \"%s\"\n", s1, s2);
	res1 = ft_strcmp(s1, s2);
	res2 = strcmp(s1, s2);
	printf("ft_strcmp: |%d|\n", res1);
	printf("vs strcmp: |%d|\n", res2);
	return (res1 == res2);
}

int	test_strdup(char *str)
{
	char	*dup1;
	char	*dup2;
	int		res;

	printf("for \"%s\"\n", str);
	dup1 = ft_strdup(str);
	dup2 = strdup(str);
	printf("ft_strdup: |%s|\n", dup1);
	printf("vs strdup: |%s|\n", dup2);
	res = strcmp(dup1, dup2) == 0 ? 1 : 0;
	return (res);
}

int	test_write(char *str, int fd)
{
	ssize_t		res1;
	ssize_t		res2;
	int			err1;
	int			err2;

	printf("for \"%s\" in fd %d\n", str, fd);
	errno = 0;
	res1 = ft_write(fd, str, strlen(str));
	printf("\nft_write: %zd\n", res1);
	err1 = errno;
	if (res1 < 0)
		print_err("ft_error ", err1);
	errno = 0;
	res2 = write(fd, str, strlen(str));
	printf("\nvs write: %zd\n", res2);
	err2 = errno;
	if (res2 < 0)
		print_err("error ", err2);
	if ((res1 != res2) || (err1 != err2))
		return (0);
	return (1);
}
