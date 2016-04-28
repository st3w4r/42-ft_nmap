/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 11:53:54 by snettah           #+#    #+#             */
/*   Updated: 2014/11/10 12:33:21 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strequ(char const *s1, char const *s2)
{
	if (s1 && s2)
	{
		if (ft_strlen((char*)s1) == ft_strlen((char*)s2))
		{
			if (ft_strstr((char*)s1, (char*)s2))
				return (1);
		}
	}
	else if (s1 == NULL && s2 == NULL)
		return (1);
	return (0);
}
