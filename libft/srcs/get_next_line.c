/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snettah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 17:05:24 by snettah           #+#    #+#             */
/*   Updated: 2015/01/07 17:05:35 by snettah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static int			check_line(char *str)
{
	int				i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char			*ft_join(char **tmp, char *buf)
{
	char			*str;

	str = ft_strjoin(*tmp, buf);
	ft_strdel(tmp);
	return (str);
}

static char			*ft_write_stock(char **line, char **src)
{
	int				n;
	char			*tmp;

	n = check_line(*src);
	*line = ft_strsub(*src, 0, n);
	n++;
	tmp = ft_strsub(*src, n, ft_strlen(*src) - n);
	ft_strdel(src);
	return (tmp);
}

int					get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static char		*tmp[10000];
	int				ret;
	int				k;

	*tmp = NULL;
	if (line == NULL || fd < 0)
		return (-1);
	while ((k = check_line(tmp[fd])) == -1)
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		tmp[fd] = ft_join(&tmp[fd], buf);
		if (ret == 0)
		{
			*line = ft_strdup(tmp[fd]);
			return (0);
		}
	}
	tmp[fd] = ft_write_stock(line, &tmp[fd]);
	if (!*line || !tmp[fd])
		return (-1);
	return (1);
}
