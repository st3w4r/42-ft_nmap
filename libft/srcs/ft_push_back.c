/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 15:12:30 by snettah           #+#    #+#             */
/*   Updated: 2014/11/14 15:22:10 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_push_back(t_list **lst, const void *content, size_t content_size)
{
	t_list	*tmp;

	if (lst)
	{
		tmp = *lst;
		while (lst)
			tmp = tmp->next;
		tmp->next = ft_lstnew(content, content_size);
	}
	else
		*lst = ft_lstnew(content, content_size);
}
