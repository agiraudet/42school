/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_align.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:10:36 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/19 14:28:51 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_put_align(t_elem *e, char *prec, int datalen, int padlen)
{
	char	*ret;
	int		i;
	int		j;

	ret = (char*)malloc(sizeof(char) * (datalen + padlen + 1));
	if (!ret)
		return (0);
	i = 0;
	if (e->align == RIGHT)
		while (i < padlen)
			ret[i++] = e->pad;
	j = 0;
	while (j < datalen)
		ret[i++] = prec[j++];
	while (i < padlen + datalen)
		ret[i++] = ' ';
	ret[i] = '\0';
	return (ret);
}

char	*ft_align(t_elem *e, char *prec)
{
	char	*ret;
	int		datalen;
	int		padlen;

	datalen = ft_strlen(prec);
	padlen = 0;
	if (e->prec || (e->type == 'p' && ft_strchr(prec, '(')))
		e->pad = ' ';
	if (e->width > datalen)
		padlen = e->width - datalen;
	if (ft_atoi(prec) < 0 && e->prec)
		e->pad = ' ';
	ret = ft_put_align(e, prec, datalen, padlen);
	free(prec);
	if (!ret)
		return (0);
	fix_minus(ret);
	if (e->type == 'p')
		fix_hex(ret);
	return (ret);
}

char	*ft_fill_buffer(t_elem *e)
{
	char	*prec;
	char	*buffer;

	if (e->type == '%')
	{
		e->type = 'i';
		e->prec = 0;
	}
	prec = ft_prec(e);
	if (!prec)
		return (0);
	buffer = ft_align(e, prec);
	return (buffer);
}
