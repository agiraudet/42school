/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:02:06 by agiraude          #+#    #+#             */
/*   Updated: 2021/01/07 17:08:40 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_elem	elem_init(void)
{
	t_elem	e;

	e.zero_flag = 0;
	e.error_flag = 0;
	e.align = RIGHT;
	e.pad = ' ';
	e.width = 0;
	e.prec = 0;
	e.size = 0;
	return (e);
}

t_elem	*elem_create(const char **str, va_list *param)
{
	t_elem	*e;

	e = (t_elem*)malloc(sizeof(t_elem));
	if (!e)
		return (0);
	*e = elem_init();
	ft_set_flag(str, e, param);
	ft_set_prec(str, e, param);
	if (!ft_strchr("cspdiuxX%", **str))
	{
		free(e);
		return (0);
	}
	e->type = **str;
	(*str)++;
	if (!ft_set_data(e, param))
	{
		free(e);
		return (0);
	}
	return (e);
}

void	put_buffer(t_elem *e, char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (e->zero_flag && buffer[i] == '.')
			write(1, &e->wchar, 1);
		else
			ft_putchar(buffer[i]);
		i++;
	}
}

void	elem_destroy(t_elem *e)
{
	free(e->data);
	free(e);
}

int		elem_print(const char **str, va_list *param)
{
	int		ret;
	char	*buffer;
	t_elem	*e;

	if (!(e = elem_create(str, param)))
		return (-1);
	if (!(buffer = ft_fill_buffer(e)))
	{
		elem_destroy(e);
		return (-1);
	}
	ret = ft_strlen(buffer);
	if (e->error_flag == 1)
	{
		free(buffer);
		buffer = ft_strdup("");
		ret = 255;
	}
	put_buffer(e, buffer);
	free(buffer);
	elem_destroy(e);
	return (ret);
}
