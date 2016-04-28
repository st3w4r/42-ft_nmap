/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 18:37:23 by snettah           #+#    #+#             */
/*   Updated: 2015/01/13 12:37:45 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s2[i] == '\0')
		return ((char *)s1);
	while (s1[i] && ((i + (size_t)ft_strlen(s2))) <= n)
	{
		if (!ft_strncmp(&((char *)s1)[i], s2, ft_strlen(s2)))
			return (&((char *)s1)[i]);
		i++;
	}
	return (NULL);
}
