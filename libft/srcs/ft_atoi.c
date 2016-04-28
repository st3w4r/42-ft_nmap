/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 12:43:22 by snettah           #+#    #+#             */
/*   Updated: 2015/01/05 12:43:25 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int		nb;
	int		sign;
	char	*temp;

	nb = 0;
	sign = 1;
	temp = ft_ltrim(str);
	if (*temp == '+')
	{
		sign = 1;
		temp++;
	}
	else if (*temp == '-')
	{
		sign = -1;
		temp++;
	}
	while (ft_isdigit(*temp) == 1)
	{
		nb = nb * 10;
		nb = nb + (*temp - '0');
		temp++;
	}
	return (nb * sign);
}
