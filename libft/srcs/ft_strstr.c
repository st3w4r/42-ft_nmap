/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/02 15:04:01 by snettah           #+#    #+#             */
/*   Updated: 2014/11/05 14:53:46 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	b;
	int size;

	i = 0;
	b = 0;
	size = 0;
	while (to_find[size])
		size++;
	if (size == 0)
		return (str);
	while (str[i])
	{
		while (to_find[b] == str[b + i])
		{
			if (b == size - 1)
				return (str + i);
			b++;
		}
		b = 0;
		i++;
	}
	return (NULL);
}
