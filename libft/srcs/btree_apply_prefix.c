/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_prefix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 12:54:32 by snettah           #+#    #+#             */
/*   Updated: 2014/12/03 14:22:30 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		btree_apply_prefix(t_btree *root, void (*f)(void*))
{
	if (root && f)
	{
		f(root->item);
		if (root->left)
			btree_apply_prefix(root->left, f);
		if (root->right)
			btree_apply_prefix(root->right, f);
	}
}
