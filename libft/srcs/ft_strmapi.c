/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 11:37:19 by snettah           #+#    #+#             */
/*   Updated: 2015/03/05 13:11:09 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (s)
	{
		str = (char*)ft_memalloc(ft_strlen(s));
		while (i < ft_strlen(s))
		{
			str[i] = (*f)(i, s[i]);
			i++;
		}
	}
	return (str);
}
