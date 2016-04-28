/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 17:26:55 by snettah           #+#    #+#             */
/*   Updated: 2014/11/06 11:58:02 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isalpha(int str)
{
	if (str >= 'a' && str <= 'z')
	{
		return (1);
	}
	if (str >= 'A' && str <= 'Z')
	{
		return (1);
	}
	else
		return (0);
}
