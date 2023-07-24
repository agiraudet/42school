/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 22:21:38 by agiraude          #+#    #+#             */
/*   Updated: 2020/11/25 01:41:14 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_line
{
	int				fnb;
	char			*cont;
	struct s_line	*next;
}					t_line;

int					get_next_line(int fd, char **line);
int					getnl(const char *str);
char				*ft_strdup(char *str);
int					clean_join(char **cont, char *buf);
int					get_first_line(char **line, char **cont);

#endif
