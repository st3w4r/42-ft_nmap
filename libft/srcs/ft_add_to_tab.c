/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/09 11:59:30 by snettah           #+#    #+#             */
/*   Updated: 2015/02/09 12:51:34 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char			**ft_add_to_tab(char **tab, char *str)
{
	char		**new;
	int			i;
	int			size;

	size = ft_tablen(tab);
	if (!tab)
		return (NULL);
	new = (char**)malloc(sizeof(char*) * (size + 2));
	i = 0;
	if (!new)
		return (NULL);
	while (tab[i] != NULL)
	{
		new[i] = tab[i];
		i++;
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	free(tab);
	return (new);
}
