/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 14:36:37 by snettah           #+#    #+#             */
/*   Updated: 2015/02/06 15:16:44 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strdup(char *s1)
{
	char		*cpy;
	int			i;
	size_t		size;

	size = ft_strlen(s1);
	i = 0;
	if (!s1)
		return (NULL);
	cpy = (char*)malloc(sizeof(char) * size + 1);
	if (!cpy)
		return (NULL);
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
