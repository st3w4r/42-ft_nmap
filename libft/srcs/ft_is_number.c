/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 13:45:37 by ybarbier          #+#    #+#             */
/*   Updated: 2016/05/02 13:52:36 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_is_number(char *number)
{
	unsigned int i;

	i = 0;
	while (i < ft_strlen(number))
	{
		if (ft_isdigit(number[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
