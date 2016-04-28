/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 12:45:04 by snettah           #+#    #+#             */
/*   Updated: 2014/11/12 13:16:38 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdelone(t_list **alst, void (*del) (void *, size_t))
{
	t_list	*tmp;

	tmp = *alst;
	del(tmp->content, tmp->content_size);
	ft_memdel((void**)alst);
}
