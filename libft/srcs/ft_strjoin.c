/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/20 11:53:10 by snettah           #+#    #+#             */
/*   Updated: 2014/11/20 14:46:13 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;

	if (s1 && s2)
	{
		new = NULL;
		if ((new = ft_strnew(ft_strlen(s1) + ft_strlen(s2))) == NULL)
			return (NULL);
		new = ft_strncat(new, (char*const)s1, ft_strlen(s1));
		new = ft_strncat(new, (char*const)s2, ft_strlen(s2));
		return (new);
	}
	else if (!s1 && s2)
		return (ft_strdup((char*const)s2));
	else if (s1 && !s2)
		return (ft_strdup((char*const)s1));
	return (NULL);
}
