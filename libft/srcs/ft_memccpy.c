/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 13:32:57 by snettah           #+#    #+#             */
/*   Updated: 2014/11/07 18:41:12 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*dt;
	const char	*sc;

	sc = src;
	dt = dest;
	while (n--)
	{
		if (*sc == c)
		{
			*dt++ = *sc++;
			return (dt);
		}
		*dt++ = *sc++;
	}
	return (NULL);
}
