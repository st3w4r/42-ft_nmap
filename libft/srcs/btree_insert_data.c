/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 14:01:44 by snettah           #+#    #+#             */
/*   Updated: 2015/01/06 18:43:30 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		btree_insert_data(t_btree **root, void *item, int (*f)(void *,
			void *))
{
	if (*root == NULL)
		btree_create_node(item);
	else if ((*f)(item, (*root)->item) < 0)
		btree_insert_data(&(*root)->left, item, f);
	else
		btree_insert_data(&(*root)->right, item, f);
}
