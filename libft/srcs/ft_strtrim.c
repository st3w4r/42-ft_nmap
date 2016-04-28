/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:05:12 by snettah           #+#    #+#             */
/*   Updated: 2014/12/02 18:47:49 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == ' ')
		return (1);
	return (0);
}

static int			*ft_strend(char *c, int *start, int *end)
{
	int				b;

	b = 0;
	while (ft_isspace(c[b]) == 1)
		b++;
	*start = b;
	b = ft_strlen(c);
	while (ft_isspace(c[b - 1]) == 1)
		b--;
	*end = b;
	return (0);
}

char				*ft_strtrim(char const *s)
{
	char			*str;
	int				i;
	int				b;
	int				cur;

	cur = 0;
	if (s)
	{
		ft_strend((char*)s, &i, &b);
		str = ft_strnew(ft_strlen(s));
		if (!str)
			return (NULL);
		while (i < b)
		{
			str[cur] = s[i];
			i++;
			cur++;
		}
		str[cur] = '\0';
		return (str);
	}
	return ((char*)s);
}
