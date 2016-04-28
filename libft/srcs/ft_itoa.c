/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 14:45:34 by snettah           #+#    #+#             */
/*   Updated: 2014/11/13 10:24:06 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoaswp(char *itoa)
{
	int		size;
	int		i;
	char	ptr;

	i = 0;
	size = ft_strlen(itoa) - 1;
	if (itoa[i] == '-')
		i++;
	while (i < size)
	{
		ptr = itoa[i];
		itoa[i] = itoa[size];
		itoa[size] = ptr;
		i++;
		size--;
	}
	return (itoa);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		i;

	if (n < -2147483646)
		return ("-2147483648");
	i = 0;
	str = (char*)malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[i] = '-';
		n = -n;
		i++;
	}
	while (n > 9)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	str[i] = n + '0';
	str[i + 1] = '\0';
	str = ft_itoaswp(str);
	return (str);
}
