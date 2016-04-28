/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 13:59:37 by snettah           #+#    #+#             */
/*   Updated: 2015/03/05 13:09:11 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*tmp;

	tmp = (char*)malloc(sizeof(char*) * n);
	ft_strncpy(tmp, src, n);
	ft_strncpy(dest, tmp, n);
	free(tmp);
	return (dest);
}
