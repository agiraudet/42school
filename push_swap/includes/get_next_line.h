/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:21:38 by agiraude          #+#    #+#             */
/*   Updated: 2021/03/22 18:15:41 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

int		get_next_line(int fd, char **line);
int		getnl(const char *str);
int		clean_join(char **cont, char *buf);
int		get_first_line(char **line, char **cont);

#endif
