/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 13:44:22 by snettah           #+#    #+#             */
/*   Updated: 2014/11/10 11:17:14 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	str = malloc(sizeof(char*) * ft_strlen(s));
	if (!s)
		return (NULL);
	ft_strcpy(str, s);
	i = ft_strlen(s);
	while ((int)i >= 0)
	{
		if (str[i] == c)
			return ((char*)s + i);
		i--;
	}
	return (NULL);
}
