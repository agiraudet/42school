/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:24:50 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/04 11:40:57 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUF_LEN 100

void	print_err(char *fct, int err);
int		test_strlen(char *str);
int		test_strcpy(char *str);
int		test_strcmp(char *s1, char *s2);
int		test_strdup(char *str);
int		test_write(char *str, int fd);

#endif
