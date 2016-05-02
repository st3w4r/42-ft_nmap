/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 18:29:32 by snettah           #+#    #+#             */
/*   Updated: 2015/01/06 18:29:34 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_cnt_word(char *str, char c)
{
	size_t i;
	size_t k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			k++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (k);
}

char		**ft_split(char **split, char *str, char c, size_t j)
{
	size_t		i;
	size_t		start;
	size_t		k;

	i = 0;
	start = 0;
	k = 0;
	while (str[i] != '\0' && k < j)
	{
		if (str[i] != c)
		{
			start = i;
			while (str[i] != c && str[i] != '\0')
				i++;
			split[k] = ft_strsub(str, start, i - start);
			k++;
		}
		else
			i++;
	}
	split[k] = NULL;
	return (split);
}

char		**ft_strsplit(char const *str, char c)
{
	char		**split;
	size_t		k;

	if (!str)
		return (NULL);
	k = ft_cnt_word((char*)str, c);
	split = NULL;
	if ((split = (char**)malloc((k + 1) * sizeof(char*))) == NULL)
    return (NULL);
	if (!split)
		return (NULL);
	split = ft_split(split, (char*)str, c, k);
	return (split);
}
