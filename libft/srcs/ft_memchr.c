/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 14:47:43 by snettah           #+#    #+#             */
/*   Updated: 2014/11/10 11:40:47 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memchr(const void *s, int c, size_t n)
{
	const char	*tmp;
	size_t		i;

	i = 0;
	tmp = (char*)s;
	if (s && n > 0)
	{
		while (i < n)
		{
			if ((unsigned char)tmp[i] == (unsigned char)c)
				return ((void*)s + i);
			i++;
		}
	}
	return (NULL);
}
