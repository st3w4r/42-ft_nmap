/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epur_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/06 15:30:21 by snettah           #+#    #+#             */
/*   Updated: 2015/02/06 15:32:37 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char		*ft_epur_str(char *src)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!src || !(tmp = (char *)malloc(sizeof(char) * ft_strlen(src) + 1)))
		return (NULL);
	while (src[i])
	{
		if ((src[i] == ' ' || src[i] == '	') && src[i])
		{
			i++;
			if ((tmp[j - 1] > 32 && tmp[j - 1] < 127) && (src[i] > 32 && src[i]
						< 127))
				tmp[j++] = ' ';
			continue ;
		}
		if (src[i] > 32 && src[i] < 127)
			tmp[j++] = src[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}
