/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 13:44:05 by ybarbier          #+#    #+#             */
/*   Updated: 2016/05/02 13:51:13 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_uint	ft_arrlen(char **arr)
{
	t_uint count;

	count = 0;
	while (arr && arr[count])
		++count;
	return (count);
}
