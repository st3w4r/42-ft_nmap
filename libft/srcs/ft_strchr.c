/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 12:01:17 by snettah           #+#    #+#             */
/*   Updated: 2014/11/22 13:03:13 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strchr(const char *s, int c)
{
	char		*str;
	int			i;

	i = 0;
	str = (char*)s;
	if (!s)
		return (NULL);
	while (str[i] != c && str[i] != '\0')
		i++;
	if (str[i] != c)
		return (NULL);
	return (str + i);
}
