/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 12:24:33 by snettah           #+#    #+#             */
/*   Updated: 2014/12/02 18:42:24 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (1);
	if (s1 && s2)
	{
		while (i < n)
		{
			if (s1[i] == s2[i])
				i++;
			else
				return (0);
		}
	}
	if (i == n)
		return (1);
	return (0);
}
