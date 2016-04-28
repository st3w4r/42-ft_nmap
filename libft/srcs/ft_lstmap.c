/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 11:06:06 by snettah           #+#    #+#             */
/*   Updated: 2014/11/14 14:53:31 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*ptrnew;
	t_list	*list;

	if (!lst || !f)
		return (NULL);
	new = f(lst);
	ptrnew = ft_lstnew(new->content, new->content_size);
	list = ptrnew;
	lst = lst->next;
	while (lst)
	{
		new = f(lst);
		list->next = ft_lstnew(new->content, new->content_size);
		lst = lst->next;
		list = list->next;
	}
	return (ptrnew);
}
