/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 10:14:13 by snettah           #+#    #+#             */
/*   Updated: 2015/03/05 13:10:49 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
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
			str[i] = (*f)(s[i]);
			i++;
		}
	}
	return (str);
}
