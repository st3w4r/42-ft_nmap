/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 14:27:00 by snettah           #+#    #+#             */
/*   Updated: 2015/03/05 13:21:30 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *alst;
	if (alst != NULL && del != NULL)
	{
		while (tmp)
		{
			tmp2 = tmp->next;
			del(tmp->content, tmp->content_size);
			free(tmp);
			tmp = tmp2;
		}
		*alst = NULL;
	}
}
