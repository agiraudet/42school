/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:06:48 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/19 14:31:11 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_prec_str(t_elem *e)
{
	char	*ret;
	char	*src;
	int		i;
	int		datalen;

	e->pad = ' ';
	src = e->data;
	datalen = ft_strlen(src);
	if (e->prec && e->size < datalen)
		datalen = e->size;
	ret = (char*)malloc(sizeof(char) * (datalen + 1));
	if (!ret)
		return (0);
	i = 0;
	while (i < datalen)
		ret[i++] = *src++;
	ret[i] = '\0';
	return (ret);
}

char	*ft_prec_chr(t_elem *e)
{
	e->pad = ' ';
	return (ft_strdup(e->data));
}

char	*ft_prec_nbr(t_elem *e)
{
	char	*ret;
	char	*src;
	int		i;
	int		datalen;
	int		padlen;

	src = e->data;
	datalen = ft_strlen(src);
	padlen = 0;
	if (e->prec && !e->size && *src == '0' && datalen == 1)
		return (ft_strdup(""));
	if (e->prec && e->size > datalen)
		padlen = e->size - datalen;
	padlen += (ft_strchr(src, '-') && e->prec && e->size >= datalen) ? 1 : 0;
	ret = (char*)malloc(sizeof(char) * (datalen + padlen + 1));
	if (!ret)
		return (0);
	i = 0;
	while (i < padlen)
		ret[i++] = '0';
	while (i < datalen + padlen)
		ret[i++] = *src++;
	ret[i] = '\0';
	fix_minus(ret);
	return (ret);
}

char	*ft_prec_ptr(t_elem *e)
{
	char	*ret;
	char	*src;
	int		i;
	int		datalen;
	int		padlen;

	src = e->data;
	if (ft_strchr(src, '('))
		return (ft_strdup(src));
	datalen = ft_strlen(src);
	if (e->prec && e->size == 0 && e->data[0] == '0')
		return (ft_strdup("0x"));
	padlen = ft_set_padlen(e, datalen);
	if (!(ret = (char*)malloc(sizeof(char) * (datalen + padlen + 3))))
		return (0);
	ret[0] = '0';
	ret[1] = 'x';
	i = 2;
	while (i < padlen + 2)
		ret[i++] = '0';
	while (i < datalen + padlen + 2)
		ret[i++] = *src++;
	ret[i] = '\0';
	return (ret);
}

char	*ft_prec(t_elem *e)
{
	if (ft_strchr("diuxX", e->type))
		return (ft_prec_nbr(e));
	else if (e->type == 'p')
		return (ft_prec_ptr(e));
	else if (e->type == 's')
		return (ft_prec_str(e));
	else if (e->type == 'c')
		return (ft_prec_chr(e));
	else
		return (0);
}
