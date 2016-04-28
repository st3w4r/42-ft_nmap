/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 18:27:15 by snettah           #+#    #+#             */
/*   Updated: 2015/01/06 18:27:19 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*substring;

	i = 0;
	substring = NULL;
	if (s && len > 0)
	{
		if ((substring = ft_strnew(len)) == NULL)
			return (NULL);
		while (i < len)
		{
			substring[i] = s[start];
			start++;
			i++;
		}
		substring[len] = '\0';
		return (substring);
	}
	return (ft_strdup(""));
}
