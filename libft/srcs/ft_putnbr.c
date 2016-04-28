/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/06 18:37:56 by snettah           #+#    #+#             */
/*   Updated: 2015/01/06 18:37:58 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void				ft_putnbr(int n)
{
	unsigned int	nbr;
	unsigned int	temp;

	nbr = (n < 0 ? -n : n);
	if (n < 0)
		write(1, "-", 1);
	if (nbr < 10)
	{
		temp = nbr + 48;
		write(1, &temp, 1);
	}
	else
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
}
