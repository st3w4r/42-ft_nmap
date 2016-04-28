/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 13:49:12 by snettah           #+#    #+#             */
/*   Updated: 2014/12/02 19:04:03 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char*)s1;
	c2 = (unsigned char*)s2;
	i = 0;
	if (n == 0)
		return (0);
	if (s1 && s2)
	{
		while (c1[i] == c2[i] && i <= n)
		{
			i++;
			if (i == n || (c1[i] == '\0' && c2[i] == '\0'))
				return (0);
		}
		return (c1[i] - c2[i]);
	}
	return (0);
}
