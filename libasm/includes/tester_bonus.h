/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:47:22 by agiraude          #+#    #+#             */
/*   Updated: 2021/02/04 11:24:45 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_BONUS_H
# define TESTER_BONUS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "libasm_bonus.h"

int		atoi_base(char *str, char *base);
void	lst_print(t_list *lst);
void	test_remove(t_list **lst, char *str);
void	test_push(t_list **lst, char *str);
void	test_size(t_list **lst);
void	test_sort(t_list **lst);

#endif
