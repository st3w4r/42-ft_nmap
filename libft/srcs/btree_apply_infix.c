/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/03 12:57:39 by snettah           #+#    #+#             */
/*   Updated: 2014/12/03 13:01:36 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			btree_apply_infix(t_btree *root, void (*f)(void*))
{
	if (root && f)
	{
		if (root->left)
			btree_apply_infix(root->left, f);
		f(root->item);
		if (root->right)
			btree_apply_infix(root->right, f);
	}
}
