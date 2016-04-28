/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltrim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 18:34:45 by snettah           #+#    #+#             */
/*   Updated: 2015/01/06 18:34:48 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_ltrim(char const *s)
{
	char	*trim;

	trim = NULL;
	if (s)
	{
		trim = (char *)s;
		while (ft_isblank(*trim))
			trim++;
		if (!*trim)
			return ((char *)s);
	}
	return (trim);
}
