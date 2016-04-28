/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 18:26:55 by snettah           #+#    #+#             */
/*   Updated: 2015/01/06 18:27:00 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_btree		*btree_create_node(void *item)
{
	t_btree	*node;

	node = NULL;
	if (!(node = (t_btree *)malloc(sizeof(*node))))
		return (NULL);
	node->item = (item ? item : 0);
	node->left = 0;
	node->right = 0;
	return (node);
}
