/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:28:48 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/07 13:13:33 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h"

# define LEFT 1
# define RIGHT 0

typedef struct	s_elem
{
	char		type;
	char		*data;
	int			zero_flag;
	int			error_flag;
	int			align;
	char		pad;
	int			width;
	int			size;
	int			prec;
	wchar_t		wchar;
}				t_elem;

int				ft_printf(const char *str, ...);
int				elem_print(const char **str, va_list *param);
char			*ft_fill_buffer(t_elem *e);
char			*ft_prec(t_elem *e);
char			*arg_to_str(char *arg);
char			*arg_to_ptr(unsigned long long ptr);
char			*arg_to_chr(t_elem *e, wchar_t x);
char			*fix_hex(char *src);
void			fix_minus(char *src);
void			ft_set_flag(const char **str, t_elem *e, va_list *param);
void			ft_set_prec(const char **str, t_elem *e, va_list *param);
int				ft_set_data(t_elem *e, va_list *param);
int				ft_set_padlen(t_elem *e, int datalen);

#endif
