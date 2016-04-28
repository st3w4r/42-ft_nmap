/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 14:59:43 by snettah           #+#    #+#             */
/*   Updated: 2014/11/14 15:02:53 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_print_list(t_list *lst)
{
	if (lst)
	{
		while (lst)
		{
			ft_putstr(lst->content);
			ft_putchar('\n');
			lst = lst->next;
		}
	}
	else
		return ;
}
